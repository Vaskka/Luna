#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <core/luna_core.h>

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 signals:

  /**
   * @brief showMessageArea 显示消息窗口区域
   * @param messageAreaObjectName 消息区域的ObjectName
   * @param message 消息内容
   * @param showSec 显示的时间
   */
  void showMessageArea(QString messageAreaObjectName, QString message);

 private slots:

  /**
   * @brief showMessageArea 处理显示消息窗口区域
   * @param messageAreaObjectName 消息区域的ObjectName
   * @param message 消息内容
   * @param showSec 显示的时间
   */
  void dealShowMessageArea(QString messageAreaObjectName, QString message);

  /**
   * @brief on_usernameLineEdit_returnPressed 用户名点击回车回调
   */
  void on_usernameLineEdit_returnPressed();

  /**
   * @brief appendNewIp 收到广播消息
   * @param ip ip
   * @param username username
   */
  void dealFindNewNode(QString ip, QString username);

  /**
   * @brief getFileSent 文件正在发送
   * @param ip ip
   * @param username username
   */
  void dealFileSending(QString ip, QString username);

  /**
   * @brief getTransferComfirm 暴露给用户的回调
   * @param ip ip
   * @param username username
   * @param name 文件名
   * @param fileContent 文件内容(real file content)
   */
  void dealReceiveFileContent(QString ip,
                              QString username,
                              QString name,
                              const QByteArray& fileContent);

  /**
   * @brief getValidFileTransferExposure 接收到有可传输的文件的暴露信息
   * @param ip 目标ip
   * @param username username
   * @param path 路径
   */
  void dealReceiveFileExposure(QString ip, QString username, QString path);

  /**
   * @brief getTransferDeny 接收到传输拒绝的消息
   * @param ip ip
   * @param username username
   * @param originPath path
   */
  void dealReceiveTransferDeny(QString ip,
                               QString username,
                               QString originPath);

  /**
   * @brief requestPassAuthorize 接收到的文件请求已经通过鉴权检验
   * @param ip ip
   * @param username username
   * @param path path
   */
  void dealRequestPassAuthorize(QString ip, QString username, QString path);

  /**
   * @brief receiveError 接收到异常消息
   * @param ip ip
   * @param username username
   * @param exception 异常类型
   */
  void dealReceiveError(QString ip,
                        QString username,
                        LunaConstant::ExceptionType exception);

 private:
  Ui::MainWindow* ui;

  QTimer timer;
};
#endif  // MAINWINDOW_H
