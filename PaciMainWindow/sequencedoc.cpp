#include "sequencedoc.h"

#include "format_handler/multiloader.h"
#include "format_handler/multisaver.h"
#include "format_handler/formatprofile.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QApplication>
#include <QDebug>
#include "configcontroller.h"
#include "candy_macros.h"

SequenceDoc::SequenceDoc(QObject *parent) : QObject(parent)
{
  init();
}

void SequenceDoc::init()
{
  Q_ASSERT_X(!self, "SequenceDoc", "Only need one.");
  self = this;
}

SequenceDoc::~SequenceDoc()
{}

SequenceDoc* SequenceDoc::instance()
{
  return self;
}

SequenceDoc* SequenceDoc::self = 0;

void SequenceDoc::open()
{
  QString selectedFilter;
  auto filePath = QFileDialog::getOpenFileName(QApplication::focusWidget(), tr("打开文件"), ConfigController::lastFileDialogPath(), Multiloader::getAllFilters(), &selectedFilter);

  if (! filePath.isEmpty()) {
    setCurrentFormatFilter(selectedFilter);
    Multiloader loader(filePath, selectedFilter);
    setSequence(loader.getSequence());

//    if (filePath.endsWith(".paci")) {
    setCurrentFilename(filePath);
    setEdited(false);
//    } else {
//      setCurrentFilename("");
//      setEdited(true);
//    }
    emit sequenceOpened();

    ConfigController::setLastFileDialogPath(filePath);
  }
}

void SequenceDoc::save()
{
  if (currentFilename().isEmpty() || (FormatProfile::searchFormat(currentFormatFilter()) != FormatProfile::Paci)) {
    CANDY_DEBUG << "Redirecting to save as...";
    saveAs();
  } else {
    if (edited()) {
      CANDY_DEBUG << "Silent save paci file:" << currentFilename();
      Multisaver saver(sequence(), currentFilename());
      saver.save();
      setEdited(false);
      emit sequenceSaved();
    }
  }
}

void SequenceDoc::saveAs()
{
  QString selectedFilter;
  auto filename = QFileDialog::getSaveFileName(QApplication::focusWidget(), tr("保存文件"), ConfigController::lastFileDialogPath(), Multisaver::getAllFilters(), &selectedFilter);

  if (! filename.isEmpty()) {
    setCurrentFormatFilter(selectedFilter);
    Multisaver saver(sequence(), filename, selectedFilter);
    saver.save();
    setEdited(false);
    emit sequenceSaved();
    setCurrentFilename(filename);
    emit sequenceOpened();
    CANDY_DEBUG << "New file:" << filename << "saved.";

    ConfigController::setLastFileDialogPath(filename);
  }
}

void SequenceDoc::create()
{
  QString sequenceName = QInputDialog::getText(QApplication::focusWidget(), tr("序列名称"), tr("请输入序列名"));
  setSequence(QSharedPointer<Sequence>::create(sequenceName));
  setCurrentFilename("");
  setEdited(true);
  emit sequenceCreated();
  CANDY_DEBUG << "New sequence" << sequenceName << "created.";
}

void SequenceDoc::setCurrentFilename(QString v)
{
  if (m_currentFilename != v) {
    m_currentFilename = v;
    emit currentFilenameChanged(v);
  }
}

void SequenceDoc::setSequence(QSharedPointer<Sequence> s)
{
  if (m_sequence != s) {
    m_sequence = s;
    emit sequenceChanged(m_sequence);
    CANDY_DEBUG << "New Sequence" << m_sequence->sequenceName() << "setted.";
  }
}

void SequenceDoc::setEdited(bool v)
{
  if (m_edited != v) {
    m_edited = v;
    emit editedChanged(m_edited);
  }
}

void SequenceDoc::justEdited()
{
  setEdited(true);
}
