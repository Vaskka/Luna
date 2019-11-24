#include "file_control_service.h"

/**
 * @brief FileControlService::checkJsonValueValid 检查json格式
 * @param value
 * @param data
 */
bool FileControlService::checkJsonValueValid(const QJsonValue& value,
                                             const QByteArray& data) {
  if (value.isNull()) {
    emit jsonParseError(data);
    return false;
  }

  return true;
}

/**
 * @brief FileControlService::FileControlService construct
 * @param parent parent QObject
 */
FileControlService::FileControlService(QObject* parent) : QObject(parent) {}

/**
 * @brief sendFileRequest 发送文件请求
 * @param ip ip
 * @param username username
 * @param token token
 * @param path path
 */
void FileControlService::sendFileRequest(QString ip,
                                         QString username,
                                         QString token,
                                         QString path) {
  QString data("");
  QString json = LunaConstant::ProtocalTool::constructLunaProtocal(
      LunaConstant::ProtocalType::ControlMessage, username,
      LunaConstant::ProtocalCommand::SendTransferRequest, token,
      LunaConstant::ExceptionType::None, path, data);

  // send control message via tcp
  this->client->send(ip, LunaConstant::FILE_CONTROL_PORT, json);
}

/**
 * @brief sendTransferDeny 发送传输否定
 * @param ip
 */
void FileControlService::sendTransferDeny(
    QString ip,
    QString username,
    LunaConstant::ExceptionType exception) {
  QString token("");
  QString path("");
  QString data("");

  QString json = LunaConstant::ProtocalTool::constructLunaProtocal(
      LunaConstant::ProtocalType::ControlMessage, username,
      LunaConstant::ProtocalCommand::DenyTransfer, token, exception, path,
      data);

  // send deny control message via tcp
  this->client->send(ip, LunaConstant::FILE_CONTROL_PORT, json);
}

/**
 * @brief FileControlService::sendFileExposure 发送文件暴露
 * @param ip ip
 * @param path path
 * @param token token
 */
void FileControlService::sendFileExposure(QString ip,
                                          QString username,
                                          QString path,
                                          QString token) {
  QString data("");

  QString json = LunaConstant::ProtocalTool::constructLunaProtocal(
      LunaConstant::ProtocalType::ControlMessage, username,
      LunaConstant::ProtocalCommand::SendTransferExposure, token,
      LunaConstant::ExceptionType::None, path, data);

  // send protocal control via tcp
  this->client->send(ip, LunaConstant::FILE_CONTROL_PORT, json);
}

/**
 * @brief FileControlService::initService 初始化服务
 */
void FileControlService::initService() {
  // 初始化客户端和服务端对象
  this->client = new TcpClient;
  this->server = new TcpServerHandler(LunaConstant::FILE_CONTROL_PORT);

  // 连接回调以处理tcp接收到的消息
  connect(this->server, &TcpServerHandler::tcpReceived, this,
          &FileControlService::dealTcpServerReceive);
}

/**
 * @brief FileControlService::runService 运行service
 */
void FileControlService::runService() {}

/**
 * @brief FileControlService::destoryService 销毁服务，释放资源
 */
void FileControlService::destoryService() {
  delete this->client;
  delete this->server;
}

/**
 * @brief FileControlService::dealTcpServerReceive
 * 处理TcpServerHandler接收到的消息
 * @param data byte-array
 */
void FileControlService::dealTcpServerReceive(const QString ip,
                                              const QByteArray& data) {
  QJsonParseError e;

  QJsonDocument doc = QJsonDocument::fromJson(data, &e);

  qDebug() << data;

  // json解析异常
  if (e.error != QJsonParseError::NoError) {
    qDebug() << "file control  service parse json error" << e.errorString();
    return;
  }

  // 判断类型 提取username
  QJsonObject root = doc.object();
  if (!checkJsonValueValid(root["type"], data) ||
      !checkJsonValueValid(root["username"], data)) {
    return;
  }

  int typeCode = root["type"].toInt();
  QString username = root["username"].toString();
  LunaConstant::ProtocalType realType =
      LunaConstant::ProtocalTool::fromCodeGetType(typeCode);

  // 协议中未定义代码
  if (realType == LunaConstant::ProtocalType::UnknowType) {
    qDebug() << "file control: protocal is unknow type(" << typeCode << ')';
    return;
  }

  // 非控制类型丢弃
  if (realType == LunaConstant::TransferData) {
    qDebug() << "file control: send file data in transfer port(type)";
    return;
  }

  // content
  if (!checkJsonValueValid(root["content"], data)) {
    return;
  }
  QJsonObject contentObj = root["content"].toObject();

  // 判断是控制信息还是异常
  if (realType == LunaConstant::ProtocalType::ControlMessage) {
    // 控制信息
    if (!checkJsonValueValid(contentObj["command"], data)) {
      return;
    }
    LunaConstant::ProtocalCommand command =
        LunaConstant::ProtocalTool::fromCodeGetCommand(
            contentObj["command"].toInt());

    // 协议未定义指令
    if (command == LunaConstant::ProtocalCommand::UnknowCommand) {
      qDebug() << "file control: protocal has unknow command(" << command
               << ')';
      return;
    }

    // 非控制类型丢弃
    if (command == LunaConstant::ProtocalCommand::ConfirmTransfer) {
      qDebug() << "file control: send file data in transfer port(command)";
      return;
    }

    // 检查各个字段格式
    if (!checkJsonValueValid(contentObj["path"], data)) {
      return;
    }
    if (!checkJsonValueValid(contentObj["token"], data)) {
      return;
    }

    //  提取ip,path
    QString path = contentObj["path"].toString();
    QString token = contentObj["token"].toString();

    // 分别处理控制信息
    switch (command) {
      case LunaConstant::SendTransferExposure:

        // 发送文件暴露回调
        emit receiveValidFileTransferExposure(ip, username, path, token);

        break;
      case LunaConstant::SendTransferRequest:
        // 发送文件请求回调
        emit receiveTransferRequest(ip, username, path, token);
        break;
      case LunaConstant::DenyTransfer:

        // 发送文件拒绝传输的回调
        emit receiveFileTransferDeny(ip, username, path);
        break;
    }

  } else {
    if (!checkJsonValueValid(contentObj["exception"], data)) {
      return;
    }
    LunaConstant::ExceptionType exceptionType =
        LunaConstant::ProtocalTool::fromCodeGetException(
            contentObj["exception"].toInt());

    // 异常
    emit receiveError(ip, username, exceptionType);
  }
}
