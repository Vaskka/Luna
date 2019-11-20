#ifndef COMMON_H
#define COMMON_H

#define PROJECT_NAME "LUNA"

namespace LunaConstant {

/* 协议类型 */
enum ProtocalType {
  ControlMessage, /* 控制信息 */
  TransferData,   /* 数据传递 */
  Exception /* 发生异常(鉴权错误等)，错误消息在content->data下 */

};

/* 执行功能的类型 */
enum ProtocalCommand {
  SendTransferRequest, /* 请求对方接收, 此时不需要鉴权, 产生一个新token存在本地
                        */
  ConfirmTransfer, /* 确认接收, 携带token传递，检查token后传输文件内容*/
  DenyTransfer, /* 否定接收 */
  TransferFile  /* 传输文件，文件内容在content->data下 */

};

}  // namespace LunaConstant

/*
{
"type": $ProtocalType$
"content" : {
"command" : $ProtocalCommand$,
"token": "authorize token", //
"data": ""
}

}
*/

#endif  // COMMON_H
