#ifndef TRACKSIDEBAR_H
#define TRACKSIDEBAR_H

#include <QWidget>
#include <QScrollArea>
#include <QButtonGroup>
#include "sequence.h"


class TrackSideBar : public QScrollArea
{
  Q_OBJECT
public:
  explicit TrackSideBar(QWidget *parent = nullptr);

protected:
  QButtonGroup *buttonGroup;
  Sequence *sequence;

signals:

public slots:
  void setSequence(Sequence *seq);

protected slots:
  void clearButtonGroup();
};

#endif // TRACKSIDEBAR_H
