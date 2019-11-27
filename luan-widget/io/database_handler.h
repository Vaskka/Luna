#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H

#include <qdebug.h>

#include <QMap>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "../common.h"

class MergeQIntegerAndQString {
 public:
  enum MergeQIntegerAndQStringType { Integer, String };
  MergeQIntegerAndQStringType getType() const;
  MergeQIntegerAndQString();
  MergeQIntegerAndQString(qint32 intValue);

  MergeQIntegerAndQString(QString stringValue);

  void setData(qint32 value);
  void setData(QString value);
  QString getData() const;

 private:
  MergeQIntegerAndQStringType type;

  QString data;
};

class DatabaseItem {
 public:
  /**
   * @brief getValuesString 得到values后连接字符串
   * @return QString
   */
  virtual QString getValuesString(void) = 0;
};

class DatabaseHandler : public QObject {
  Q_OBJECT
 signals:

  void openError(QString errmsg);

  void insertError(QString insertValuesString, QString errmsg);

  void queryError(QMap<QString, MergeQIntegerAndQString> map, QString errmsg);

 protected:
  QString tableName;

  QSqlDatabase ref;

 public:
  /**
   * @brief concatWhereString 得到where组合结果
   * @return QString
   */
  static QString concatWhereString(QMap<QString, MergeQIntegerAndQString>);

  /**
   * @brief searchResultWithFieldAndName 在结果中搜索
   * @param query qsqlquery
   * @param field field
   * @param name name
   * @return QString
   */
  static QString searchResultWithFieldAndName(QSqlQuery& query,
                                              QString field,
                                              QVariant fieldVar,
                                              QString searchFirld);

  /**
   * @brief insertIntoDatabase 执行插入接口
   */
  virtual void insertIntoDatabase(DatabaseItem&) = 0;

  /**
   * @brief removeFromDatabase 执行删除的接口
   */
  virtual void removeFromDatabase(QMap<QString, MergeQIntegerAndQString>) = 0;

  /**
   * @brief getDataFromDatabase 执行查询的接口
   */
  virtual QSqlQuery getDataFromDatabase(
      QMap<QString, MergeQIntegerAndQString>) = 0;

  /**
   * @brief updateFromDatabase 更新数据的接口
   */
  virtual void updateFromDatabase(QString field,
                                  QString fieldValue,
                                  QMap<QString, MergeQIntegerAndQString>) = 0;

  /**
   * @brief checkDataExist 查看是否存在数据的接口
   * @return
   */
  virtual bool checkDataExist(QMap<QString, MergeQIntegerAndQString>) = 0;

  DatabaseHandler(QString table);
};

#endif  // DATABASE_HANDLER_H
