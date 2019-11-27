#ifndef BOARDCASTSERVICE_H
#define BOARDCASTSERVICE_H

#include <QObject>
//#include <QThread>

#include "../../network/udp/udp_client_handler.h"
#include "../../network/udp/udp_server_handler.h"
#include "common.h"

/**
 * @brief The BoardcastService class 广播服务
 */
class BoardcastService : public QObject {
  Q_OBJECT

 signals:

  /**
   * @brief appendNewIp 收到广播消息
   * @param ip ip
   * @param username username
   */
  void appendNewIp(QString ip, QString username);

 private:
  UdpClient* client;

  UdpServerHandler* server;

  QString username;

 public:
  BoardcastService(QString username);

  void initService();

  void runService();

  void destoryService();

  QString getUsername() const;
  void setUsername(const QString& value);

 private slots:
  /**
   * @brief dealBroadcastMessage 处理广播消息
   * @param 广播内容
   */
  void dealBroadcastMessage(QString ip, QString content);
};

#endif  // BOARDCASTSERVICE_H
