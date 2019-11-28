#include "alive_nodes_service.h"

/**
 * @brief AliveNodesService::doInsert 内部插入方法
 * @param node 要插入的node的引用
 */
void AliveNodesService::doInsert(AliveNode& node) {
  QString id = AliveNode::getIdentifyKey(node.getIp(), node.getUsername());
  this->map->insert(id, &node);
}

/**
 * @brief doAppendPathAndToken 内部搜索指定id的node并更新path和token
 * @param identifyId 指定id
 * @param path path
 * @param token token
 */
void AliveNodesService::doAppendPathAndToken(QString identify,
                                             QString path,
                                             QString token) {
  // update map
  if (map->contains(identify)) {
    AliveNode* node = (*(this->map))[identify];
    node->appendTransferUnit(path, token);
  }
}

/**
 * @brief AliveNodesService::AliveNodesService  service-construct
 */
AliveNodesService::AliveNodesService() {
  this->map = new QMap<QString, AliveNode*>();
}

/**
 * @brief insertAliveAfterSearchTheSame 如果不存在唯一的ip, username插入
 * @param ip ip
 * @param username username
 * @return bool 插入成功返回true
 */
bool AliveNodesService::insertAliveMakeSureUnique(const QString ip,
                                                  const QString username) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);
  AliveNode* newNode = new AliveNode(realIp, username);
  QString newNodeId =
      AliveNode::getIdentifyKey(newNode->getIp(), newNode->getUsername());

  // 不存在插入
  if (map->contains(newNodeId)) {
    return false;
  } else {
    this->doInsert(*newNode);
  }

  return true;
}

/**
 * @brief insertPathAndTokenInfo 插入指定ip和username的 path, token信息
 * @param ip ip
 * @param username username
 * @param path path
 * @param token token
 */
void AliveNodesService::insertPathAndTokenInfo(const QString ip,
                                               const QString username,
                                               const QString path,
                                               const QString token) {
  QString identify = AliveNode::getIdentifyKey(ip, username);

  // 搜索 node 设置其path和token，没搜索到直接为其增加新的值
  this->doAppendPathAndToken(identify, path, token);

  AliveNode* newNode = new AliveNode(ip, username);
  newNode->appendTransferUnit(path, token);

  this->doInsert(*newNode);
}

/**
 * @brief getNodeFromIpAndUsername 根据 ip和username 搜索Alivenode
 * @param ip ip
 * @param username username
 * @return AliveNode*
 */
AliveNode* AliveNodesService::getNodeFromIpAndUsername(const QString ip,
                                                       const QString username) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);
  QString id = AliveNode::getIdentifyKey(realIp, username);

  if (this->map->contains(id)) {
    return (*(this->map))[id];
  }

  return nullptr;
}

/**
 * @brief AliveNodesService::getMap 得到活跃节点的Map
 * @return QMap&lt;QString, AliveNode*&gt; map
 */
QMap<QString, AliveNode*>* AliveNodesService::getMap() const {
  return this->map;
}

/**
 * @brief searchToken  搜索ip-username对应path的token
 * @param ip ip
 * @param username username
 * @param path path
 * @return QString
 */
QString AliveNodesService::searchToken(QString ip,
                                       QString username,
                                       QString path) {
  QString realIp = Util::changeCompatibleIpv6ToIpv4(ip);
  QString id = AliveNode::getIdentifyKey(realIp, username);

  if (this->map->contains(id)) {
    AliveNode node = *(*(this->map))[id];

    QLinkedList<FileUnit*>* innerList = node.getTransferList();

    QLinkedListIterator<FileUnit*> it(*innerList);
    while (it.hasNext()) {
      FileUnit* unit = it.next();
      if (unit->getPath() == path) {
        return unit->getToken();
      }
    }
  }

  // 没找到返回空字
  return QString("");
}

/* getter and setter */
QString AliveNode::getUsername() const {
  return username;
}

QString AliveNode::getIp() const {
  return ip;
}

/**
 * @brief AliveNode::getIdentifyKey 计算唯一id，sha1(ip + '-LunaNode-' +
 * username)
 * @param ip ip
 * @param username username
 * @return QString key
 */
QLinkedList<FileUnit*>* AliveNode::getTransferList() const {
  return transferList;
}

/**
 * @brief appendTransferUnit 增长一个tranfer-unit
 * @param path path
 * @param token token
 */
AliveNode::AliveNode(QString ip, QString username) {
  this->ip = Util::changeCompatibleIpv6ToIpv4(ip);
  this->username = username;
  this->transferList = new QLinkedList<FileUnit*>;
}

/**
 * @brief AliveNode::appendTransferUnit 增长一个transfer-unit
 * @param path path
 * @param token token
 */
void AliveNode::appendTransferUnit(QString path, QString token) {
  FileUnit* unit =
      new FileUnit(path, token, QDateTime::currentDateTime().toUTC());

  this->transferList->append(unit);
}

/**
 * @brief AliveNode::getIdentifyKey sha1(ip + '-LunaNode-' + username)
 * @param ip
 * @param username
 * @return
 */
QString AliveNode::getIdentifyKey(QString ip, QString username) {
  // sha1(ip + '-LunaNode-' + username)
  QString payload(ip);
  payload.append("-LunaNode-");
  payload.append(username);

  // cal sha1
  QString result =
      QCryptographicHash::hash(payload.toUtf8(), QCryptographicHash::Sha1)
          .toHex();

  return result;
}

/**
 * @brief FileUnit::FileUnit 单次文件传送construct
 * @param path path
 * @param token token
 * @param createTime createTime
 */
FileUnit::FileUnit(QString path, QString token, QDateTime createTime) {
  this->path = path;
  this->token = token;
  this->createTime = createTime;
}

/* getter and setter */
QString FileUnit::getPath() const {
  return path;
}

void FileUnit::setPath(const QString& value) {
  path = value;
}

QString FileUnit::getToken() const {
  return token;
}

void FileUnit::setToken(const QString& value) {
  token = value;
}

QDateTime FileUnit::getCreateTime() const {
  return createTime;
}

void FileUnit::setCreateTime(const QDateTime& value) {
  createTime = value;
}
