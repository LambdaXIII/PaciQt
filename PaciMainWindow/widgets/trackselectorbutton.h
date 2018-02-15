#ifndef TRACKSELECTORBUTTON_H
#define TRACKSELECTORBUTTON_H

#include <QWidget>
#include <QRadioButton>
#include <QPixmap>
#include <QTimer>
#include "pacibasebutton.h"
#include "track.h"

class TrackSelectorButton
  : public PaciBaseButton
{
  Q_OBJECT
  CANDY_PROPERTY_RO_VALUE(int, trackIndex, 0)
  CANDY_PROPERTY_RO(Track*, track)
public:
  explicit TrackSelectorButton(int i, Track* _track, QWidget *parent = nullptr);

protected:
  QStringList getPreviewLines();
  QString getTopLeftText();
  QString getBottomRightText();

  QPixmap m_previewMap;
  void drawPreviewMap();

  int m_overlay_offset;
  QTimer *offsetTimer;

  void paintEvent(QPaintEvent *event) override;

signals:
//  void trackSelected(int i);

protected slots:
  void updateOffset();
};

#endif // TRACKSELECTORBUTTON_H
