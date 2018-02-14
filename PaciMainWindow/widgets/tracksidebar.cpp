#include "tracksidebar.h"
#include <QVBoxLayout>
#include "trackbutton.h"

TrackSideBar::TrackSideBar(QWidget *parent) : QScrollArea(parent)
{
//  QWidget *widget = new QWidget()
  setMaximumWidth(150);
  QVBoxLayout *box = new QVBoxLayout();
  box->setContentsMargins(0, 0, 0, 0);
  box->setSpacing(0);
  setLayout(box);
  buttonGroup = new QButtonGroup(this);
  spacer = new QSpacerItem(999999, 999999, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
}

void TrackSideBar::clearButtonGroup()
{
  foreach (QAbstractButton *b, buttonGroup->buttons()) {
    b->deleteLater();
    buttonGroup->removeButton(b);
  }
  layout()->removeItem(spacer);
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
  layout()->addItem(spacer);

  if (GlobalSequence->trackBox()->size() <= 1)
    this->setVisible(false);
  else
    this->setVisible(true);

  buttonGroup->buttons().first()->setChecked(true);
  emit trackSelected(0);
}

void TrackSideBar::handleSelection()
{
  TrackButton *checked = (TrackButton*)buttonGroup->checkedButton();
  emit trackSelected(checked->trackIndex);
}
