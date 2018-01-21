#ifndef TRACKSELECTOR_H
#define TRACKSELECTOR_H

#include <QDialog>
#include <QButtonGroup>
#include "trackselectorbutton.h"
#include "sequence.h"

namespace Ui {
class TrackSelector;
}

class TrackSelector : public QDialog
{
  Q_OBJECT
  CANDY_PROPERTY_RO_VALUE(int, currentTrackIndex, 0)
  CANDY_PROPERTY_RO(Sequence*, sequence)

public:
  explicit TrackSelector(Sequence* _seq, QWidget *parent = 0);
  ~TrackSelector();

  void setQuestion(QString s);
  QString question();

  static int getSelectedTrackIndex(Sequence *_seq, QWidget *parent = nullptr);
  static Track* getSelectedTrack(Sequence *_seq, QWidget *parent = nullptr);

private:
  Ui::TrackSelector *ui;
  QButtonGroup *buttonGroup;
  void setupButtons();

public slots:
  void handleToggle();
};

#endif // TRACKSELECTOR_H
