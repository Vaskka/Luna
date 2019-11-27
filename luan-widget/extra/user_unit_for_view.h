#ifndef USERUNITFORVIEW_H
#define USERUNITFORVIEW_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QObject>
#include <QVector>

class UserUnitForView {
 private:
  QString ip;
  QString username;

  QString key;

  QVector<QListWidgetItem*> innerPathList;

 public:
  UserUnitForView(QString ip, QString username);

  /**
   * @brief tryAppendNewListWidgetItem 尝试加入新的path
   * @param path path
   * @return QListWidgetItem\*
   */
  QListWidgetItem* tryAppendNewListWidgetItem(QString path);

  QString getKey() const;
  QString getUsername() const;
  QString getIp() const;
  QVector<QListWidgetItem*> getInnerPathList() const;
};

#endif  // USERUNITFORVIEW_H
