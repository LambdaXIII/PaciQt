#include "usetimecodeselector.h"
#include <QVBoxLayout>

UseTimecodeSelector::UseTimecodeSelector(QWidget *parent) : QWidget(parent)
{
  useTimecodeButton = new QRadioButton(tr("使用时间码"), this);
  useFrameButton = new QRadioButton(tr("使用帧数"), this);

  useFrameButton->setChecked(true);
  useTimecodeButton->setChecked(false);

  auto *layout = new QVBoxLayout(this);
  setLayout(layout);
  layout->addWidget(useFrameButton);
  layout->addWidget(useTimecodeButton);

  connect(useTimecodeButton, &QRadioButton::toggled, this, &UseTimecodeSelector::useTimecodeChanged);
//  connect(useFrameButton,&QRadioButton::toggled,this,&UseTimecodeSelector::handleCheckedAction);
}


bool UseTimecodeSelector::useTimecode() const
{
  return useTimecodeButton->isChecked();
}

void UseTimecodeSelector::setUseTimecode(bool x)
{
  if (useTimecodeButton->isChecked() != x)
    useTimecodeButton->setChecked(x);
}
