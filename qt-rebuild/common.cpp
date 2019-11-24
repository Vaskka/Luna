#include "common.h"

#include <iostream>

namespace LunaConstant {

/**
 * @brief fromEnumGetInteger 协议类型转代码
 * @param type 协议类型
 * @return quint32
 */
int ProtocalTool::fromProtocalTypeGetInteger(const ProtocalType type) {
  switch (type) {
    case ControlMessage:
      return 0x0;
    case TransferData:
      return 0x1;
    case Exception:
      return 0x2;
    default:
      return 0x3;
  }
}

/**
 * @brief fromProtocalCommandGetInteger 协议指令转代码
 * @param command 指令类型
 * @return quint32
 */
int ProtocalTool::fromProtocalCommandGetInteger(const ProtocalCommand command) {
  switch (command) {
    case SendTransferExposure:
      return 0x10;
    case SendTransferRequest:
      return 0x20;
    case ConfirmTransfer:
      return 0x30;
    case DenyTransfer:
      return 0x40;
    default:
      return 0x50;
  }
}

/**
 * @brief fromProtocalExceptionGetInteger 协议异常类型转代码
 * @param exception 异常
 * @return quint32
 */
int ProtocalTool::fromProtocalExceptionGetInteger(
    const ExceptionType exception) {
  switch (exception) {
    case None:
      return 0x100;
    case FileNotFound:
      return 0x200;
    case AuthError:
      return 0x300;
    case HostCanNotArrive:
      return 0x400;
    default:
      return 0x500;
  }
}

/**
 * @brief fromCodeGetType 类型代码转类型
 * @param code 代码
 * @return ProtocalType
 */
LunaConstant::ProtocalType ProtocalTool::fromCodeGetType(const int code) {
  switch (code) {
    case 0x0:
      return ProtocalType::ControlMessage;
    case 0x1:
      return ProtocalType::TransferData;
    case 0x2:
      return ProtocalType::Exception;
    default:
      return ProtocalType::UnknowType;
  }
}

/**
 * @brief fromCodeGetCommand 指令代码转类型
 * @param code 代码
 * @return ProtocalCommand
 */
ProtocalCommand ProtocalTool::fromCodeGetCommand(const int code) {
  switch (code) {
    case 0x10:
      return ProtocalCommand::SendTransferExposure;
    case 0x20:
      return ProtocalCommand::SendTransferRequest;
    case 0x30:
      return ProtocalCommand::ConfirmTransfer;
    case 0x40:
      return ProtocalCommand::DenyTransfer;
    default:
      return ProtocalCommand::UnknowCommand;
  }
}

/**
 * @brief fromCodeGetException 异常代码转类型
 * @param code 代码
 * @return ExceptionType
 */
ExceptionType ProtocalTool::fromCodeGetException(const int code) {
  switch (code) {
    case 0x100:
      return ExceptionType::None;
    case 0x200:
      return ExceptionType::FileNotFound;
    case 0x300:
      return ExceptionType::AuthError;
    case 0x400:
      return ExceptionType::HostCanNotArrive;
    default:
      return ExceptionType::UnknowException;
  }
}

/**
 * @brief constructLunaProtocal 组装协议字段
 * @param type 协议类型
 * @param command 执行的指令
 * @param token 鉴权
 * @param exception 异常类型
 * @param path 文件路径
 * @param data  文件数据
 * @return QString-Json
 */
QString ProtocalTool::constructLunaProtocal(enum ProtocalType type,
                                            QString username,
                                            enum ProtocalCommand command,
                                            QString token,
                                            enum ExceptionType exception,
                                            QString path,
                                            QString& data) {
  QJsonObject root;
  QJsonObject content;

  content.insert("command", fromProtocalCommandGetInteger(command));
  content.insert("token", token);
  content.insert("exception", fromProtocalExceptionGetInteger(exception));
  content.insert("path", path);
  content.insert("data", data);

  root.insert("type", fromProtocalTypeGetInteger(type));
  root.insert("content", content);
  root.insert("username", username);

  QJsonDocument doc(root);

  QString result = doc.toJson(QJsonDocument::Compact);

  return result;
}

};  // namespace LunaConstant
