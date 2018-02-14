#include "clipeditor.h"
#include "ui_clipeditor.h"

ClipEditor::ClipEditor(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ClipEditor)
{
  ui->setupUi(this);
  setVisible(false);
  connect(GlobalDocument, &SequenceDoc::sequenceChanged, this, &ClipEditor::whenSequenceChanged);
  connect(ui->okButton, &QPushButton::clicked, this, &ClipEditor::applyEditing);
}

ClipEditor::~ClipEditor()
{
  delete ui;
}

void ClipEditor::whenSequenceChanged()
{
  ui->startTC->setTimebase(GlobalSequence->timebase());
  ui->endTC->setTimebase(GlobalSequence->timebase());
}

void ClipEditor::editClip(int row, Clip *clip)
{
  m_currentClip = clip;
  m_currentIndex = row;
  ui->startTC->setFrames(m_currentClip->startPoint());
  ui->endTC->setFrames(m_currentClip->endPoint());
  ui->currentTextField->document()->setPlainText(m_currentClip->content());
  setVisible(true);
}

void ClipEditor::applyEditing()
{
  QString res = ui->currentTextField->document()->toPlainText();
  if (m_currentClip->content() != res) {
    emit editingDone(m_currentIndex, ui->currentTextField->document()->toPlainText());
  }
  setVisible(false);
}
