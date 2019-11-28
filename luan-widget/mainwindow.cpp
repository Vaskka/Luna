#include "mainwindow.h"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // init data
  this->fileSavePath =
      QStandardPaths::standardLocations(QStandardPaths::DesktopLocation)
          .first();
  QLabel* saveDirLabel = this->findChild<QLabel*>("saveDirLabel");
  saveDirLabel->setText(fileSavePath);

  // init core
  this->core = new LunaCore(this);

  // 消息label显示
  connect(this, &MainWindow::showMessageArea, this,
          &MainWindow::dealShowMessageArea);

  // 处理发现新节点
  connect(this->core, &LunaCore::findNewNode, this,
          &MainWindow::dealFindNewNode);

  // 处理文件正在发送
  connect(this->core, &LunaCore::fileSending, this,
          &MainWindow::dealFileSending);

  // 处理文件暴露
  connect(this->core, &LunaCore::receiveFileExposure, this,
          &MainWindow::dealReceiveFileExposure);

  // 处理文件 拒绝
  connect(this->core, &LunaCore::receiveTransferDeny, this,
          &MainWindow::dealReceiveTransferDeny);

  // 处理文件请求已经通过鉴权
  connect(this->core, &LunaCore::requestPassAuthorize, this,
          &MainWindow::dealRequestPassAuthorize);

  // 处理接收到异常
  connect(this->core, &LunaCore::receiveError, this,
          &MainWindow::dealReceiveError);

  // 处理接收到文件内容
  connect(this->core, &LunaCore::receiveFileContent, this,
          &MainWindow::dealReceiveFileContent);

  // 处理op异常
  connect(this->core, &LunaCore::opError, this, &MainWindow::dealOpError);
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

  this->setUsername(edit->text());
}

/**
 * @brief appendNewIp 收到广播消息
 * @param ip ip
 * @param username username
 */
void MainWindow::dealFindNewNode(QString ip, QString username) {
  qDebug() << "get new node ip:" << ip << " username:" << username;
  this->updateUserList();
}

/**
 * @brief getFileSent 文件正在发送
 * @param ip ip
 * @param username username
 */
void MainWindow::dealFileSending(QString ip, QString username) {
  qDebug() << "file is sending to" << ip << " username:" << username;
}

/**
 * @brief getTransferComfirm 暴露给用户的回调
 * @param ip ip
 * @param username username
 * @param name 文件名
 * @param fileContent 文件内容(real file content)
 */
