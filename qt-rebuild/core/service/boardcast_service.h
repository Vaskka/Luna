#ifndef BOARDCASTSERVICE_H
#define BOARDCASTSERVICE_H

#include <QObject>
//#include <QThread>

#include "../../network/udp/udp_client_handler.h"
#include "../../network/udp/udp_server_handler.h"
#include "common.h"

///**
// * @brief The BroadcastThread class 广播发送线程
// */
// class BroadcastSendThread : public QThread {
// public:
//  BroadcastSendThread();

//  void run() override;
//};

///**
// * @brief The BroadcastReceiveThread class 广播接收线程
// */
// class BroadcastReceiveThread : public QThread {
// public:
//  BroadcastReceiveThread();

//  void run() override;
//};

/**
 * @brief The BoardcastService class 广播服务
 */
class BoardcastService : public QObject {
  Q_OBJECT

 signals:

  /**
   * @brief appendNewIp 收到广播消息
   * @param ip ip
   */
  void appendNewIp(QString ip);

 private:
  UdpClient* client;

  UdpServerHandler* server;

 public:
  BoardcastService();

  void initService();

  void runService();

  void destoryService();

 private slots:
  /**
   * @brief dealBroadcastMessage 处理广播消息
   * @param 广播内容
   */
  void dealBroadcastMessage(QString ip, QString content);
};

#endif  // BOARDCASTSERVICE_H
