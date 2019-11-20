#ifndef TCP_SERVER_HANDLER_H
#define TCP_SERVER_HANDLER_H

#include <QObject>
#include <QTcpSocket>

#include "tcp_server.h"

#define TRANS_PORT 4002

class TcpServerHandler : public QObject {
  Q_OBJECT

 public:
  explicit TcpServerHandler();
  ~TcpServerHandler();

 signals:
  void serverReceived(qintptr, QTcpSocket*, const QByteArray&);

 private:
  TcpServer* server = nullptr;

 protected slots:
  void serverReceivedHandler(qintptr desc,
                             QTcpSocket* socketRef,
                             const QByteArray& data);
 public slots:
  void clientConnected(qintptr desc, QTcpSocket* socket);

  void clientDisconnected(qintptr desc);
};

#endif  // TCP_SERVER_HANDLER_H