void MainWindow::dealReceiveFileContent(QString ip,
                                        QString username,
                                        QString name,
                                        const QByteArray& fileContent) {
  qDebug() << "receive file Content";
  QString saveFileFullPath = this->fileSavePath + "/" + name;
  QFile saveFile(saveFileFullPath);

  if (!saveFile.open(QFile::WriteOnly)) {
    // 文件打开失败
    QString errMsg = "file cant open:" + saveFileFullPath + " from ip:" + ip +
                     "from username:" + username;
    qDebug() << errMsg;
    dealOpError(errMsg);
    return;
  }

  // write file content
  saveFile.write(fileContent);
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
  emit showMessageArea("infoLabel", message);

  // 当前状态是接收到文件暴露的用户，就刷新文件列表
  if (this->currentIp == ip && this->currentUsername == username) {
    this->updateFileList(ip, username);
  }
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

  QMessageBox::warning(nullptr, "传输拒绝", content, QMessageBox::Ok);
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
  /*
    QMessageBox::StandardButton rb =
        QMessageBox::information(this, tr("文件传输请求确认"), content,
                                 QMessageBox::Yes | QMessageBox::No);
    // 判断用户的相应类型
    switch (rb) {
      case QMessageBox::Yes:
        qDebug() << "Yes";
        // this->core->sendFileContent(ip, username, path);
        break;
      case QMessageBox::No:
        qDebug() << "NO";
        // this->core->sendTransferDeny(ip, username);
        break;
      default:
        break;
    }
  */
  qDebug() << "q";
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

/**
 * @brief opError core层错误信息
 * @param errorMsg 错误信息
 */
void MainWindow::dealOpError(QString errorMsg) {
  QMessageBox::warning(this, "Opps!", errorMsg, QMessageBox::Ok);
}

void MainWindow::setUsername(const QString& value) {
  this->core->setUsername(value);
}

QString MainWindow::getUsername() const {
  return this->core->getUsername();
}

/**
 * @brief MainWindow::updateFileList 更新文件列表
 * @param currentIp 当前用户ip
 * @param currentUsername 当前用户用户名
 */
void MainWindow::updateFileList(QString currentIp, QString currentUsername) {
  QMap<QString, AliveNode*>* map = this->core->getAliveNodeMap();

  QString token = AliveNode::getIdentifyKey(currentIp, currentUsername);

  if (!map->contains(token)) {
    // 此用户不存在
    qDebug() << "update file list error:" << currentIp << " " << currentUsername
             << " not exits";
    return;
  }

  QListWidget* fileWidget = this->findChild<QListWidget*>("userFileListWidget");

  // 更新列表视图
  fileWidget->clear();
  QLinkedList<FileUnit*>* pathNames = (*map)[token]->getTransferList();
  for (FileUnit* unit : *pathNames) {
    fileWidget->addItem(unit->getPath());
  }
}

/**
 * @brief updateUserList 更新用户列表
 */
void MainWindow::updateUserList() {
  QListWidget* userWidget = this->findChild<QListWidget*>("userListWidget");

  // 更新列表视图
  userWidget->clear();
  QMap<QString, AliveNode*>* map = this->core->getAliveNodeMap();

  for (AliveNode* node : map->values()) {
    userWidget->addItem(node->getUsername());
  }
}

/**
 * @brief MainWindow::on_chooseFileToExp_clicked 向当前用户发送文件暴露
 */
void MainWindow::on_chooseFileToExp_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("选则您向别人分享的文件"), "", tr("*.*"));
  qDebug() << "send file to exp:" << fileName;

  this->core->sendFileExposure(currentIp, currentUsername, fileName);
}

/**
 * @brief MainWindow::on_userFileListWidget_itemDoubleClicked 双击某一个文件
 * @param item QListWidgetItem*
 */
void MainWindow::on_userFileListWidget_itemDoubleClicked(
    QListWidgetItem* item) {
  this->core->sendFileRequest(currentIp, currentUsername, item->text());
}

/**
 * @brief MainWindow::on_pushButton_clicked 选择文件存储文件夹
 */
void MainWindow::on_chooseFileToSave_clicked() {
  QString dirPath =
      QFileDialog::getExistingDirectory(this, tr("选择文件的存储目录"));

  this->fileSavePath = dirPath;
  QLabel* saveDirLabel = this->findChild<QLabel*>("saveDirLabel");

  saveDirLabel->setText(dirPath);
}

/**
 * @brief MainWindow::on_userListWidget_itemActivated 选择的用户被点击或双击
 * @param item
 */
void MainWindow::on_userListWidget_itemActivated(QListWidgetItem* item) {
  QString username = item->text();
  QString ip = this->core->fromUsernameSearchIp(username);

  if (ip.isNull()) {
    // 没搜索到删除这个项（当前用户已经离线）
    QListWidget* userWidget = this->findChild<QListWidget*>("userListWidget");
    userWidget->removeItemWidget(item);
    return;
  }

  // 暂存这个用户的ip和用户名
  this->currentIp = ip;
  this->currentUsername = username;

  // 更新这个用户的文件列表
  this->updateFileList(ip, username);

  // 屏幕中相应lable显示用户名
  QLabel* currUsernameLabel =
      this->findChild<QLabel*>("currentChooseUserValue");
  currUsernameLabel->setText(username);
}
