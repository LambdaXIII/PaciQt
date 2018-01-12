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


void TrackSideBar::refresh()
{
  clearButtonGroup();

  TrackBox *tracks = GlobalSequence->trackBox();
  for (int i = 0; i < tracks->size(); i++) {
    TrackButton *button = new TrackButton(i, GlobalSequence->trackBox()->at(i));
    buttonGroup->addButton(button);
    layout()->addWidget(button);
  }
}

void TrackSideBar::handleSelection()
{
  TrackButton *checked = (TrackButton*)buttonGroup->checkedButton();
  emit trackSelected(checked->trackIndex);
}
