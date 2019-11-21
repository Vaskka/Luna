#include "boardcast_service.h"

BoardcastService::BoardcastService() {}

/**
 * @brief BoardcastService::initService 初始化服务
 */
void BoardcastService::initService() {}

/**
 * @brief BoardcastService::runService 运行服务
 */
void BoardcastService::runService() {
  this->client = new UdpClient(LunaConstant::broadcastContent);
  this->server = new UdpServerHandler();

  /**
   * @brief connect 监听udpserver的回调消息
   */
  connect(this->server, &UdpServerHandler::processDatagram, this,
          &BoardcastService::dealBroadcastMessage);
}

/**
 * @brief BoardcastService::dealBroadcastMessage 处理广播消息
 * @param
 */
void BoardcastService::dealBroadcastMessage(QString ip, QString s) {
  // not correct return
  if (s != LunaConstant::broadcastContent) {
    return;
  }

  emit appendNewIp(ip);
}
