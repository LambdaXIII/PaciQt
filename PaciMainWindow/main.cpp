#include "pacimainwindow.h"
#include "sequencedoc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication::setApplicationName("Paci");
  QApplication::setApplicationDisplayName(QApplication::translate("main", "啪词"));
  QApplication::setApplicationVersion("0.1a");

  QApplication::setOrganizationName("Paci Project");
  QApplication::setOrganizationDomain("org.paci");

#ifdef Q_OS_WIN
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
#endif

  QApplication a(argc, argv);

  SequenceDoc(qApp);
//  SequenceDoc();

  PaciMainWindow w;
//  SequenceDoc(w);
  w.show();

  return a.exec();
}
