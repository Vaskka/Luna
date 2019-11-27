#ifndef IOCENTER_H
#define IOCENTER_H

#include <QDebug>
#include <QFile>
#include <QObject>

class IOCenter : public QObject {
  Q_OBJECT

 signals:

  /**
   * @brief readDataDone数据读取完成
   * @param uri 读取uri
   */
  void readDataDone(QString uri);

  /**
   * @brief saveDataDone 文件save完成
   * @param uri
   */
  void saveDataDone(QString uri);

  /**
   * @brief fileOpenError 文件打开错误
   * @param uri uri
   */
  void fileOpenError(QString uri);

 public:
  IOCenter();

  QByteArray readDataFromUri(QString uri);

  void saveDataIntoPath(QString uri, QByteArray data);
};

#endif  // IOCENTER_H
