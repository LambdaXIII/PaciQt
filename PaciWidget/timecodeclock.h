#ifndef TIMECODECLOCK_H
#define TIMECODECLOCK_H

#include <QWidget>
#include <QPaintEvent>
#include <QMap>
#include <QLCDNumber>
#include "timebase.h"
#include "candy_macros.h"
#include "paciwidget_global.h"


class PACIWIDGETSHARED_EXPORT TimecodeClock : public QLCDNumber
{
  Q_OBJECT
  CANDY_PROPERTY_RO(Timebase*, timebase)
  CANDY_PROPERTY_RO(int, frames)

public:
  explicit TimecodeClock(QWidget *parent = 0);
  explicit TimecodeClock(int f, Timebase *_tb, QWidget *parent = 0);
  ~TimecodeClock();

  void setTimebase(Timebase *tb);
  void setFrames(int x);

protected slots:
  void updateTC();

signals:
  void timebaseChanged(Timebase* x);
  void framesChanged(int x);
};

#endif // TIMECODECLOCK_H
