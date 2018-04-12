#include <QCoreApplication>
#include <QTest>
#include "basetest.h"

int main(int argc, char *argv[])
{
  /*
   QCoreApplication a(argc, argv);

   return a.exec();
  */
  int failedTestCount = 0;

  QVector<QObject*>::iterator iTest;
  for (iTest = BaseTest::m_testVector.begin(); iTest != BaseTest::m_testVector.end(); iTest++) {
    int result = QTest::qExec(*iTest, argc, argv);
    if (result != 0)
      failedTestCount++;
  }

  return failedTestCount;
}
