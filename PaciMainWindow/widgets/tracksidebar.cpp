#include "tracksidebar.h"
#include <QVBoxLayout>
#include "trackbutton.h"

TrackSideBar::TrackSideBar(QWidget *parent) : QScrollArea(parent)
{
//  QWidget *widget = new QWidget()
  QVBoxLayout *box = new QVBoxLayout();
  setLayout(box);
  buttonGroup = new QButtonGroup(this);
}

void TrackSideBar::clearButtonGroup()
{
  foreach (QAbstractButton *b, buttonGroup->buttons()) {
    b->deleteLater();
    buttonGroup->removeButton(b);
  }
}


void TrackSideBar::setSequence(Sequence *seq)
{
  layout()->children().clear();
  clearButtonGroup();

  sequence = seq;
  TrackBox *tracks = sequence->trackBox();
  for (int i = 0; i < tracks->size(); i++) {
    TrackButton *button = new TrackButton(i, sequence->trackBox()[i]);
    buttonGroup->addButton(button);
    layout()->addWidget(button);
  }
}
