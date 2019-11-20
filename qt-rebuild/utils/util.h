#ifndef UTIL_H
#define UTIL_H

#include <QCryptographicHash>
#include <QDate>
#include <QDateTime>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QUuid>

class Util {
 public:
  Util();

  /**
   * @brief getUniqueId 获取唯一id
   * @return QString
   */
  static QString getUniqueId();

  /**
   * @brief getLocalAddress 得到本机IP
   * @return
   */
  static QHostAddress getLocalAddress(void);

  /**
   * @brief getTimeStamp 得到时间戳
   * @return  int
   */
  static quint32 getTimeStamp(void);

  /**
   * @brief getRandom 获得不大于upper的随机数
   * @param upper
   * @return
   */
  static qint32 getRandom(qint32 upper);

  /**
   * @brief getFormatCurrentDateTime 得到格式化的当前时间
   * @return QString
   */
  static QString getFormatCurrentDateTime();
};

#endif  // UTIL_H
