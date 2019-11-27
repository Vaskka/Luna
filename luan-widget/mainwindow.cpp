#include "mainwindow.h"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // 消息label显示
  connect(this, &MainWindow::showMessageArea, this,
          &MainWindow::dealShowMessageArea);
}

MainWindow::~MainWindow() {
  delete ui;
}

/**
 * @brief showMessageArea 处理显示消息窗口区域
 * @param messageAreaObjectName 消息区域的ObjectName
 */
void MainWindow::dealShowMessageArea(QString messageAreaObjectName,
                                     QString message) {
  QLabel* messageLable = this->findChild<QLabel*>(messageAreaObjectName);
  messageLable->setText(message);
}

/**
 * @brief MainWindow::on_usernameLineEdit_returnPressed return press
 */
void MainWindow::on_usernameLineEdit_returnPressed() {
  QLineEdit* edit = dynamic_cast<QLineEdit*>(sender());

  qDebug() << "return:" << edit->text();

  QString content;
  content += "用户 ";
  content += edit->text();
  content += ' ';
  content += "请求传输文件:";
  content += edit->text();

  QMessageBox messageBox(QMessageBox::NoIcon, "文件传输请求确认", content,
                         QMessageBox::Yes | QMessageBox::No, this);
  int result = messageBox.exec();

  // 判断用户的请求类型
  switch (result) {
    case QMessageBox::Yes:
      qDebug() << "Yes";
      break;
    case QMessageBox::No:
      qDebug() << "NO";
      break;
    default:
      break;
  }
}

/**
 * @brief getValidFileTransferExposure 接收到有可传输的文件的暴露信息
 * @param ip 目标ip
 * @param username username
 * @param path 路径
 */
void MainWindow::dealReceiveFileExposure(QString ip,
                                         QString username,
                                         QString path) {
  QString message;
  message += "接收到用户:";
  message += username;
  message += " 的可请求下载文件:";
  message += Util::fromPathGetFileName(path);
  // 显示消息
  emit showMessageArea(message, "infoLabel");

  QListWidget* userListView =
      this->findChild<QListWidget*>("userFileListWidget");

  /* 添加新的可获取文件ListWidget */
  QListWidgetItem* newItem = new QListWidgetItem;
  newItem->setText(path);
}

/**
 * @brief getTransferDeny 接收到传输拒绝的消息
 * @param ip ip
 * @param username username
 * @param originPath path
 */
void MainWindow::dealReceiveTransferDeny(QString ip,
                                         QString username,
                                         QString originPath) {
  QString content;
  content += "用户:";
  content += username;
  content += " 拒绝传输文件:";
  content += originPath;

  QMessageBox::warning(this, "传输拒绝", content, QMessageBox::Ok);
  qDebug() << "catch deny transfer with ip:" << ip << " username:" << username
           << " path:" << originPath;
}

/**
 * @brief requestPassAuthorize 接收到的文件请求已经通过鉴权检验
 * @param ip ip
 * @param username username
 * @param path path
 */
void MainWindow::dealRequestPassAuthorize(QString ip,
                                          QString username,
                                          QString path) {
  QString content;
  content += "用户 ";
  content += username;
  content += ' ';
  content += "请求传输文件:";
  content += path;

  QMessageBox messageBox(QMessageBox::NoIcon, "文件传输请求确认", content,
                         QMessageBox::Yes | QMessageBox::No, this);
  int result = messageBox.exec();

  // 判断用户的请求类型
  switch (result) {
    case QMessageBox::Yes:
      qDebug() << "Yes";
      break;
    case QMessageBox::No:
      qDebug() << "NO";
      break;
    default:
      break;
  }
}

/**
 * @brief MainWindow::dealReceiveError 接收到异常
 * @param ip
 * @param username
 * @param exception
 */
void MainWindow::dealReceiveError(QString ip,
                                  QString username,
                                  LunaConstant::ExceptionType exception) {
  qDebug() << "catch Exception with:: "
           << "ip:" << ip << "user:" << username << "exception:" << exception;
}
