#ifndef USERUNITFORVIEW_H
#define USERUNITFORVIEW_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QMap>
#include <QObject>
#include <QVector>

class UserUnitForView {
 private:
  QString ip;
  QString username;

  QString key;

  QMap<QString, QListWidgetItem*> innersListWidgetItemMap;

 public:
  UserUnitForView(QString ip, QString username);

  /**
   * @brief tryAppendNewListWidgetItem 尝试加入新的path
   * @param path path
   * @return QListWidgetItem\*
   */
  QListWidgetItem* tryAppendNewListWidgetItem(QString path);

  /**
   * @brief removeListWidgetWithPath 根据path移除ListWidget
   * @param path  path
   */
  // void removeListWidgetItemWithPath(QString path);

  QString getKey() const;
  QString getUsername() const;
  QString getIp() const;
  QMap<QString, QListWidgetItem*> getInnerListWidgetItemMap() const;
};

#endif  // USERUNITFORVIEW_H
