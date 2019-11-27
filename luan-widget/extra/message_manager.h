#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <QObject>

class MessageManager : public QObject {
  Q_OBJECT
 public:
  explicit MessageManager(QObject* parent = nullptr);

  /**
   * @brief registerMessage 向消息中心注册消息
   * @param registerObj 发起消息的对象
   * @param showPlatform 展示的平台
   * @param showTimeSecond 展示消息的时间
   * @param message 消息内容
   */
  void registerMessage(QObject* registerObj,
                       QObject* showPlatform,
                       int showTimeSecond,
                       QString& message);

 signals:

 public slots:
};

#endif  // MESSAGEMANAGER_H
