#include "tcp_server_handler.h"

TcpServerHandler::TcpServerHandler() {
  server = new TcpServer;

  // 同一tcp消息处理回调
  connect(this, &TcpServerHandler::serverReceived, this,
          &TcpServerHandler::serverReceivedHandler);

  // listening
  if (!server->listen(QHostAddress::Any, TRANS_PORT)) {
    qDebug() << server->errorString();
    return;
  }

  // 连接回调
  connect(server, &TcpServer::ClientConnected, this,
          &TcpServerHandler::clientConnected);

  // 掉线回调
  connect(server, &TcpServer::ClientDisconnected, this,
          &TcpServerHandler::clientDisconnected);
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
  QString* s = new QString(data);
  qDebug() << "received:" << *s;
}

void TcpServerHandler::clientConnected(qintptr desc, QTcpSocket* socket) {
  // test
  qDebug() << desc << " is connected\n";

  // 出发处理内容的回调
  connect(socket, &QTcpSocket::readyRead,
          [=] { emit serverReceived(desc, socket, socket->readAll()); });
}

void TcpServerHandler::clientDisconnected(qintptr desc) {
  qDebug() << desc << " is disconnected";
}

TcpServerHandler::~TcpServerHandler() {
  server->close();
}
