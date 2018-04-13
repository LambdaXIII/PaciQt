#include "testtest.h"
#include <QDebug>

void TestTest::aTestTestFunction()
{
  qDebug() << "Tests Started!";
  QCOMPARE(1, 1);
}

//To make the test availuable -- uncommet next line
//MAKEINC(TestTest)
