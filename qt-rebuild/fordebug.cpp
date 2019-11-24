#include "fordebug.h"

ForDebug::ForDebug() : QObject() {
  this->service = new BoardcastService("asdasd");
  service->initService();
  service->runService();

  connect(this->service, &BoardcastService::appendNewIp, this,
          &ForDebug::debugAppendNewIp);
  //  connect(&this->service, &FileTransferService::getTransferComfirm, this,
  //          &ForDebug::debugGetTransferComfirm);

  //  connect(&this->service,
  //  &FileControlService::receiveValidFileTransferExposure,
  //          this, &ForDebug::debugReceiveValidFileTransferExposure);

  //  connect(&this->service, &FileControlService::receiveTransferRequest, this,
  //          &ForDebug::debugReceiveTransferRequest);

  //  connect(&this->service, &FileControlService::receiveFileTransferDeny,
  //  this,
  //          &ForDebug::debugReceiveFileTransferDeny);

  //  connect(&this->service, &FileControlService::receiveError, this,
  //          &ForDebug::debugReceiveError);
}

void ForDebug::sendBC() {}

void ForDebug::debugSendFileComfirm(const QString ip,
                                    const QString path,
                                    const QByteArray& data) {
  // this->service.sendFileComfirm(ip, path, data);
}

void ForDebug::debugAppendNewIp(QString ip, QString username) {
  qDebug() << "get ip:" << ip << " and username is:" << username;
}

// void ForDebug::sendExp(QString ip, QString path, QString token) {
//  this->service.sendFileExposure(ip, path, token);
//}

// void ForDebug::sendDeny(QString ip) {
//  this->service.sendTransferDeny(ip);
//}

void ForDebug::debugReceiveValidFileTransferExposure(QString ip,
                                                     QString path,
                                                     QString token) {
  qDebug() << "receive file transfer exposure with ip:" << ip
           << " path:" << path << " token:" << token;
}

void ForDebug::debugReceiveTransferRequest(QString ip,
                                           QString path,
                                           QString token) {
  qDebug() << "receive file transfer request with ip:" << ip << " path:" << path
           << " token:" << token;
}

void ForDebug::debugReceiveFileTransferDeny(QString ip, QString originPath) {
  qDebug() << "receive file transfer deny with ip:" << ip
           << " path:" << originPath;
}

void ForDebug::debugReceiveError(QString ip,
                                 LunaConstant::ExceptionType exception) {
  qDebug() << "receive file transfer error with ip:" << ip
           << " exception:" << exception;
}

void ForDebug::debugJsonParseError(const QByteArray& errorData) {
  qDebug() << "catch error:" << errorData;
}

/* file transfer */
void ForDebug::debugGetTransferComfirm(QString ip,
                                       QString name,
                                       const QByteArray& fileContent) {
  //  qDebug() << "get file content from " << ip << ":" << name << ":"
  //           << fileContent;

  QFile file("/Users/vaskka/Desktop/ttt/" + name);

  file.open(QFile::ReadWrite);

  file.write(fileContent);
}

void ForDebug::debugFileSending(QString ip) {
  qDebug() << "file is sending to " << ip;
}
