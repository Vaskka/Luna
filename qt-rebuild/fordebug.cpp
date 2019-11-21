#include "fordebug.h"

ForDebug::ForDebug() : QObject() {
  service.runService();
  connect(&service, &BoardcastService::appendNewIp, this, &ForDebug::debug);
}

void ForDebug::debug(QString ip) {
  this->set.insert(ip);
  foreach (auto s, this->set) { qDebug() << s << ", "; }
}
