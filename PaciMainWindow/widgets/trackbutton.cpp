#include "trackbutton.h"
#include <QPainter>

TrackButton::TrackButton(int _index, Track* _track, QWidget *parent)
  : PaciBaseButton(parent), track(_track), trackIndex(_index)
{
//  setFlat(true);
  setFocusPolicy(Qt::NoFocus);
  setMinimumSize(50, 30);
  setCheckable(true);
//  setupLabel();
}


void TrackButton::paintEvent(QPaintEvent *event)
{
  QPainter p(this);
  paintButtonShape(p);
  paintCheckableOverlay(p);
  p.setPen(Qt::white);
  p.drawText(centerBox(), Qt::AlignLeft | Qt::AlignVCenter, QString::number(trackIndex));
  p.drawText(centerBox(), Qt::AlignRight | Qt::AlignVCenter, track->tag());
}


//void TrackButton::setupLabel()
//{
//  setText(QString("#%1\n%2").arg(trackIndex).arg(track->tag()));
//}
