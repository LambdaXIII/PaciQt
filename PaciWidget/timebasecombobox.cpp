#include "timebasecombobox.h"

TimebaseComboBox::TimebaseComboBox(QWidget *parent): QComboBox(parent)
{
  this->addItems(Timebase::profiles());
  setCurrentText("24");
  connect(this, &TimebaseComboBox::currentProfileChanged, this, &TimebaseComboBox::currentTextChanged);
}

QString TimebaseComboBox::currentProfile() const
{
  return currentText();
}

Timebase* TimebaseComboBox::currentTimebase() const
{
  return Timebase::fromProfile(currentText());
}
