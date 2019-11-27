#include "file_transfer_service.h"

FileTransferService::FileTransferService(QObject* parent) : QObject(parent) {}

/**
 * @brief sendFileComfirm 发送文件内容
 * @param ip ip
 * @param path path
 * @param data data
 */
void FileTransferService::sendFileComfirm(const QString ip,
                                          const QString username,
                                          const QString path,
                                          const QByteArray& data) {
  QString* fileContent = new QString(data.toBase64());
  QString paramToken("");

  QString result = LunaConstant::ProtocalTool::constructLunaProtocal(
      LunaConstant::ProtocalType::TransferData, username,
      LunaConstant::ProtocalCommand::ConfirmTransfer, paramToken,
      LunaConstant::ExceptionType::None, path, *fileContent);

  // send file content via tcp
  this->client->send(ip, LunaConstant::FILE_TRANSFER_PORT, result);

  // 文件发送回调
  emit fileSending(ip, username);
}

/**
 * @brief FileTransferService::initService 初始化服务，分配内存
 */
void FileTransferService::initService() {
  // 初始化客户端和服务端对象
  this->client = new TcpClient;
  this->server = new TcpServerHandler(LunaConstant::FILE_TRANSFER_PORT);

  // 连接回调以处理tcp接收到的消息
  connect(this->server, &TcpServerHandler::tcpReceived, this,
          &FileTransferService::dealFileContentArrive);
}

/**
 * @brief FileTransferService::runService 运行服务，开始监听
 */
void FileTransferService::runService() {}

/**
 * @brief FileTransferService::destoryService 销毁服务，释放内存
 */
void FileTransferService::destoryService() {
  delete this->client;
  delete this->server;
}

/**
 * @brief FileTransferService::dealFileContentArrive 处理文件内容到达
 * @param ip ip
 * @param data data
 */
void FileTransferService::dealFileContentArrive(const QString ip,
                                                const QByteArray& data) {
  QJsonParseError e;

  QJsonDocument doc = QJsonDocument::fromJson(data, &e);

  // json解析异常
  if (doc.isNull() || e.error != QJsonParseError::NoError) {
    qDebug() << "file transfer: service parse json error";
    return;
  }

  // 判断类型 获取 username
  QJsonObject root = doc.object();
  if (!checkJsonValueValid(root["type"], data) ||
      !checkJsonValueValid(root["type"], data)) {
    return;
  }

  int typeCode = root["type"].toInt();
  QString username = root["username"].toString();
  LunaConstant::ProtocalType realType =
      LunaConstant::ProtocalTool::fromCodeGetType(typeCode);

  // 协议中未定义代码
  if (realType == LunaConstant::ProtocalType::UnknowType) {
    qDebug() << "file transfer: protocal is unknow type(" << typeCode << ')';
    return;
  }

  // 非传输类型丢弃
  if (realType != LunaConstant::TransferData) {
    qDebug() << "file transfer: send control data in transfer port(type)";
    return;
  }

  // content
  if (!checkJsonValueValid(root["content"], data)) {
    return;
  }
  QJsonObject contentObj = root["content"].toObject();

  // 检查command, 非传输指令丢弃
  if (!checkJsonValueValid(contentObj["command"], data)) {
    return;
  }
  LunaConstant::ProtocalCommand command =
      LunaConstant::ProtocalTool::fromCodeGetCommand(
          contentObj["command"].toInt());
  if (command == LunaConstant::ProtocalCommand::UnknowCommand) {
    qDebug() << "file transfer: unknow command";
    return;
  }
  if (command != LunaConstant::ProtocalCommand::ConfirmTransfer) {
    qDebug() << "file transfer: send control command in content transfer port";
    return;
  }

  // 提取path，提取文件名，提取内容，通知文件已经准备就绪
  if (!checkJsonValueValid(contentObj["path"], data) ||
      !checkJsonValueValid(contentObj["data"], data)) {
    return;
  }
  QString path = contentObj["path"].toString();
  QString base64Content = contentObj["data"].toString();

  QString filename = Util::fromPathGetFileName(path);
  // base64 解码
  QByteArray fileContent = QByteArray::fromBase64(base64Content.toUtf8());

  // 文件就绪回调
  emit getTransferComfirm(ip, username, filename, fileContent);
}

/**
 * @brief FileTransferService::checkJsonValueValid 检查json值是否正常
 * @param value QJsonValue
 * @param data QByteArray
 * @return bool
 */
bool FileTransferService::checkJsonValueValid(const QJsonValue& value,
                                              const QByteArray& data) {
  if (value.isNull()) {
    emit jsonParseError(data);
    return false;
  }

  return true;
}
