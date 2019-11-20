#ifndef AUTHORIZE_H
#define AUTHORIZE_H

#include <QCryptographicHash>
#include <QDateTime>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

#include "../io/database_handler.h"
#include "../utils/util.h"

// token失效时间
//#define TOKEN_TIME_LIMIT 120

class AuthItem : public DatabaseItem {
 private:
  QString id;
  QString path;
  QString ipaddr;
  QString hostname;
  QString token;
  QString createtime;
  QString salt;

 public:
  AuthItem();

  AuthItem(QString id,
           QString path,
           QString ipaddr,
           QString hostname,
           QString token,
           QString createtime,
           QString salt);

  QString getValuesString() override;

  /* getter and setter */
  QString getId() const;
  void setId(const QString& value);

  QString getPath() const;
  void setPath(const QString& value);

  QString getIpaddr() const;
  void setIpaddr(const QString& value);

  QString getHostname() const;
  void setHostname(const QString& value);

  QString getToken() const;
  void setToken(const QString& value);

  QString getCreatetime() const;
  void setCreatetime(const QString& value);

  QString getSalt() const;
  void setSalt(const QString& value);
};

/**
 * @brief The AuthDatabaseHandler class 鉴权数据库处理中心
 */
class AuthDatabaseHandler : protected DatabaseHandler {
  Q_OBJECT
 signals:
  /**
   * @brief tokenInvalid token 不合法
   * @param token invalid token 不合法
   * @param msg 错误信息
   */
  void tokenNotFound(QString token, QString msg);

  /**
   * @brief tokenTimeout token timeout
   * @param token token
   * @param createTime 创建时间
   * @param timeOutSec 超时秒数
   */
  void tokenTimeout(QString token, QDateTime createTime, qint32 timeOutSec);

  /**
   * @brief tokenNotFit token内容不合法
   * @param token token
   */
  void tokenNotFit(QString token);

 public:
  explicit AuthDatabaseHandler(QString table);
  explicit AuthDatabaseHandler(QString table, int timeout);

  /**
   * @brief checkIfTokenTimeout 检查token是否有效
   * @param token
   * @return bool
   */
  bool checkIfTokenValid(QString token);

  virtual void insertIntoDatabase(DatabaseItem&) override;

  virtual void removeFromDatabase(
      QMap<QString, MergeQIntegerAndQString>) override;

  virtual QSqlQuery getDataFromDatabase(
      QMap<QString, MergeQIntegerAndQString>) override;

  virtual bool checkDataExist(QMap<QString, MergeQIntegerAndQString>) override;

  virtual void updateFromDatabase(
      QString field,
      QString fieldValue,
      QMap<QString, MergeQIntegerAndQString>) override;

 private:
  void createTableWithName(QString name);
  qint32 timeout;
};

/**
 * @brief The Authorize class 鉴权中心
 */
class Authorize : public QObject {
  Q_OBJECT

 signals:

 private:
  AuthDatabaseHandler* handler;

  /**
   * @brief timeLimit 超时毫秒数
   */
  qint32 timeLimit;

 public:
  explicit Authorize(int);

  /**
   * @brief applyUniqueToken 向鉴权中心申请唯一token
   * @return
   */
  QString applyUniqueToken(QString ipaddr, QString hostname, QString path);

  /**
   * @brief checkIfTokenValid 检查token是否失效
   * @param token token
   * @return bool
   */
  bool checkIfTokenValid(QString token);

  /**
   * @brief getUniqueToken 生成unique id
   * @param ipaddr ip
   * @param hostname 主机名
   * @param path 路径
   * @param salt 加盐
   * @return 唯一id
   */
  static QString getUniqueToken(QString ipaddr,
                                QString hostname,
                                QString path,
                                QString salt);

  /**
   * @brief getRandomSalt 得到随机salt
   * @return QString-salt
   */
  static QString getRandomSalt(void);

  /**
   * @brief getTimeout 获得超时秒数
   * @return qint32
   */
  inline qint32 getTimeout() const;
};

#endif  // AUTHORIZE_H
