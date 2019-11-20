#include "udp_server_handler.h"

UdpServerHandler::UdpServerHandler() {
  this->socket = new QUdpSocket(this);

  socket->bind(QHostAddress::AnyIPv4, BOARDCAST_PORT);

  connect(socket, &QUdpSocket::readyRead, this,
          &UdpServerHandler::receiveBoardcase);
}

UdpServerHandler::~UdpServerHandler() {
  delete this->socket;
}

/**
 * @brief UdpServer::receiveBoardcase 接收udp消息
 */
void UdpServerHandler::receiveBoardcase() {
  QByteArray datagram;
  while (socket->hasPendingDatagrams()) {
    datagram.resize(int(socket->pendingDatagramSize()));
    socket->readDatagram(datagram.data(), datagram.size());

    QString content(datagram);
    processDatagram(content);
  }
}

/**
 * @brief UdpServer::processTheDatagram 子类重写处理方法
 * @param s QString
 */
void UdpServerHandler::processDatagram(QString s) {
  qDebug() << s;
}
