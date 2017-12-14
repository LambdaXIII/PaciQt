#ifndef TRACKBUTTON_H
#define TRACKBUTTON_H

#include <QWidget>
#include <QPushButton>
#include "track.h"

class TrackButton : public QPushButton
{
public:
  TrackButton(int _index, Track *_track, QWidget *parent = 0);

  Track *track;
  int trackIndex;

  void paintEvent(QPaintEvent *event) override;
};

#endif // TRACKBUTTON_H
