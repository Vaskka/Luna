#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <core/luna_core.h>
#include <extra/user_unit_for_view.h>

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QStandardPaths>

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

  QString getUsername() const;

  void setUsername(const QString& value);

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

  /**
   * @brief opError core层错误信息
   * @param errorMsg 错误信息
   */
  void dealOpError(QString errorMsg);

  /**
   * @brief on_chooseFileToExp_clicked 处理选择分享的文件
   */
  void on_chooseFileToExp_clicked();

  /**
   * @brief MainWindow::on_userFileListWidget_itemDoubleClicked
   * 处理双击某一个文件
   * @param item QListWidgetItem*
   */
  void on_userFileListWidget_itemDoubleClicked(QListWidgetItem* item);

  /**
   * @brief MainWindow::on_pushButton_clicked 选择文件存储文件夹
   */
  void on_chooseFileToSave_clicked();

  /**
   * @brief MainWindow::on_userListWidget_itemActivated 选择的用户被点击或双击
   * @param item
   */
  void on_userListWidget_itemActivated(QListWidgetItem* item);

 private:
  Ui::MainWindow* ui;

  LunaCore* core;

  QString currentIp;

  QString currentUsername;

  QString fileSavePath;

  /**
   * @brief updateFileList 更新文件列表
   * @param currentIp 当前ip
   * @param currentUsername 当前username
   */
  void updateFileList(QString currentIp, QString currentUsername);

  /**
   * @brief updateUserList 更新用户列表
   */
  void updateUserList();
};
#endif  // MAINWINDOW_H
