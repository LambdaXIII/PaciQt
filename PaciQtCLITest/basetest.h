#ifndef BASETEST_H
#define BASETEST_H

#include <QObject>
//#include <QTest>
#include <QVector>

class BaseTest : public QObject
{
  Q_OBJECT
public:
  static QVector<QObject*> m_testVector;
  explicit BaseTest();

signals:

public slots:
};

#endif // BASETEST_H
