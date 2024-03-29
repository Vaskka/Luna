#include "udp_client_handler.h"

UdpClient::UdpClient(QString boardcaseContent) {
  this->boardcaseContent =
      new QByteArray(boardcaseContent.toStdString().c_str());
  this->socket = new QUdpSocket(this);

  this->timer = new QTimer;
  this->timer->start(1000);
  connect(timer, &QTimer::timeout, this, &UdpClient::processBoardcast);
}

/**
 * @brief UdpClient::~UdpClient 释放连接 释放timer
 */
UdpClient::~UdpClient() {
  this->timer->stop();
  delete this->timer;

  this->socket->close();
  delete this->socket;
}

/**
 * @brief UdpClient::processBoardcast 发送udp消息
 */
void UdpClient::processBoardcast() {
  qint64 len = socket->writeDatagram(*boardcaseContent, QHostAddress::Broadcast,
                                     BOARDCAST_PORT);

  if (len != this->boardcaseContent->length()) {
    return;
  }
}
