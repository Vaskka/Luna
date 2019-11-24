#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QHostAddress>
#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject {
  Q_OBJECT

 private:
  QTcpSocket* sock = nullptr;

  QString content;

  void close();

 public:
  TcpClient();

  ~TcpClient();

  void send(QString ipaddr, quint16 port, QString& msg);

 public slots:

  /**
   * @brief readDataFromServer 从服务器读取数据
   */
  void readDataFromServer();

  /**
   * @brief connectSuccess 连接成功回调
   */
  void connectSuccess();

  /**
   * @brief clientDisconnected 掉线回调
   */
  void clientDisconnected();

  /**
   * @brief clientFinishedSendingData 数据发送完毕
   */
  void clientFinishedSendingData();
};

#endif  // TCPCLIENT_H
