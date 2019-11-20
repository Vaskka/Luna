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
 * @brief UdpClient::processBoardcast 发送udp消息
 */
void UdpClient::processBoardcast() {
  qint64 len = socket->writeDatagram(*boardcaseContent, QHostAddress::Broadcast,
                                     BOARDCAST_PORT);

  if (len != this->boardcaseContent->length()) {
    return;
  }

  QString s(*this->boardcaseContent);
  qDebug() << s;
}
