#include "sequencedoc.h"

#include "format_handler/multiloader.h"
#include "format_handler/multisaver.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QApplication>

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
  auto filePath = QFileDialog::getOpenFileName(QApplication::focusWidget(), tr("打开文件"), QDir::homePath(), FormatProfile::getAllFilters(), &selectedFilter);

  if (! filePath.isEmpty()) {
    setCurrentFormatFilter(selectedFilter);
    Multiloader loader(filePath, selectedFilter);
    setSequence(loader.getSequence());
    setCurrentFilename(filePath);
    setEdited(false);
    emit sequenceOpened();
  }
}

void SequenceDoc::save()
{
  if (currentFilename().isEmpty()) {
    saveAs();
  } else {
    if (edited()) {
      Multisaver saver(sequence(), currentFilename(), currentFormatFilter());
      saver.save();
      setEdited(false);
      emit sequenceSaved();
    }
  }
}

void SequenceDoc::saveAs()
{
  QString selectedFilter;
  auto filename = QFileDialog::getSaveFileName(QApplication::focusWidget(), tr("保存文件"), QDir::homePath(), FormatProfile::getAllFilters(), &selectedFilter);

  if (! filename.isEmpty()) {
    setCurrentFormatFilter(selectedFilter);
    Multisaver saver(sequence(), filename, selectedFilter);
    saver.save();
    setEdited(false);
    emit sequenceSaved();
    setCurrentFilename(filename);
    emit sequenceOpened();
  }
}

void SequenceDoc::create()
{
  QString sequenceName = QInputDialog::getText(QApplication::focusWidget(), tr("序列名称"), tr("请输入序列名"));
  setSequence(QSharedPointer<Sequence>::create(sequenceName));
  setCurrentFilename("");
  setEdited(true);
  emit sequenceCreated();
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
