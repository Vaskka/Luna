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
  quint16 receivePort;
  QHostAddress ipaddr;
  while (socket->hasPendingDatagrams()) {
    datagram.resize(int(socket->pendingDatagramSize()));
    socket->readDatagram(datagram.data(), datagram.size(), &ipaddr,
                         &receivePort);

    QString content = datagram;
    emit processDatagram(ipaddr.toString(), content);
  }
}
