#include <QCoreApplication>
#include <QMap>
#include <QObject>
#include <QUuid>
#include <iostream>

#include "auth/authorize.h"
#include "core/service/boardcast_service.h"
#include "fordebug.h"
#include "io/database_handler.h"
#include "utils/util.h"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  ForDebug debug;

  auto map = debug.getMap();

  AliveNode* n = new AliveNode("10.132.31.0", "MyNode");
  n->appendTransferUnit("/Users/vaskka/Desktop/classmodel.png",
                        "fbd948a9aa3635f79de1e56632b7915ce31cbe3a");
  map->insert(AliveNode::getIdentifyKey("10.132.31.0", "MyNode"), n);

  // read
  QFile file("/Users/vaskka/Desktop/classmodel.png");
  file.open(QFile::ReadOnly);

  QByteArray data = file.readAll();

  debug.sendFileContent("10.132.31.0", "MyNode",
                        "/Users/vaskka/Desktop/classmodel.png", data);

  return a.exec();
}
