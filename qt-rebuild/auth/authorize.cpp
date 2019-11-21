#include "authorize.h"

/**
 * @brief AuthDatabaseHandler::checkIfTokenValid 检查token是否合理
 * @param token token
 * @return bool
 */
bool AuthDatabaseHandler::checkIfTokenValid(QString token) {
  QMap<QString, MergeQIntegerAndQString> map;

  map["token"] = MergeQIntegerAndQString(token);

  QSqlQuery query = getDataFromDatabase(map);

  // token 没找到
  if (!query.size()) {
    emit tokenNotFound(token, query.lastError().text());
    return false;
  }

  QSqlRecord r = query.record();
  int id = r.indexOf("id");
  int tokenCol = r.indexOf("token");
  int createTimeCol = r.indexOf("createtime");
  int ipCol = r.indexOf("ipaddr");
  int hostnameCol = r.indexOf("hostname");
  int pathCol = r.indexOf("path");
  int saltCol = r.indexOf("salt");

  // make sure we get first
  query.next();

  // record in database
  QString recordId = query.value(id).toString();
  QString recordToken = query.value(tokenCol).toString();
  QDateTime recordCreateTime = query.value(createTimeCol).toDateTime();
  QString recordIpaddr = query.value(ipCol).toString();
  QString recordHostName = query.value(hostnameCol).toString();
  QString recordPath = query.value(pathCol).toString();
  QString recordSalt = query.value(saltCol).toString();

  // check valid
  QString shouldToken = Authorize::getUniqueToken(recordIpaddr, recordHostName,
                                                  recordPath, recordSalt);
  if (shouldToken != recordToken) {
    emit tokenNotFit(recordToken);
    return false;
  }

  // check time
  qint64 intervalMSec = recordCreateTime.secsTo(QDateTime::currentDateTime());

  if (intervalMSec > this->timeout) {
    this->ref.transaction();

    // where ip = originalIP
    QMap<QString, MergeQIntegerAndQString> ipWhere;
    ipWhere["ipaddr"] = MergeQIntegerAndQString(recordIpaddr);

    // 计算新的salt和token
    recordSalt = Authorize::getRandomSalt();
    recordToken = Authorize::getUniqueToken(recordIpaddr, recordHostName,
                                            recordPath, recordSalt);

    // update salt, token, createtime
    updateFromDatabase("salt", "\"" + recordSalt + "\"", ipWhere);
    updateFromDatabase("token", "\"" + recordToken + "\"", ipWhere);
    updateFromDatabase("createtime",
                       "\"" + Util::getFormatCurrentDateTime() + "\"", ipWhere);

    this->ref.commit();

    emit tokenTimeout(token, recordCreateTime, this->timeout);
  }

  return true;
}

/**
 * @brief AuthDatabaseHandler::insertIntoDatabase 插入数据
 * @param query DatabaseItem实体
 */
void AuthDatabaseHandler::insertIntoDatabase(DatabaseItem& query) {
  QSqlQuery sqlQuery;

  QString queryText =
      "insert into " + this->tableName + " VALUES " + query.getValuesString();

  if (!sqlQuery.exec(queryText)) {
    QString errmsg = "Error: Fail to exec insert:" + queryText +
                     " MSG:" + sqlQuery.lastError().text();

    emit insertError(query.getValuesString(), errmsg);
  }

  qDebug() << sqlQuery.lastError();
}

/**
 * @brief AuthDatabaseHandler::removeFromDatabase remove data with where
 * @param where where-map
 */
void AuthDatabaseHandler::removeFromDatabase(
    QMap<QString, MergeQIntegerAndQString> where) {
  QMap<QString, MergeQIntegerAndQString> whereData = where;
  QSqlQuery query;
  QString queryText = "delete from " + this->tableName + " where " +
                      DatabaseHandler::concatWhereString(whereData);

  if (!query.exec(queryText)) {
    QString errmsg = "Error: Fail to exec query:" + queryText +
                     " MSG:" + query.lastError().text();

    emit queryError(whereData, errmsg);
  }

  qDebug() << query.lastError();
}

/**
 * @brief AuthDatabaseHandler::getDataFromDatabase 查询制定的数据
 * @param where where-map
 * @return QSqlQuery
 */
QSqlQuery AuthDatabaseHandler::getDataFromDatabase(
    QMap<QString, MergeQIntegerAndQString> where) {
  QMap<QString, MergeQIntegerAndQString> whereData = where;
  QSqlQuery query;

  QString queryText = "select * from " + this->tableName + " where " +
                      DatabaseHandler::concatWhereString(whereData);

  if (!query.exec(queryText)) {
    QString errmsg = "Error: Fail to exec query:" + queryText +
                     " MSG:" + query.lastError().text();

    emit queryError(whereData, errmsg);
  }
  qDebug() << query.lastError();

  return query;
}

