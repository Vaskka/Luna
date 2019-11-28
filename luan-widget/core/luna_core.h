#ifndef LUNACORE_H
#define LUNACORE_H

#include <QMap>
#include <QObject>

#include "../auth/authorize.h"
#include "common.h"
#include "service/alive_nodes_service.h"
#include "service/boardcast_service.h"
#include "service/file_control_service.h"
#include "service/file_transfer_service.h"

class LunaCore : public QObject {
  Q_OBJECT

 private:
  /**
   * @brief username username
   */
  QString username;

  /**
   * @brief auth 鉴权中心
   */
  Authorize* auth;

  /**
   * @brief controlService 传输控制服务
   */
  FileControlService* controlService;

  /**
   * @brief transferService 文件传输服务
   */
  FileTransferService* transferService;

  /**
   * @brief boardcastService 广播发现服务
   */
  BoardcastService* boardcastService;

  /**
   * @brief aliveNodeService 可用节点服务
   */
  AliveNodesService* aliveNodeService;

 private:
  /**
   * @brief init 启动服务等
   */
  void init();

 public:
  /**
   * @brief LunaCore 默认构造
   * @param parent parent
   * @param username 'LunaNode'
   */
  explicit LunaCore(QObject* parent = nullptr, QString username = "LunaNode");

  /**
   * @brief LunaCore
   * @param username 指定username的构造
   */
  explicit LunaCore(QString username);

  /**
   * 析构
   */
  ~LunaCore();

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
   */
  void sendFileContent(const QString ip,
                       const QString username,
                       const QString path);

  /**
   * @brief sendTransferDeny 否认传输(鉴权失败和用户手动均可调用此方法)
   * @param ip ip
   * @param username username
   */
  void sendTransferDeny(QString ip,
                        QString username,
                        LunaConstant::ExceptionType exception =
                            LunaConstant::ExceptionType::None);

  /**
   * @brief getUsername 获取用户名
   * @return
   */
  QString getUsername() const;

  /**
   * @brief setUsername 设置用户名
   * @param value
   */
  void setUsername(const QString& value);

  /**
   * @brief getAliveNodeMap 获得活跃节点映射表
   * @return QMap&lt;QString, AliveNode*&gt;
   */
  QMap<QString, AliveNode*>* getAliveNodeMap() const;

  /**
   * @brief fromUsernameSearchIp 根据username查找对应ip
   * @param username username
   * @return QString ip
   */
  QString fromUsernameSearchIp(const QString username) const;

 signals:

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

  /**
   * @brief opError 接口调用错误(后期需要改成异常类型可供枚举)
   * @param errorMsg 提示上层显示给用户的信息
   */
  void opError(QString errorMsg);

 private slots:

  /**
   * @brief dealComingExposure 处理文件暴露
   * @param ip ip
   * @param username username
   * @param path path
   * @param token token
   */
  void dealExposureComing(QString ip,
                          QString username,
                          QString path,
                          QString token);

  /**
   * @brief dealComingRequest 处理文件请求-完成token鉴权
   * @param ip ip
   * @param username username
   * @param path path
   * @param token token
   */
  void dealRequestComing(QString ip,
                         QString username,
                         QString path,
                         QString token);

  /**
   * @brief dealTransferDeny 处理传输拒绝的消息
   * @param ip ip
   * @param username username
   * @param originPath path
   */
  void dealTransferDeny(QString ip, QString username, QString originPath);

  /**
   * @brief dealFileContentComing 处理文件内容到达
   * @param ip ip
   * @param username username
   * @param name name
   * @param fileContent file-byte-content
   */
  void dealFileContentComing(QString ip,
                             QString username,
                             QString name,
                             const QByteArray& fileContent);
  /**
   * @brief dealBoardcastFound
   * 处理广播到达-对比当前列表-如果是新节点发送findNewNode的信号
   * @param ip ip
   * @param username username
   */
  void dealBoardcastFound(QString ip, QString username);

  /**
   * @brief dealFileSending 处理文件正在发送
   * @param ip ip
   * @param username username
   */
  void dealFileSending(QString ip, QString username);

  /**
   * @brief dealError 接收到异常消息
   * @param ip ip
   * @param username username
   * @param exception 异常类型
   */
  void dealError(QString ip,
                 QString username,
                 LunaConstant::ExceptionType exception);
};

#endif  // LUNACORE_H
