#ifndef FILECONTROLSERVICE_H
#define FILECONTROLSERVICE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

#include "../../network/tcp/tcp_client_handler.h"
#include "../../network/tcp/tcp_server_handler.h"
#include "common.h"

/**
 * @brief The FileControlService class 监听和发送文件控制信息
 */
class FileControlService : public QObject {
  Q_OBJECT

 signals:

  /**
   * @brief getValidFileTransferExposure 接收到有可传输的文件的暴露信息
   * @param ip 目标ip
   * @param username username
   * @param path 路径
   * @param token 可用的鉴权token
   */
  void receiveValidFileTransferExposure(QString ip,
                                        QString username,
                                        QString path,
                                        QString token);

  /**
   * @brief receiveTransferRequest 接收到文件传输请求
   * @param ip ip
   * @param username username
   * @param path path
   * @param token token
   */
  void receiveTransferRequest(QString ip,
                              QString username,
                              QString path,
                              QString token);

  /**
   * @brief getTransferDeny 接收到传输拒绝的消息
   * @param ip ip
   * @param username username
   * @param originPath path
   */
  void receiveFileTransferDeny(QString ip,
                               QString username,
                               QString originPath);

  /**
   * @brief receiveError 接收到异常消息
   * @param ip ip
   * @param username username
   * @param exception 异常类型
   */
  void receiveError(QString ip,
                    QString username,
                    LunaConstant::ExceptionType exception);

  /**
   * @brief jsonParseError json 解析异常
   * @param errorData 异常内容
   */
  void jsonParseError(const QByteArray& errorData);

 private:
  TcpClient* client;
  TcpServerHandler* server;

  /**
   * @brief checkJsonValueValid 检查json格式
   * @param value QJSonValue
   */
  bool checkJsonValueValid(const QJsonValue& value, const QByteArray& data);

 public:
  explicit FileControlService(QObject* parent = nullptr);

  /**
   * @brief sendTransferDeny 发送传输否定
   * @param ip
   * @param username username
   */
  void sendTransferDeny(QString ip,
                        QString username,
                        LunaConstant::ExceptionType exception =
                            LunaConstant::ExceptionType::None);

  /**
   * @brief sendFileExposure 发送文件暴露
   * @param ip ip
   * @param username username
   * @param path path
   * @param token token
   */
  void sendFileExposure(QString ip,
                        QString username,
                        QString path,
                        QString token);

  /**
   * @brief sendFileRequest 发送文件请求
   * @param ip ip
   * @param username username
   * @param token token
   * @param path path
   */
  void sendFileRequest(QString ip,
                       QString username,
                       QString token,
                       QString path);

  /**
   * @brief initService 初始化service
   */
  void initService();

  /**
   * @brief runService 运行service
   */
  void runService();

  /**
   * @brief destoryService 销毁service释放内部内存
   */
  void destoryService();

 private slots:

  /**
   * @brief dealTcpServerReceive 处理Tcp接收到的信息
   * @param data byte-array
   */
  void dealTcpServerReceive(const QString ip, const QByteArray& data);
};

#endif  // FILECONTROLSERVICE_H
