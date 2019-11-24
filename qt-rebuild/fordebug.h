#ifndef FORDEBUG_H
#define FORDEBUG_H

#include <QObject>
#include <QSet>

#include "core/luna_core.h"

class ForDebug : public QObject {
  Q_OBJECT

 private:
  LunaCore* core;

 public:
  explicit ForDebug();

  /**
   * @brief sendFileExposure 发送文件暴露
   * @param ip ip
   * @param username username
   * @param path path
   * @param token token
   */
  void sendFileExposure(QString ip, QString username, QString path);

  /**
   * @brief sendFileRequest 发送文件请求
   * @param ip ip
   * @param username username
   * @param token token
   * @param path path
   */
  void sendFileRequest(QString ip, QString username, QString path);

  /**
   * @brief sendFileComfirm 发送文件内容
   * @param ip ip
   * @param username username
   * @param path path
   * @param data data
   */
  void sendFileContent(const QString ip,
                       const QString username,
                       const QString path,
                       const QByteArray& data);

  /**
   * @brief sendTransferDeny 否认传输(鉴权失败和用户手动均可调用此方法)
   * @param ip ip
   * @param username username
   */
  void sendTransferDeny(QString ip,
                        QString username,
                        LunaConstant::ExceptionType exception =
                            LunaConstant::ExceptionType::None);

  QMap<QString, AliveNode*>* getMap();

 public slots:

  /**
   * @brief appendNewIp 收到广播消息
   * @param ip ip
   * @param username username
   */
  void findNewNode(QString ip, QString username);

  /**
   * @brief getFileSent 文件正在发送
   * @param ip ip
   * @param username username
   */
  void fileSending(QString ip, QString username);

  /**
   * @brief getTransferComfirm 暴露给用户的回调
   * @param ip ip
   * @param username username
   * @param name 文件名
   * @param fileContent 文件内容(real file content)
   */
  void receiveFileContent(QString ip,
                          QString username,
                          QString name,
                          const QByteArray& fileContent);

  /**
   * @brief getValidFileTransferExposure 接收到有可传输的文件的暴露信息
   * @param ip 目标ip
   * @param username username
   * @param path 路径
   */
  void receiveFileExposure(QString ip, QString username, QString path);

  /**
   * @brief getTransferDeny 接收到传输拒绝的消息
   * @param ip ip
   * @param username username
   * @param originPath path
   */
  void receiveTransferDeny(QString ip, QString username, QString originPath);

  /**
   * @brief requestPassAuthorize 接收到的文件请求已经通过鉴权检验
   * @param ip ip
   * @param username username
   * @param path path
   */
  void requestPassAuthorize(QString ip, QString username, QString path);

  /**
   * @brief receiveError 接收到异常消息
   * @param ip ip
   * @param username username
   * @param exception 异常类型
   */
  void receiveError(QString ip,
                    QString username,
                    LunaConstant::ExceptionType exception);
};

#endif  // FORDEBUG_H
