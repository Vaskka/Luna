#include "util.h"

Util::Util() {}

/**
 * @brief Util::getUniqueId 得到唯一ID
 * @return
 */
QString Util::getUniqueId() {
  QString res = QUuid::createUuid().toString();
  int len = res.length();

  res = res.left(len - 1);
  res = res.remove(0, 1);

  return res;
}

/**
 * @brief Util::getLocalAddress 得到本机IP
 * @return
 */
QHostAddress Util::getLocalAddress() {
  foreach (const QHostAddress& hostAddress, QNetworkInterface::allAddresses()) {
    qDebug() << hostAddress;
    if (hostAddress != QHostAddress::LocalHost && hostAddress.toIPv4Address()) {
      return hostAddress;
    }
  }

  return QHostAddress::LocalHost;
}

/**
 * @brief getTimeStamp 得到时间戳
 * @return  int
 */
quint32 Util::getTimeStamp(void) {
  QDateTime time = QDateTime::currentDateTime();  //获取当前时间
  return time.toTime_t();  //将当前时间转为时间戳
}

/**
 * @brief Util::getRandom 获得不大于upper的随机数
 * @param upper
 * @return
 */
qint32 Util::getRandom(qint32 upper) {
  qsrand(getTimeStamp());

  return qrand() % upper;
}

/**
 * @brief getFormatCurrentDateTime 得到格式化的当前时间
 * @return QString
 */
QString Util::getFormatCurrentDateTime() {
  return QDateTime::currentDateTime().toUTC().toString("yyyy-MM-dd HH:mm:ss");
}

quint32 Util::increment = 0;

/**
 * @brief Util::getAutoInceaseId 获取自增id
 * @return quint32
 */
quint32 Util::getAutoInceaseId() {
  Util::increment = (Util::increment + 1) % 0xFFFFFF;
  return Util::increment;
}

/**
 * @brief Util::fromPathGetFileName 使用路径名得到文件名
 * @param path path
 * @return 文件名
 */
QString Util::fromPathGetFileName(QString path) {
  if (path.contains('\\')) {
    QString* s = new QString;
    for (int i = path.length() - 1; i >= 0; i--) {
      QChar curr = path.at(i);
      if (curr == '\\') {
        break;
      }

      s->insert(0, path.at(i));
    }
    return *s;

  } else {
    QFileInfo info(path);

    return info.fileName();
  }
}
