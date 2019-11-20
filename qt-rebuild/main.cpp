#include <QCoreApplication>
#include <QMap>
#include <QUuid>
#include <iostream>

#include "auth/authorize.h"
#include "io/database_handler.h"
#include "utils/util.h"

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  Authorize auth(1000 * 1000);

  QString token = auth.applyUniqueToken("127.0.0.1", "macbook",
                                        "/Users/vaskka/Desktop/a.txt");

  qDebug() << token;
  QTime t;
  t.start();
  while (t.elapsed() < 3000)
    ;

  bool r = auth.checkIfTokenValid(token);

  qDebug() << r;
  qDebug() << auth.applyUniqueToken("127.0.0.1", "macbook",
                                    "/Users/vaskka/Desktop/a.txt");
  return a.exec();
}
