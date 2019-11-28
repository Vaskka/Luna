#include <QApplication>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);

  MainWindow w;
  w.show();

  // qDebug() << Util::changeCompatibleIpv6ToIpv4("::ffff:10.132.30.26");

  return a.exec();
}
