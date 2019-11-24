#include <QCoreApplication>
#include <QMap>
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
  //  QFile afile("/Users/vaskka/Desktop/a.out");
  //  QFile bfile("/Users/vaskka/Desktop/b.out");
  //  afile.open(QFile::ReadOnly);
  //  bfile.open(QFile::ReadOnly);
  //  QByteArray adata = afile.readAll();
  //  QByteArray bdata = bfile.readAll();
  //  debug.debugSendFileComfirm("127.0.0.1", "/Users/vaskka/Desktop/a.out",
  //  adata); debug.debugSendFileComfirm("127.0.0.1",
  //  "/Users/vaskka/Desktop/b.out", bdata);

  return a.exec();
}
