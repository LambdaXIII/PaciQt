#ifndef TESTTEST_H
#define TESTTEST_H
#include "basetest.h"
#include <QTest>

class TestTest : public BaseTest
{
  Q_OBJECT
private slots:
  void aTestTestFunction();
};

#endif // TESTTEST_H
