#ifndef ALIVENODESSERVICE_H
#define ALIVENODESSERVICE_H

#include <utils/util.h>

#include <QCryptographicHash>
#include <QDateTime>
#include <QLinkedList>
#include <QMap>
#include <QObject>

/**
 * @brief The FileUnit class 标识一次文件传输
 */
class FileUnit {
 public:
  FileUnit(QString path, QString token, QDateTime createTime);

  /* getter and setter */
  QString getPath() const;
  void setPath(const QString& value);

  QString getToken() const;
  void setToken(const QString& value);

  QDateTime getCreateTime() const;
  void setCreateTime(const QDateTime& value);

 private:
  QString path;
  QString token;
  QDateTime createTime;
  /**
   * @brief isTransfer 是否接收过
   */
  bool isTransfer = false;
};

/**
 * @brief The AliveNode class 包含token信息的节点
 */
class AliveNode {
 private:
  QString ip;
  QString username;

  QLinkedList<FileUnit*>* transferList;

 public:
  /* 限制构造只能通过不设置token和path的方式 */
  AliveNode(QString ip, QString username);

  /**
   * @brief appendTransferUnit 增长一个tranfer-unit
   * @param path path
   * @param token token
   */
  void appendTransferUnit(QString path, QString token);

  /**
   * @brief getIdentifyKey  获取唯一标识key
   * @param ip ip
   * @param username username
   * @return QString
   */
  static QString getIdentifyKey(QString ip, QString username);

  /* getter and setter */
  QString getIp() const;
  QString getUsername() const;

  QLinkedList<FileUnit*>* getTransferList() const;
};

/**
 * @brief The AliveNodesService class 管理当前可用的节点,
 * 使用内存中的dict结构代替sqlite, 由于需要频繁搜索，使用QMap
 * TODO: 使用database存储当前节点状态，ip, path, token, username, createtime,
 */
class AliveNodesService {
 private:
  /**
   * @brief set 存储节点的set
   */
  QMap<QString, AliveNode*>* map;

 private:
  /*  method */

  /**
   * @brief doInsert 内部插入map方法
   * @param node 要插入的node的 引用
   */
  void doInsert(AliveNode& node);

  /**
   * @brief doUpdatePathAndToken 内部搜索指定id的node并更新path和token
   * @param identifyId 指定id
   * @param path path
   * @param token token
   */
  void doAppendPathAndToken(QString identify, QString path, QString token);

 public:
  /* 初始化服务，分配空间 */
  AliveNodesService();

  /**
   * @brief insertAliveAfterSearchTheSame 如果不存在唯一的ip, username插入
   * @param ip ip
   * @param username username
   * @return bool
   */
  bool insertAliveMakeSureUnique(const QString ip, const QString username);

  /**
   * @brief insertPathAndTokenInfo 插入指定ip和username的 path, token信息
   * @param ip ip
   * @param username username
   * @param path path
   * @param token token
   */
  void insertPathAndTokenInfo(const QString ip,
                              const QString username,
                              const QString path,
                              const QString token);

  /**
   * @brief getNodeFromIpAndUsername 根据 ip和username 搜索Alivenode
   * @param ip ip
   * @param username username
   * @return AliveNode*
   */
  AliveNode* getNodeFromIpAndUsername(const QString ip, const QString username);

  /**
   * @brief getMap 得到可以向上层暴露的节点map的getter
   * @return
   */
  QMap<QString, AliveNode*>* getMap() const;

  /**
   * @brief searchToken  搜索ip-username对应path的token
   * @param ip ip
   * @param username username
   * @param path path
   * @return QString
   */
  QString searchToken(QString ip, QString username, QString path);
};

#endif  // ALIVENODESSERVICE_H
