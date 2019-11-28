#include "luna_core.h"

/**
 * @brief LunaCore::init 初始化、启动服务
 */
void LunaCore::init() {
  // 分配内存
  this->boardcastService = new BoardcastService(this->username);
  this->controlService = new FileControlService;
  this->transferService = new FileTransferService;
  this->aliveNodeService = new AliveNodesService;
  this->auth = new Authorize(LunaConstant::TOKEN_TIMEOUT_MSEC);

  // init service
  this->boardcastService->initService();
  this->controlService->initService();
  this->transferService->initService();

  // run service
  this->boardcastService->runService();
  this->controlService->runService();
  this->transferService->runService();

  /* connect */
  // 广播发现
  connect(this->boardcastService, &BoardcastService::appendNewIp, this,
          &LunaCore::dealBoardcastFound);

  // 文件暴露
  connect(this->controlService,
          &FileControlService::receiveValidFileTransferExposure, this,
          &LunaCore::dealExposureComing);

  // 请求传输
  connect(this->controlService, &FileControlService::receiveTransferRequest,
          this, &LunaCore::dealRequestComing);

  // 传输拒绝
  connect(this->controlService, &FileControlService::receiveFileTransferDeny,
          this, &LunaCore::dealTransferDeny);

  // 处理异常
  connect(this->controlService, &FileControlService::receiveError, this,
          &LunaCore::dealError);

  // 正在发送
  connect(this->transferService, &FileTransferService::fileSending, this,
          &LunaCore::fileSending);

  // 文件到达
  connect(this->transferService, &FileTransferService::getTransferComfirm, this,
          &LunaCore::receiveFileContent);
}

/**
 * @brief LunaCore::LunaCore 默认构造
 * @param parent parent
 * @param username 'LunaNode'
 */
LunaCore::LunaCore(QObject* parent, QString username) : QObject(parent) {
  this->username = username;
  this->init();
}

/**
 * @brief LunaCore::LunaCore 指定 用户名的构造
 * @param username username
 */
LunaCore::LunaCore(QString username) {
  this->username = username;
  this->init();
}

/**
 * @brief LunaCore::~LunaCore 析构
 */
LunaCore::~LunaCore() {
  this->controlService->destoryService();
  this->transferService->destoryService();
  this->boardcastService->destoryService();

  delete this->auth;
  delete this->controlService;
  delete this->transferService;
  delete this->boardcastService;
  delete this->aliveNodeService;
}

/**
 * @brief sendFileExposure 发送文件暴露
 * @param ip ip
 * @param username username
 * @param path path
 * @param token token
 */
void LunaCore::sendFileExposure(QString ip, QString username, QString path) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);

  if (!this->getAliveNodeMap()->contains(
          AliveNode::getIdentifyKey(realIp, username))) {
    emit this->opError("用户不存在，请选择先选择一个用户");
  }

  // 向鉴权中心申请唯一token
  QString token = this->auth->applyUniqueToken(realIp, username, path);

  // 传输控制层 执行发送
  this->controlService->sendFileExposure(realIp, username, path, token);
}

/**
 * @brief sendFileRequest 发送文件请求
 * @param ip ip
 * @param username username
 * @param token token
 * @param path path
 */
void LunaCore::sendFileRequest(QString ip, QString username, QString path) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);

  // 使用活跃节点管理服务搜索相应的token
  QString token = this->aliveNodeService->searchToken(realIp, username, path);

  // 传输控制层 执行发送
  this->controlService->sendFileRequest(realIp, username, token, path);
}

/**
 * @brief sendFileComfirm 发送文件内容
 * @param ip ip
 * @param username username
 * @param path path
 */
void LunaCore::sendFileContent(const QString ip,
                               const QString username,
                               const QString path) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);

  QFile file(path);

  // try to read file content
  if (!file.open(QFile::ReadOnly)) {
    QString errMsg;
    errMsg += ("Read file:" + path + "error.");
    qDebug() << errMsg;
    emit opError(errMsg);
  }

  // read file contemt
  QByteArray data = file.readAll();

  this->transferService->sendFileComfirm(realIp, username, path, data.data());
}

