#include "tcp_client_handler.h"

TcpClient::TcpClient() {
  sock = new QTcpSocket();
}

/**
 * @brief send 发送数据给指定地址:端口
 * @param ipaddr ip
 * @param port 端口
 * @param msg 发送的数据
 */
void TcpClient::send(QString ipaddr, quint16 port, QString msg) {
  this->content = msg;

  // 连接
  sock->connectToHost(ipaddr, port);
  // 检测连接成功
  connect(this->sock, &QTcpSocket::connected, this, &TcpClient::connectSuccess);
}

/**
 * @brief Client::close 关闭连接
 */
void TcpClient::close() {
  sock->close();
}

/**
 * @brief connectSuccess 连接成功回调
 */
void TcpClient::connectSuccess() {
  QTcpSocket* dest = (QTcpSocket*)sender();

  // 读取服务端数据
  connect(sock, &QTcpSocket::readyRead, this, &TcpClient::readDataFromServer);
  // 检测掉线
  connect(sock, &QTcpSocket::disconnected, this,
          &TcpClient::clientDisconnected);

  qDebug() << "Success connected to " << dest->peerName() << " with "
           << dest->peerAddress() << "\n";

  sock->write(this->content.toUtf8());

  // 检测发送完毕
  connect(sock, &QTcpSocket::bytesWritten, this,
          &TcpClient::clientFinishedSendingData);
  // sock->flush();
}

/**
 * @brief readDataFromServer 从服务器读取数据
 */
void TcpClient::readDataFromServer() {
  QTcpSocket* socket = (QTcpSocket*)sender();
  QString s = socket->readAll();
  qDebug() << s << " from " << socket->peerAddress();
}

/**
 * @brief clientDisconnected 掉线回调
 */
void TcpClient::clientDisconnected() {
  QTcpSocket* dissocket = (QTcpSocket*)sender();

  qDebug() << "client " << dissocket->peerAddress() << " disconnected!\n";
}

/**
 * @brief clientFinishedSendingData 数据发送完毕
 */
void TcpClient::clientFinishedSendingData() {
  this->close();
}
