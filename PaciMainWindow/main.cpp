#include "pacimainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication::setApplicationName("Paci");
  QApplication::setApplicationDisplayName(QApplication::translate("main", "啪词"));
  QApplication::setApplicationVersion("0.1a");
  QApplication a(argc, argv);
  PaciMainWindow w;
  w.show();

  return a.exec();
}
