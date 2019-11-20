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

 public:
  explicit UdpServerHandler();

  ~UdpServerHandler();

 protected slots:
  void processDatagram(QString s);

 private slots:
  void receiveBoardcase();
};

#endif  // UPDSERVER_H
