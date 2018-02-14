#include "trackselectorbutton.h"

TrackSelectorButton::TrackSelectorButton(int i, Track *_track, QWidget *parent)
  : QRadioButton(parent), m_trackIndex(i), m_track(_track)
{
  setCheckable(true);
  setText(getButtonText());
}

QStringList TrackSelectorButton::getPreviewLines()
{
  QStringList res;
  if (track()->isEmpty())
    res << tr("[空轨道]");
  else {
    int count = track()->size() >= 10 ? 9 : track()->size();

    for (int i = 0; i < count; i++) {
      res << track()->at(i)->content();
    }
    if (count >= 9) {
      res << "...";
    }
  }
  return res;
}

QString TrackSelectorButton::getButtonText()
{
  QStringList res;
  res << QString("[%1]%2").arg(trackIndex()).arg(track()->tag());
  res << getPreviewLines();
  return res.join("\n");
}
