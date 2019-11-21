#ifndef FORDEBUG_H
#define FORDEBUG_H

#include <QObject>
#include <QSet>

#include "core/service/boardcast_service.h"

class ForDebug : public QObject {
  Q_OBJECT
  BoardcastService service;

 private:
  QSet<QString> set;

 public:
  explicit ForDebug();

 public slots:
  void debug(QString ip);
};

#endif  // FORDEBUG_H
