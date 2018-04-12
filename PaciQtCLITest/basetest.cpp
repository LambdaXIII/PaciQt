#include "basetest.h"

BaseTest::BaseTest() : QObject()
{
  m_testVector.push_back(this);
}

QVector<QObject*> BaseTest::m_testVector;
