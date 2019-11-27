#ifndef COMMON_H
#define COMMON_H

#define PROJECT_NAME "LUNA"

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

namespace LunaConstant {

/* 协议类型 */
enum ProtocalType {
  ControlMessage,
  /* 控制信息 */  // 0
  TransferData,
  /* 数据传递, 此字段在文件传输端口发送 */  // 1
  Exception,
  /* 发生异常(鉴权错误等)，错误消息在content->data下 */  // 2
  UnknowType /* 代码未定义的类型*/                       // 3

};

/* 执行功能的类型 */
enum ProtocalCommand {
  SendTransferExposure, /* 发送文件暴露, 示意对方可以请求此文件,
                           产生新的token附在content.token字段,
                           发送方存储此字段在本地,
                           接收方检查到此字段也存储token到本地 */ // 16
  SendTransferRequest,  /* 请求对方发送指定文件, 携带token传递,
                         * 接收方检查到此字段可根据token情况或由用户直接确定是否进行传输或否认传输
                         */ // 32
  ConfirmTransfer,      /* 传输文件, 文件内容在content->data下,
                        此字段在文件传输端口发送*/ // 48
  DenyTransfer,         /* 否定接收 */ // 64
  UnknowCommand         /* 代码未定义的指令*/ // 80
};

/* 异常类型 */
enum ExceptionType {
  None,
  /* 无异常 */  // 256
  FileNotFound,
  /* 文件不存在 */  // 512
  AuthError,
  /* 鉴权错误 */  // 768
  HostCanNotArrive,
  /* 主机不可达 */                        // 1024
  UnknowException /* 代码未定义的异常 */  // 1280
};

class ProtocalTool {
 public:
  /**
   * @brief fromEnumGetInteger 协议类型转代码
   * @param type 协议类型
   * @return quint32
   */
  static int fromProtocalTypeGetInteger(const ProtocalType type);

  /**
   * @brief fromProtocalCommandGetInteger 协议指令转代码
   * @param command 指令类型
   * @return quint32
   */
  static int fromProtocalCommandGetInteger(const ProtocalCommand command);

  /**
   * @brief fromProtocalExceptionGetInteger 协议异常类型转代码
   * @param exception 异常
   * @return quint32
   */
  static int fromProtocalExceptionGetInteger(const ExceptionType exception);

  /**
   * @brief fromCodeGetType 类型代码转类型
   * @param code 代码
   * @return ProtocalType
   */
  static ProtocalType fromCodeGetType(const int code);

  /**
   * @brief fromCodeGetCommand 指令代码转类型
   * @param code 代码
   * @return ProtocalCommand
   */
  static ProtocalCommand fromCodeGetCommand(const int code);

  /**
   * @brief fromCodeGetException 异常代码转类型
   * @param code 代码
   * @return ExceptionType
   */
  static ExceptionType fromCodeGetException(const int code);

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
  static QString constructLunaProtocal(enum ProtocalType type,
                                       QString username,
                                       enum ProtocalCommand command,
                                       QString token,
                                       enum ExceptionType exception,
                                       QString path,
                                       QString& data);
};

/* 广播定段 */
static const char* broadcastContent = "LUNA_BROADCAST";

/* 文件控制信息通过4002端口传输 */
static const unsigned int FILE_CONTROL_PORT = 4002;

/* 文件内容传输通过4003端口传输 */
static const unsigned int FILE_TRANSFER_PORT = 4003;

/* token 超时毫秒数 */
static const qint32 TOKEN_TIMEOUT_MSEC = 5 * 60 * 1000;

}  // namespace LunaConstant

///**
// * @brief The LunaProtocalContent class 协议内部内容对象
// */
// class LunaProtocalContent {
// public:
//  LunaConstant::ProtocalCommand getCommand() const;
//  void setCommand(const LunaConstant::ProtocalCommand& value);

//  QString getToken() const;
//  void setToken(const QString& value);

//  LunaConstant::ExceptionType getException() const;
//  void setException(const LunaConstant::ExceptionType& value);

//  QString getData() const;
//  void setData(const QString& value);

//  QString getPath() const;
//  void setPath(const QString& value);

// private:
//  LunaConstant::ProtocalCommand command;

//  QString token;

//  LunaConstant::ExceptionType exception;

//  QString data;

//  QString path;
//};

///**
// * @brief The LunaProtocalObject class 协议结构对象
// */
// class LunaProtocalObject {
//  LunaConstant::ProtocalType type;

//  LunaProtocalContent content;

// public:
//  LunaConstant::ProtocalType getType() const;
//  void setType(const LunaConstant::ProtocalType& value);

//  LunaProtocalContent getContent() const;
//  void setContent(const LunaProtocalContent& value);
//};

/*
{
"type": $ProtocalType$,
"username": "sender username",
"content" : {
"command" : $ProtocalCommand$,
"token": "authorize token", //
"exception": $ExceptionType$,
"path": "file abs path"
"data": ""
}

}
*/

#endif  // COMMON_H
