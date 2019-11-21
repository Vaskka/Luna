#ifndef LUNASERVICE_H
#define LUNASERVICE_H

#include <QObject>

#include "../../network/tcp/tcp_client_handler.h"
#include "../../network/tcp/tcp_server_handler.h"

class LunaService : public QObject {
  Q_OBJECT

 private:
  TcpClient* client;

  TcpServerHandler* server;

 signals:
  /**
   * @brief getValidFileTransferExposure 接收到有可传输的文件
   * @param ip 目标id
   * @param path 目标路径
   * @param token 鉴权token
   */
  void getValidFileTransferExposure(QString ip, QString path, QString token);

  /**
   * @brief getTransferComfirm 文件内容已经到达
   * @param ip ip
   * @param originPath 源path
   * @param fileContent 文件内容（base64编码之后）
   */
  void getTransferComfirm(QString ip, QString originPath, QString fileContent);

  /**
   * @brief getTransferDeny 传输拒绝
   * @param ip ip
   * @param originPath path
   */
  void getTransferDeny(QString ip, QString originPath);

 public:
  explicit LunaService(QObject* parent = nullptr);

  /**
   * @brief sendFileRequest search in database find token then send
   * @param ip ip
   * @param path path
   */
  void sendFileRequest(QString ip, QString path);

 public:
  void initService();

  void runService();

  void destoryService();

 public slots:
};

#endif  // LUNASERVICE_H
