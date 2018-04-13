#ifndef BASETEST_H
#define BASETEST_H

#include <QObject>
#include <QTest>
#include <QDebug>
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

#define MAKEINC(X) static X instance;

#endif // BASETEST_H
