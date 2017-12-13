#include "pacimainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  PaciMainWindow w;
  w.show();

  return a.exec();
}
