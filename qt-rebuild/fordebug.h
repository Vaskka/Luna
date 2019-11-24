#ifndef FORDEBUG_H
#define FORDEBUG_H

#include <QObject>
#include <QSet>

#include "core/service/boardcast_service.h"
#include "core/service/file_control_service.h"
#include "core/service/file_transfer_service.h"

class ForDebug : public QObject {
  Q_OBJECT

 private:
  QSet<QString> set;

  BoardcastService* service;

 public:
  explicit ForDebug();

  void sendBC();

  void sendExp(QString ip, QString path, QString token);

  void sendDeny(QString ip);

  void debugSendFileComfirm(const QString ip,
                            const QString path,
                            const QByteArray& data);

 public slots:

  void debugAppendNewIp(QString ip, QString username);

  void debugReceiveValidFileTransferExposure(QString ip,
                                             QString path,
                                             QString token);
  void debugReceiveTransferRequest(QString ip, QString path, QString token);
  void debugReceiveFileTransferDeny(QString ip, QString originPath);

  void debugReceiveError(QString ip, LunaConstant::ExceptionType exception);
  void debugJsonParseError(const QByteArray& errorData);

  void debugGetTransferComfirm(QString ip,
                               QString name,
                               const QByteArray& fileContent);

  void debugFileSending(QString ip);
};

#endif  // FORDEBUG_H
