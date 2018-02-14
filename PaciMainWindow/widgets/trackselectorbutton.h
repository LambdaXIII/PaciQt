#ifndef TRACKSELECTORBUTTON_H
#define TRACKSELECTORBUTTON_H

#include <QWidget>
#include <QRadioButton>
#include "pacibasebutton.h"
#include "track.h"

class TrackSelectorButton
  : public QRadioButton
{
  Q_OBJECT
  CANDY_PROPERTY_RO_VALUE(int, trackIndex, 0)
  CANDY_PROPERTY_RO(Track*, track)
public:
  explicit TrackSelectorButton(int i, Track* _track, QWidget *parent = nullptr);

protected:
  QStringList getPreviewLines();
  QString getButtonText();

signals:
//  void trackSelected(int i);
};

#endif // TRACKSELECTORBUTTON_H
