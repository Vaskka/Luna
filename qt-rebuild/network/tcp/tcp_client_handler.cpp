#include "tcp_client_handler.h"

TcpClient::TcpClient() {
  sock = new QTcpSocket();
  connect(this->sock, &QTcpSocket::connected, this, &TcpClient::connectSuccess);
}

TcpClient::~TcpClient() {
  this->close();
}

/**
 * @brief send 发送数据给指定地址:端口
 * @param ipaddr ip
 * @param port 端口
 * @param msg 发送的数据
 */
void TcpClient::send(QString ipaddr, quint16 port, QString& msg) {
  this->content = msg;

  // 连接
  if (sock->state() == QAbstractSocket::SocketState::UnconnectedState) {
    sock->connectToHost(ipaddr, port);
  }

  // 检测连接成功
  this->sock->waitForConnected();
}

/**
 * @brief Client::close 关闭连接
 */
void TcpClient::close() {
  sock->flush();
  sock->close();
}

/**
 * @brief connectSuccess 连接成功回调
 */
void TcpClient::connectSuccess() {
  // 读取服务端数据
  connect(sock, &QTcpSocket::readyRead, this, &TcpClient::readDataFromServer);
  // 检测掉线
  connect(sock, &QTcpSocket::disconnected, this,
          &TcpClient::clientDisconnected);

  sock->write(this->content.toUtf8());

  // 检测发送完毕
  connect(sock, &QTcpSocket::bytesWritten, this,
          &TcpClient::clientFinishedSendingData);
  this->sock->waitForBytesWritten();
}

/**
 * @brief readDataFromServer 从服务器读取数据
 */
void TcpClient::readDataFromServer() {}

/**
 * @brief clientDisconnected 掉线回调
 */
void TcpClient::clientDisconnected() {}

/**
 * @brief clientFinishedSendingData 数据发送完毕
 */
void TcpClient::clientFinishedSendingData() {
  this->close();
}
