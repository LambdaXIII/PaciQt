#include "pacitimetest.h"

void PaciTimeTest::initTestCase()
{
  printf("测试 PaciCore 模块中的时间转换函数\n");
}

void PaciTimeTest::testFrameToSecond_data()
{
  QTest::addColumn<int>("rate");
  QTest::addColumn<int>("frame");
  QTest::addColumn<qreal>("second");

  QTest::newRow("one second") << 24 << 24 << 1.0;
  QTest::newRow("half second") << 24 << 12 << 0.5;
  QTest::newRow("six point twenty five second") << 24 << 150 << 6.25 ;
}

void PaciTimeTest::testFrameToSecond()
{
  QFETCH(int, rate);
  QFETCH(int, frame);
  QFETCH(qreal, second);

  Timebase tb(rate);
  qreal res = PaciTime::frame_to_second(tb, frame);
  QCOMPARE(res, second);
}

void PaciTimeTest::testSecondToFrame_data()
{
  QTest::addColumn<int>("rate");
  QTest::addColumn<qreal>("second");
  QTest::addColumn<int>("frame");

  QTest::addRow("1 second 24") << 24 << 1.0 << 24;
  QTest::addRow("1.5 second 18fps") << 18 << 1.5 << 27;
  QTest::addRow("5.8 second 30fps") << 30 << 5.8 << 174;
  QTest::addRow("32.048s 25fps") << 25 << 32.048 << 801;
}

void PaciTimeTest::testSecondToFrame()
{
  QFETCH(int, rate);
  QFETCH(int, frame);
  QFETCH(qreal, second);

  Timebase tb(rate);
  int res = PaciTime::second_to_frame(tb, second);
  QCOMPARE(res, frame);
}

void PaciTimeTest::secondDoubleCheck_data()
{
  QTest::addColumn<int>("rate");
  QTest::addColumn<qreal>("second");

  QTest::addRow("1.3s 24fps") << 24 << 1.3;
  QTest::addRow("6.6s 12fps") << 12 << 6.6;
  QTest::addRow("3.475s 50fps") << 50 << 3.475;
}

void PaciTimeTest::secondDoubleCheck()
{
  QFETCH(int, rate);
  QFETCH(qreal, second);

  Timebase tb(rate);
  int delta = PaciTime::second_to_frame(tb, second);
  qreal res = PaciTime::frame_to_second(tb, delta);
  qDebug() << (res == second ? "完全相等" : "有误差");
  QVERIFY(qAbs(second - res) <= 0.05);
}

void PaciTimeTest::frameDoubleCheck_data()
{
  QTest::addColumn<int>("rate");
  QTest::addColumn<int>("frame");

  QTest::addRow("300f 24fps") << 24 << 300;
  QTest::addRow("128f 25fps") << 25 << 128;
  QTest::addRow("21f 18fps") << 18 << 21;
  QTest::addRow("3892f 19fps") << 19 << 3892;
}

void PaciTimeTest::frameDoubleCheck()
{
  QFETCH(int, rate);
  QFETCH(int, frame);

  Timebase tb(rate);
  qreal delta = PaciTime::frame_to_second(tb, frame);
  int res = PaciTime::second_to_frame(tb, delta);
  QCOMPARE(frame, res);
}


MAKEINC(PaciTimeTest)
