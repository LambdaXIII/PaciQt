#ifndef TIMECODECLOCK_H
#define TIMECODECLOCK_H

#include <QWidget>
#include <QPaintEvent>
#include <QMap>
#include "timebase.h"
#include "candy_macros.h"
#include "paciwidget_global.h"


class PACIWIDGETSHARED_EXPORT TimecodeClock : public QWidget
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

protected:
  static const int DigitWidth = 15;
  static const int DigitHeight = 20;
  void paintEvent(QPaintEvent *event) override;
  const QMap<QChar, QString> imageMap {
    {';', ":/tc_clock/df"},
    {':', ":/tc_clock/ndf"}
  };


signals:
  void timebaseChanged(Timebase* x);
  void framesChanged(int x);
};

#endif // TIMECODECLOCK_H
