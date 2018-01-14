#include "tracksidebar.h"
#include <QVBoxLayout>
#include "trackbutton.h"

TrackSideBar::TrackSideBar(QWidget *parent) : QScrollArea(parent)
{
//  QWidget *widget = new QWidget()
  setMaximumWidth(150);
  QVBoxLayout *box = new QVBoxLayout();
  box->setContentsMargins(0, 0, 0, 0);
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
    connect(button, &TrackButton::clicked, this, &TrackSideBar::handleSelection);
    buttonGroup->addButton(button);
    layout()->addWidget(button);
  }
}

void TrackSideBar::handleSelection()
{
  TrackButton *checked = (TrackButton*)buttonGroup->checkedButton();
  emit trackSelected(checked->trackIndex);
}
