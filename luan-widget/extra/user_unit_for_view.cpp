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

QVector<QListWidget*> UserUnitForView::getInnerPathList() const {
  return innerPathList;
}

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
  ////////
  for (int i = 0; i < this->innerPathList.length(); i++) {
    if (this->innerPathList.da)
  }

  for (QListWidgetItem* item : this->innerPathList) {
    if (item->data().toString() == path) {
      return item;
    }
  }

  QListWidgetItem* newItem = new QListWidgetItem;
  newItem->setText(path);
}
