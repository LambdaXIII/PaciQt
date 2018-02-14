#include "trackselector.h"
#include "ui_trackselector.h"

TrackSelector::TrackSelector(Sequence* _seq, QWidget *parent) :
  QDialog(parent), m_sequence(_seq),
  ui(new Ui::TrackSelector)
{
  ui->setupUi(this);
  buttonGroup = new QButtonGroup(this);
  setupButtons();

  connect(ui->okButton, &QPushButton::clicked, this, &TrackSelector::accept);
}

TrackSelector::~TrackSelector()
{
  delete ui;
}

void TrackSelector::setupButtons()
{
  /*
  foreach (QAbstractButton *b, buttonGroup->buttons()) {
    b->deleteLater();
    buttonGroup->removeButton(b);
  }
  */
  TrackBox *box = sequence()->trackBox();

  if (! box->isEmpty()) {
    for (int x = 0; x < box->size(); x++) {
      auto b = new TrackSelectorButton(x, box->at(x), this);
      buttonGroup->addButton(b);
      ui->trackButtonAreaLayout->addWidget(b);
      connect(b, &TrackSelectorButton::toggled, this, &TrackSelector::handleToggle);
    }
  }

}

void TrackSelector::handleToggle()
{
  TrackSelectorButton *button = qobject_cast<TrackSelectorButton*>(buttonGroup->checkedButton());
  m_currentTrackIndex = button->trackIndex();
}

void TrackSelector::setQuestion(QString s)
{
  ui->questionLabel->setText(s);
}

QString TrackSelector::question()
{
  return ui->questionLabel->text();
}

int TrackSelector::getSelectedTrackIndex(Sequence *_seq, QWidget *parent)
{
  int result = 0;
  if (_seq->trackBox()->size() > 1) {
    auto dialog = new TrackSelector(_seq, parent);
    dialog->exec();
    result = dialog->currentTrackIndex();
    dialog->deleteLater();
  }
  return result;
}

Track* TrackSelector::getSelectedTrack(Sequence *_seq, QWidget *parent)
{
  int i = 0;
  if (_seq->trackBox()->size() > 1) {
    auto dialog = new TrackSelector(_seq, parent);
    dialog->exec();
    i = dialog->currentTrackIndex();
    dialog->deleteLater();
  }
  return _seq->trackBox()->at(i);
}
