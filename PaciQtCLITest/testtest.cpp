#include "testtest.h"
#include <QDebug>

void TestTest::aTestTestFunction()
{
  qDebug() << "Tests Started!";
  QCOMPARE(1, 2);
}

static TestTest instance;
