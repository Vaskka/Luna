#ifndef UPD_SERVER_HANDLER_H
#define UPD_SERVER_HANDLER_H

#include <QHostAddress>
#include <QNetworkDatagram>
#include <QObject>
#include <QUdpSocket>

#define BOARDCAST_PORT 4001

class UdpServerHandler : public QObject {
  Q_OBJECT

 private:
  QUdpSocket* socket;

 signals:
  void processDatagram(QString ip, QString s);

 public:
  explicit UdpServerHandler();

  ~UdpServerHandler();

 private slots:
  void receiveBoardcase();
};

#endif  // UPDSERVER_H
