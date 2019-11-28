#include "user_unit_for_view.h"

QString UserUnitForView::getKey() const {
  return key;
}

QString UserUnitForView::getUsername() const {
  return username;
}

QString UserUnitForView::getIp() const {
  return ip;
}

QMap<QString, QListWidgetItem*> UserUnitForView::getInnerListWidgetItemMap()
    const {
  return innersListWidgetItemMap;
}

/**
 * @brief UserUnitForView::UserUnitForView construct
 * @param ip
 * @param username
 */
UserUnitForView::UserUnitForView(QString ip, QString username) {
  this->ip = ip;
  this->username = username;
}

/**
 * @brief tryAppendNewListWidgetItem 尝试加入新的path
 * @param path path
 * @return QListWidgetItem\*
 */
QListWidgetItem* UserUnitForView::tryAppendNewListWidgetItem(QString path) {
  ////--////
  // 找不到一样的path才append,找得到就返回
  if (this->innersListWidgetItemMap.contains(path)) {
    return this->innersListWidgetItemMap[path];
  }

  QListWidgetItem* newItem = new QListWidgetItem;
  newItem->setText(path);
  this->innersListWidgetItemMap.insert(path, newItem);
  return newItem;
}

/**
 * @brief UserUnitForView::removeListWidgetWithPath 根据path移除ListWidgetItem
 * @param path path
 */
// void UserUnitForView::removeListWidgetItemWithPath(QString path) { }
