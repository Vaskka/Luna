#include "database_handler.h"

MergeQIntegerAndQString::MergeQIntegerAndQString() {}

MergeQIntegerAndQString::MergeQIntegerAndQString(qint32 intValue) {
  this->data = QString::number(intValue);

  this->type = MergeQIntegerAndQStringType::Integer;
}

MergeQIntegerAndQString::MergeQIntegerAndQString(QString stringValue) {
  this->data = QString("");
  this->data.append('\'');
  this->data.append(stringValue);
  this->data.append('\'');

  this->type = MergeQIntegerAndQStringType::String;
}

QString DatabaseHandler::concatWhereString(
    QMap<QString, MergeQIntegerAndQString> where) {
  QMap<QString, MergeQIntegerAndQString> whereRaw = where;

  if (!whereRaw.count()) {
    return QString::number(1);
  }

  QMapIterator<QString, MergeQIntegerAndQString> it(whereRaw);
  QString res;

  while (it.hasNext()) {
    QMapIterator<QString, MergeQIntegerAndQString>::Item item = it.next();

    res.append(item.key());
    res.append(" = ");
    res.append(item.value().getData());
    res.append(" and ");
  }

  int len = res.length();
  res = res.left(len - 4);

  if (!res.length()) {
    return QString::number(1);
  }

  return res;
}

QString DatabaseHandler::searchResultWithFieldAndName(QSqlQuery& query,
                                                      QString field,
                                                      QVariant var,
                                                      QString searchFirld) {
  query.first();

  do {
    QVariant currVar = query.value(field);

    if (currVar == var) {
      return query.value(searchFirld).toString();
    }

  } while (query.next());

  return nullptr;
}

DatabaseHandler::DatabaseHandler(QString table) {
  this->tableName = table;
  this->ref = QSqlDatabase::addDatabase("QSQLITE");

  this->ref.setDatabaseName(QString(PROJECT_NAME) + ".db");

  // 检查数据库打开情况
  if (!this->ref.open()) {
    QString errmsg = QString("Error: Failed to connect database.") +
                     this->ref.lastError().text();
    qDebug() << errmsg;
    emit this->openError(errmsg);

  } else {
    qDebug() << "Succeed to connect database.";
  }
}

MergeQIntegerAndQString::MergeQIntegerAndQStringType
MergeQIntegerAndQString::getType() const {
  return type;
}

void MergeQIntegerAndQString::setData(qint32 value) {
  this->type = MergeQIntegerAndQStringType::Integer;

  this->data = QString::number(value);
}

void MergeQIntegerAndQString::setData(QString value) {
  this->type = MergeQIntegerAndQStringType::String;

  this->data = QString("");
  this->data.append('\'');
  this->data.append(value);
  this->data.append('\'');
}

QString MergeQIntegerAndQString::getData() const {
  return this->data;
}
