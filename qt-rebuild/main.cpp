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

  ForDebug f;

  return a.exec();
}
