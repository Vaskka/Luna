#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QHostAddress>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>

#define BOARDCAST_PORT 4001

class UdpClient : public QObject {
  Q_OBJECT

 private:
  QUdpSocket* socket = nullptr;
  QByteArray* boardcaseContent = nullptr;
  QTimer* timer = nullptr;

 protected slots:
  void processBoardcast();

 public:
  explicit UdpClient(QString boardcaseContent);
};

#endif  // UDPCLIENT_H