/**
 * @brief AuthDatabaseHandler::checkDataExist 检查制定where查询是否存在
 * @param where where-map
 * @return bool
 */
bool AuthDatabaseHandler::checkDataExist(
    QMap<QString, MergeQIntegerAndQString> where) {
  QMap<QString, MergeQIntegerAndQString> whereData = where;
  QSqlQuery query(this->ref);

  QString queryText = "select count(1) from " + this->tableName + " where " +
                      DatabaseHandler::concatWhereString(whereData);

  if (!query.exec(queryText)) {
    QString errmsg = "Error: Fail to exec query:" + queryText +
                     " MSG:" + query.lastError().text();

    emit queryError(whereData, errmsg);
  }
  //  query.next();
  //  qDebug() << query.lastError();
  //  qDebug() << this->ref.isValid();
  //  int s = query.size();

  //  bool aa = query.isActive();

  query.first();

  return query.value("count(1)").toBool();
}

/**
 * @brief AuthDatabaseHandler::updateFromDatabase 更新权限表
 * @param field 要更新的列名
 * @param fieldValue 要更新的列值
 * @param where where-map
 */
void AuthDatabaseHandler::updateFromDatabase(
    QString field,
    QString fieldValue,
    QMap<QString, MergeQIntegerAndQString> where) {
  QMap<QString, MergeQIntegerAndQString> whereData = where;
  QSqlQuery query;

  QString queryText = "update " + this->tableName + " set " + field + " = " +
                      fieldValue + " where " +
                      DatabaseHandler::concatWhereString(whereData);

  if (!query.exec(queryText)) {
    QString errmsg = "Error: Fail to exec query:" + queryText +
                     " MSG:" + query.lastError().text();

    emit queryError(whereData, errmsg);
  }
  qDebug() << query.lastError();
}

/**
 * @brief AuthDatabaseHandler::createTableWithName 根据表名创建表
 * @param name
 */
void AuthDatabaseHandler::createTableWithName(QString name) {  // 创建table
  QSqlQuery sqlQuery;

  // 不存在这个表就创建
  if (!this->ref.tables().contains(name)) {
    if (!sqlQuery.exec("create table " + name + " (\
                         id         varchar(255) not null\
                           primary key,\
                         ipaddr     varchar(16)  not null,\
                         hostname   varchar(255),\
                         path       varchar(255) not null,\
                         token      varchar(255),\
                         createtime datetime,\
                         salt       varchar(255)\
                       );")) {
      QString errmsg =
          "Error: Fail to create table." + sqlQuery.lastError().text();
      QMap<QString, MergeQIntegerAndQString> errmap;
      emit queryError(errmap, errmsg);
    } else {
      qDebug() << "Table created!";
    }
  }
}

/**
 * @brief AuthDatabaseHandler::AuthDatabaseHandler
 * @param table 表名
 */
AuthDatabaseHandler::AuthDatabaseHandler(QString table)
    : DatabaseHandler(table) {
  createTableWithName(table);
}

/**
 * @brief AuthDatabaseHandler::AuthDatabaseHandler
 * @param table 表名
 * @param timeout 超时时间
 */
AuthDatabaseHandler::AuthDatabaseHandler(QString table, int timeout)
    : DatabaseHandler(table) {
  createTableWithName(table);
  this->timeout = timeout;
}

/**
 * @brief AuthItem::AuthItem default-construct
 */
AuthItem::AuthItem() {}

/**
 * @brief AuthItem::AuthItem
 * @param id
 * @param path
 * @param ipaddr
 * @param hostname
 * @param token
 * @param createtime
 * @param salt
 */
AuthItem::AuthItem(QString id,
                   QString path,
                   QString ipaddr,
                   QString hostname,
                   QString token,
                   QString createtime,
                   QString salt)
    : DatabaseItem() {
  this->id = QString('"');
  this->path = QString('"');
  this->ipaddr = QString('"');
  this->hostname = QString('"');
  this->token = QString('"');
  this->createtime = QString('"');
  this->salt = QString('"');

  this->id.append(id);
  this->path.append(path);
  this->ipaddr.append(ipaddr);
  this->hostname.append(hostname);
  this->token.append(token);
  this->createtime.append(createtime);
  this->salt.append(salt);

  this->id.append('"');
  this->path.append('"');
  this->ipaddr.append('"');
  this->hostname.append('"');
  this->token.append('"');
  this->createtime.append('"');
  this->salt.append('"');
}

