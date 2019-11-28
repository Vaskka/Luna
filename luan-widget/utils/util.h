#ifndef UTIL_H
#define UTIL_H

#include <QCryptographicHash>
#include <QDate>
#include <QDateTime>
#include <QFileInfo>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QRegExp>
#include <QUuid>

class Util {
 private:
  /**
   * @brief increment 自增id
   */
  static quint32 increment;

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

  /**
   * @brief getAutoInceaseId 得到自增id
   * @return quint32
   */
  static quint32 getAutoInceaseId();

  /**
   * @brief fromPathGetFileName 使用路径得到文件名
   * @param path path
   * @return QString
   */
  static QString fromPathGetFileName(QString path);

  /**
   * @brief changeCompatibleIpv6ToIpv4 将ipv6兼容地址转换为ipv4
   * @param compatibleIpv6 兼容的ipv6
   * @return ipv4
   */
  static QString changeCompatibleIpv6ToIpv4(QString compatibleIpv6);
};

#endif  // UTIL_H
