#include "timecodeclock.h"
#include <QPainter>

TimecodeClock::TimecodeClock(int f, Timebase *_tb, QWidget *parent)
  : QWidget(parent), m_frames(f), m_timebase(_tb)
{
  setMaximumHeight(DigitHeight);
  setMaximumWidth(DigitWidth * 11);
}

TimecodeClock::TimecodeClock(QWidget *parent)
  : QWidget(parent)
{}

TimecodeClock::~TimecodeClock()
{

}

void TimecodeClock::setTimebase(Timebase *tb)
{
  if (tb != timebase()) {
    m_timebase = tb;
    emit timebaseChanged(tb);
  }
}

void TimecodeClock::setFrames(int x)
{
  if (x != frames()) {
    m_frames = x;
    emit framesChanged(x);
  }
}

void TimecodeClock::paintEvent(QPaintEvent *event)
{
  QString tc = "12:34:56;78";

  QPainter painter(this);
  for (int index = 0; index <= 10; index++) {
    QImage img;
    if (QString("1234567890").contains(tc[index]))
      img = QImage(":/tc_clock/" + tc[index]);
    else
      img = QImage(imageMap[tc[index]]);

    painter.drawImage(
      index * DigitWidth, 0,
      img
    );
  }
}
