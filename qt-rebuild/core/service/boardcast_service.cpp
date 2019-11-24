#include "boardcast_service.h"

QString BoardcastService::getUsername() const {
  return username;
}

void BoardcastService::setUsername(const QString& value) {
  username = value;
}

BoardcastService::BoardcastService(QString username) {
  this->username = username;
}

/**
 * @brief BoardcastService::initService 初始化服务
 */
void BoardcastService::initService() {}

/**
 * @brief BoardcastService::runService 运行服务
 */
void BoardcastService::runService() {
  QString btext;

  btext.append(LunaConstant::broadcastContent);
  btext.append("\n");
  btext.append(this->username);

  this->client = new UdpClient(btext);
  this->server = new UdpServerHandler();

  /**
   * @brief connect 监听udpserver的回调消息
   */
  connect(this->server, &UdpServerHandler::processDatagram, this,
          &BoardcastService::dealBroadcastMessage);
}

void BoardcastService::destoryService() {
  delete this->client;
  delete this->server;
}

/**
 * @brief BoardcastService::dealBroadcastMessage 处理广播消息
 * @param
 */
void BoardcastService::dealBroadcastMessage(QString ip, QString s) {
  // not correct return
  QStringList sl = s.split('\n');

  if (s.length() != 2 && sl[0] != LunaConstant::broadcastContent) {
    return;
  }

  emit appendNewIp(ip, sl[1]);
}
