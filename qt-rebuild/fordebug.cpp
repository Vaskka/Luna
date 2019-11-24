#include "fordebug.h"

ForDebug::ForDebug() : QObject() {
  this->core = new LunaCore("MyNode");

  connect(this->core, &LunaCore::receiveError, this, &ForDebug::receiveError);
  connect(this->core, &LunaCore::findNewNode, this, &ForDebug::findNewNode);
  connect(this->core, &LunaCore::fileSending, this, &ForDebug::fileSending);
  connect(this->core, &LunaCore::receiveFileContent, this,
          &ForDebug::receiveFileContent);
  connect(this->core, &LunaCore::receiveFileExposure, this,
          &ForDebug::receiveFileExposure);
  connect(this->core, &LunaCore::receiveTransferDeny, this,
          &ForDebug::receiveTransferDeny);

  connect(this->core, &LunaCore::requestPassAuthorize, this,
          &ForDebug::requestPassAuthorize);
}

void ForDebug::sendFileExposure(QString ip, QString username, QString path) {
  this->core->sendFileExposure(ip, username, path);
}

void ForDebug::sendFileRequest(QString ip, QString username, QString path) {
  this->core->sendFileRequest(ip, username, path);
}

void ForDebug::sendFileContent(const QString ip,
                               const QString username,
                               const QString path,
                               const QByteArray& data) {
  this->core->sendFileContent(ip, username, path, data);
}

void ForDebug::sendTransferDeny(QString ip,
                                QString username,
                                LunaConstant::ExceptionType exception) {
  this->core->sendTransferDeny(ip, username, exception);
}

QMap<QString, AliveNode*>* ForDebug::getMap() {
  return core->getAliveNodeMap();
}

void ForDebug::findNewNode(QString ip, QString username) {
  qDebug() << "find new node ip:" << ip << " username: " << username;
}

void ForDebug::fileSending(QString ip, QString username) {
  qDebug() << "file is sending to " << ip << " with " << username;
}

void ForDebug::receiveFileContent(QString ip,
                                  QString username,
                                  QString name,
                                  const QByteArray& fileContent) {
  qDebug() << "receive file content with ip:" << ip << " username:" << username
           << " filename:" << name;

  QFile file("/Users/vaskka/Desktop/ttt/" + name);
  file.open(QFile::WriteOnly);

  file.write(fileContent);
}

void ForDebug::receiveFileExposure(QString ip, QString username, QString path) {
  qDebug() << "find file exposure with ip:" << ip << " username:" << username
           << " path:" << path;
}

void ForDebug::receiveTransferDeny(QString ip,
                                   QString username,
                                   QString originPath) {
  qDebug() << "get transfer deny with ip:" << ip << " username:" << username
           << " path:" << originPath;
}

void ForDebug::requestPassAuthorize(QString ip,
                                    QString username,
                                    QString path) {
  qDebug() << "receive file request(already authorize): " << path
           << " with ip:" << ip << " username:" << username;
}

void ForDebug::receiveError(QString ip,
                            QString username,
                            LunaConstant::ExceptionType exception) {
  qDebug() << "receive Exception " << exception << " with ip:" << ip
           << " username:" << username;
}
