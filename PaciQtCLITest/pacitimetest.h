#ifndef PACITIMETEST_H
#define PACITIMETEST_H

#include <QObject>
#include "basetest.h"
#include "pacitime.h"

class PaciTimeTest : public BaseTest
{
  Q_OBJECT
private slots:
  void initTestCase();

  void testFrameToSecond_data();
  void testFrameToSecond();

  void testSecondToFrame_data();
  void testSecondToFrame();

  void secondDoubleCheck_data();
  void secondDoubleCheck();

  void frameDoubleCheck_data();
  void frameDoubleCheck();
};

#endif // PACITIMETEST_H