/**
 * @brief sendTransferDeny 否认传输(鉴权失败和用户手动均可调用此方法)
 * @param ip ip
 * @param username username
 */
void LunaCore::sendTransferDeny(QString ip,
                                QString username,
                                LunaConstant::ExceptionType exception) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);

  this->controlService->sendTransferDeny(realIp, username, exception);
}

/**
 * @brief getUsername 获取用户名
 * @return
 */
QString LunaCore::getUsername() const {
  return username;
}

/**
 * @brief setUsername 设置用户名
 * @param value
 */
void LunaCore::setUsername(const QString& value) {
  username = value;
}

/**
 * @brief getAliveNodeMap 获得活跃节点映射表
 * @return QMap&lt;QString, AliveNode*&gt;
 */
QMap<QString, AliveNode*>* LunaCore::getAliveNodeMap() const {
  return this->aliveNodeService->getMap();
}

/**
 * @brief fromUsernameSearchIp 根据username查找对应ip
 * @param username username
 * @return QString ip
 */
QString LunaCore::fromUsernameSearchIp(const QString username) const {
  for (AliveNode* node : this->getAliveNodeMap()->values()) {
    if (node->getUsername() == username) {
      return node->getIp();
    }
  }

  return QString();
}

/**
 * @brief dealComingExposure 处理文件暴露
 * @param ip ip
 * @param username username
 * @param path path
 * @param token token
 */
void LunaCore::dealExposureComing(QString ip,
                                  QString username,
                                  QString path,
                                  QString token) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);

  this->aliveNodeService->insertPathAndTokenInfo(realIp, username, path, token);

  // 通知并向上层隐藏token
  emit receiveFileExposure(realIp, username, path);
}

/**
 * @brief dealComingRequest 处理文件请求-完成token鉴权
 * @param ip ip
 * @param username username
 * @param path path
 * @param token token
 */
void LunaCore::dealRequestComing(QString ip,
                                 QString username,
                                 QString path,
                                 QString token) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);

  // 鉴权失败直接deny
  if (!this->auth->checkIfTokenValid(token)) {
    this->sendTransferDeny(realIp, username,
                           LunaConstant::ExceptionType::AuthError);
    return;
  }

  // 鉴权成功隐藏token通知上层
  emit requestPassAuthorize(realIp, username, path);
}

/**
 * @brief dealTransferDeny 处理传输拒绝的消息
 * @param ip ip
 * @param username username
 * @param originPath path
 */
void LunaCore::dealTransferDeny(QString ip,
                                QString username,
                                QString originPath) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);

  emit receiveTransferDeny(realIp, username, originPath);
}

/**
 * @brief dealFileContentComing 处理文件内容到达
 * @param ip ip
 * @param username username
 * @param name name
 * @param fileContent file-byte-content
 */
void LunaCore::dealFileContentComing(QString ip,
                                     QString username,
                                     QString name,
                                     const QByteArray& fileContent) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);
  // 通知上层
  emit receiveFileContent(realIp, username, name, fileContent);
}

/**
 * @brief dealBoardcastFound
 * 处理广播到达-对比当前列表-如果是新节点发送findNewNode的信号
 * @param ip ip
 * @param username username
 */
void LunaCore::dealBoardcastFound(QString ip, QString username) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);
  if (this->aliveNodeService->insertAliveMakeSureUnique(realIp, username)) {
    emit findNewNode(realIp, username);
  }
}

/**
 * @brief dealFileSending 处理文件正在发送
 * @param ip ip
 * @param username username
 */
void LunaCore::dealFileSending(QString ip, QString username) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);
  emit fileSending(realIp, username);
}

/**
 * @brief dealError 接收到异常消息
 * @param ip ip
 * @param username username
 * @param exception 异常类型
 */
void LunaCore::dealError(QString ip,
                         QString username,
                         LunaConstant::ExceptionType exception) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);
  emit receiveError(realIp, username, exception);
}
