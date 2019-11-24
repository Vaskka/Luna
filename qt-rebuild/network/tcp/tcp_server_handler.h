#ifndef TCP_SERVER_HANDLER_H
#define TCP_SERVER_HANDLER_H

#include <QObject>
#include <QTcpSocket>

#include "tcp_server.h"

#define DEFAULT_TRANS_PORT 4002

class TcpServerHandler : public QObject {
  Q_OBJECT

 public:
  /**
   * @brief TcpServerHandler 创建一个指定端口号的监听
   * @param port 端口号
   */
  explicit TcpServerHandler(quint16 port);
  ~TcpServerHandler();

  quint16 getPort() const;

 signals:

  /**
   * @brief serverReceived 内部接口回调，可以用与log或debug
   */
  void serverReceived(qintptr, QTcpSocket*, const QByteArray&);

  /**
   * @brief tcpReceived 向外暴露的接口回调
   * @param data QByteArray& const
   */
  void tcpReceived(const QString ip, const QByteArray& data);

 private:
  TcpServer* server = nullptr;

  quint16 port;

 protected slots:
  void serverReceivedHandler(qintptr desc,
                             QTcpSocket* socketRef,
                             const QByteArray& data);
 public slots:
  void clientConnected(qintptr desc, QTcpSocket* socket);

  void clientDisconnected(qintptr desc);
};

#endif  // TCP_SERVER_HANDLER_H
