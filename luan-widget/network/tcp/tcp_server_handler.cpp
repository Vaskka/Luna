#include "tcp_server_handler.h"

/**
 * @brief TcpServerHandler::TcpServerHandler 创建一个指定端口号的监听
 * @param port 端口号
 */
TcpServerHandler::TcpServerHandler(quint16 port) {
  // 0 为默认端口
  if (port == 0) {
    port = DEFAULT_TRANS_PORT;
  }
  this->port = port;

  server = new TcpServer;

  // 同一tcp消息处理回调
  connect(this, &TcpServerHandler::serverReceived, this,
          &TcpServerHandler::serverReceivedHandler, Qt::QueuedConnection);

  // listening
  if (!server->listen(QHostAddress::Any, port)) {
    return;
  }

  // 连接回调
  connect(server, &TcpServer::ClientConnected, this,
          &TcpServerHandler::clientConnected, Qt::QueuedConnection);

  // 掉线回调
  connect(server, &TcpServer::ClientDisconnected, this,
          &TcpServerHandler::clientDisconnected, Qt::QueuedConnection);
}

/**
 * @brief ServerHandler::serverReceivedHandler 处理tcp内容，上层可继承重写
 * @param desc socket标识
 * @param socketRef socket引用
 * @param data tcp字节流内容
 */
void TcpServerHandler::serverReceivedHandler(qintptr desc,
                                             QTcpSocket* socketRef,
                                             const QByteArray& data) {
  // QString* s = new QString(data);
  // qDebug() << "tcp " << getPort() << " received:" << *s;

  /* 可接入logger */

  // 外部可接入回调
  emit tcpReceived(socketRef->peerAddress().toString(), data);
}

void TcpServerHandler::clientConnected(qintptr desc, QTcpSocket* socket) {
  // 出发处理内容的回调
  connect(socket, &QTcpSocket::readyRead,
          [=] { emit serverReceived(desc, socket, socket->readAll()); });
}

void TcpServerHandler::clientDisconnected(qintptr desc) {}

TcpServerHandler::~TcpServerHandler() {
  server->close();
}

quint16 TcpServerHandler::getPort() const {
  return port;
}