/**
 * @brief AuthItem::getValuesString 得到VALUES后连接字符串
 * @return QString
 */
QString AuthItem::getValuesString(void) {
  QString res("");

  res.append("('");
  res.append(Util::getUniqueId());
  res.append("', ");
  res.append(this->getIpaddr());
  res.append(", ");
  res.append(this->getHostname());
  res.append(", ");
  res.append(this->getPath());
  res.append(", ");
  res.append(this->getToken());
  res.append(", ");
  res.append(this->getCreatetime());
  res.append(", ");
  res.append(this->getSalt());
  res.append(")");

  return res;
}

/**
 * @brief Authorize::Authorize auth-construct
 * @param timeLimit
 */
Authorize::Authorize(int timeLimit) {
  this->timeLimit = timeLimit;
  this->handler = new AuthDatabaseHandler(QString("auth"), this->timeLimit);
}

/**
 * @brief Authorize::getUniqueToken 得到签名
 * @param ipaddr ip
 * @param hostname hostname
 * @param path path
 * @param salt salt
 * @return after-hash
 */
QString Authorize::getUniqueToken(QString ipaddr,
                                  QString hostname,
                                  QString path,
                                  QString salt) {
  QString res = ipaddr + hostname + salt + path;

  return QCryptographicHash::hash(res.toUtf8(), QCryptographicHash::Sha1)
      .toHex();
}

/**
 * @brief getRandomSalt 得到随机salt
 * @return QString-salt
 */
QString Authorize::getRandomSalt(void) {
  QString hashed = QCryptographicHash::hash(
      QString(Util::getTimeStamp()).toUtf8(), QCryptographicHash::Md5);

  QString re(Util::getRandom(256));

  QString res =
      QCryptographicHash::hash((hashed + re).toUtf8(), QCryptographicHash::Md5)
          .toHex();

  return res;
}

/**
 * @brief Authorize::getTimeout 获得超时秒数
 * @return qint32
 */
qint32 Authorize::getTimeout() const {
  return this->timeLimit;
}

/**
 * @brief Authorize::applyUniqueToken 申请唯一token
 * @param ipaddr ip
 * @param hostname hostname
 * @param path path
 * @return token
 */
QString Authorize::applyUniqueToken(QString ipaddr,
                                    QString hostname,
                                    QString path) {
  QMap<QString, MergeQIntegerAndQString> map;
  map["ipaddr"] = ipaddr;
  map["hostname"] = hostname;
  map["path"] = path;

  if (handler->checkDataExist(map)) {
    // 存在返回存在的
    QSqlQuery query = handler->getDataFromDatabase(map);

    QString recordToken = DatabaseHandler::searchResultWithFieldAndName(
        query, "ipaddr", ipaddr, "token");
    return recordToken;

  } else {
    // 不存在这个记录，插入新的
    QString salt = getRandomSalt();
    QString token = getUniqueToken(ipaddr, hostname, path, salt);

    AuthItem item(Util::getUniqueId(), path, ipaddr, hostname, token,
                  Util::getFormatCurrentDateTime(), salt);

    handler->insertIntoDatabase(item);
    return token;
  }
}

/**
 * @brief Authorize::checkIfTokenValid 检查token是否失效
 * @param token token
 * @return  有效true， 无效 false
 */
bool Authorize::checkIfTokenValid(QString token) {
  return handler->checkIfTokenValid(token);
}

/* getter and setter */
QString AuthItem::getHostname() const {
  return hostname;
}

void AuthItem::setHostname(const QString& value) {
  hostname = value;
}

QString AuthItem::getPath() const {
  return path;
}

void AuthItem::setPath(const QString& value) {
  path = value;
}

QString AuthItem::getIpaddr() const {
  return ipaddr;
}

void AuthItem::setIpaddr(const QString& value) {
  ipaddr = value;
}

QString AuthItem::getToken() const {
  return token;
}

void AuthItem::setToken(const QString& value) {
  token = value;
}

QString AuthItem::getCreatetime() const {
  return createtime;
}

void AuthItem::setCreatetime(const QString& value) {
  createtime = value;
}

QString AuthItem::getSalt() const {
  return salt;
}

void AuthItem::setSalt(const QString& value) {
  salt = value;
}

QString AuthItem::getId() const {
  return id;
}

void AuthItem::setId(const QString& value) {
  id = value;
}
