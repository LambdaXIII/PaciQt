#include "trackbutton.h"
#include <QPainter>

TrackButton::TrackButton(int _index, Track* _track, QWidget *parent): QPushButton(parent), track(_track), trackIndex(_index)
{
  setFlat(true);
  setFocusPolicy(Qt::NoFocus);
  setMinimumSize(50, 30);
  setCheckable(true);
  setupLabel();
}

/*
void TrackButton::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  p.setFont(QFont("HeitiSC", 13));
  p.drawText(0, height() / 2, QString::number(trackIndex));
}
*/

void TrackButton::setupLabel()
{
  setText(QString("#%1\n%2").arg(trackIndex).arg(track->tag()));
}
