#ifndef FILETRANSFERSERVICE_H
#define FILETRANSFERSERVICE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

#include "../../common.h"
#include "../../network/tcp/tcp_client_handler.h"
#include "../../network/tcp/tcp_server_handler.h"
#include "../../utils/util.h"

class FileTransferService : public QObject {
  Q_OBJECT

 private:
  TcpClient* client;

  TcpServerHandler* server;

 signals:

  /**
   * @brief getTransferComfirm 暴露给用户的回调
   * @param ip ip
   * @param username username
   * @param name 文件名
   * @param fileContent 文件内容(real file content)
   */
  void getTransferComfirm(QString ip,
                          QString username,
                          QString name,
                          const QByteArray& fileContent);

  /**
   * @brief getFileSent 文件正在发送
   * @param ip ip
   * @param username username
   */
  void fileSending(QString ip, QString username);

  /**
   * @brief jsonParseError json 解析异常
   * @param errorData 异常内容
   */
  void jsonParseError(const QByteArray& errorData);

 public:
  explicit FileTransferService(QObject* parent = nullptr);

  /**
   * @brief sendFileComfirm 发送文件内容
   * @param ip ip
   * @param username username
   * @param path path
   * @param data data
   */
  void sendFileComfirm(const QString ip,
                       const QString username,
                       const QString path,
                       const QByteArray& data);

 public:
  void initService();

  void runService();

  void destoryService();

 private slots:
  /**
   * @brief dealFileContentArrive 文件内容到达
   * @param ip ip
   * @param data data
   */
  void dealFileContentArrive(const QString ip, const QByteArray& data);

  /**
   * @brief checkJsonValueValid 检查json格式
   * @param value QJSonValue
   */
  bool checkJsonValueValid(const QJsonValue& value, const QByteArray& data);
};

#endif  // FILETRANSFERSERVICE_H
