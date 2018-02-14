#ifndef TRACKBUTTON_H
#define TRACKBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "track.h"
#include "pacibasebutton.h"

class TrackButton : public PaciBaseButton
{
  Q_OBJECT
public:
  TrackButton(int _index, Track *_track, QWidget *parent = 0);

  Track *track;
  int trackIndex;

//  void setupLabel();

  void paintEvent(QPaintEvent *event) override;
};

#endif // TRACKBUTTON_H
