#include "timecodeclock.h"
#include <QPainter>

TimecodeClock::TimecodeClock(int f, Timebase *_tb, QWidget *parent)
  : QLCDNumber(parent), m_frames(f)
{
  if (! _tb) {
    m_timebase = new Timebase(this);
  }
  setSegmentStyle(QLCDNumber::Flat);
  setDigitCount(11);
  connect(this, &TimecodeClock::framesChanged, this, &TimecodeClock::updateTC);
  connect(this, &TimecodeClock::timebaseChanged, this, &TimecodeClock::updateTC);
  setFrames(36789);
//  updateTC();
}

TimecodeClock::TimecodeClock(QWidget *parent)
  : TimecodeClock(0, nullptr, parent)
{

}

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

void TimecodeClock::updateTC()
{
  QString s = Timebase::frameToTimecode(frames(), timebase());
  s.replace(";", ".");
  display(s);
}
