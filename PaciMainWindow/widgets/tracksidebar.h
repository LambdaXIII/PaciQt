#ifndef TRACKSIDEBAR_H
#define TRACKSIDEBAR_H

#include <QWidget>
#include <QScrollArea>
#include <QButtonGroup>
#include "sequence.h"
#include "../sequencedoc.h"
#include <QSpacerItem>


class TrackSideBar : public QScrollArea
{
  Q_OBJECT
public:
  explicit TrackSideBar(QWidget *parent = nullptr);

protected:
  QButtonGroup *buttonGroup;
  QSpacerItem *spacer;

signals:
  void trackSelected(int index);

public slots:
  void refresh();

protected slots:
  void clearButtonGroup();
  void handleSelection();
};

#endif // TRACKSIDEBAR_H
