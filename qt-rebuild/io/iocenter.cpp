#include "iocenter.h"

IOCenter::IOCenter() {}

/**
 * @brief IOCenter::readDataFromUri 从uri读数据
 * @param uri
 * @return
 */
QByteArray IOCenter::readDataFromUri(QString uri) {
  QFile file(uri);

  // open file
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    emit fileOpenError(uri);
    return nullptr;
  }

  // read all
  QByteArray res = file.readAll();

  file.close();

  emit readDataDone(uri);
  return res;
}

/**
 * @brief IOCenter::saveDataIntoPath 保存数据到路径
 * @param uri uri
 * @param data data
 */
void IOCenter::saveDataIntoPath(QString uri, QByteArray data) {
  QFile file(uri);

  // open file
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    emit fileOpenError(uri);
    return;
  }

  // write
  file.write(data);

  file.close();

  emit saveDataDone(uri);
}
