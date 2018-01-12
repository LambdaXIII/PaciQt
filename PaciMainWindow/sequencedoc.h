#ifndef SEQUENCEDOC_H
#define SEQUENCEDOC_H

#include <QObject>
#include <QSharedPointer>
#include "sequence.h"
#include "candy_macros.h"
#include "format_handler/formatprofile.h"

class SequenceDoc : public QObject
{
  Q_OBJECT
  CANDY_PROPERTY_RO_VALUE(bool, edited, false)
  CANDY_PROPERTY_RO(QString, currentFilename)
  CANDY_PROPERTY_RO(QSharedPointer<Sequence>, sequence)
  CANDY_PROPERTY(QString, currentFormatFilter, CurrentFormatFilter)

public:
  ~SequenceDoc();
  static SequenceDoc* instance();
  explicit SequenceDoc(QObject *parent = nullptr);

  void setCurrentFilename(QString v);
  void setSequence(QSharedPointer<Sequence> s);

private:
  void init();
  static SequenceDoc *self;

signals:
  void sequenceOpened();
  void sequenceSaved();
  void sequenceCreated();
  void editedChanged(bool e);
  void currentFilenameChanged(QString f);
  void sequenceChanged(QSharedPointer<Sequence> s);


public slots:
  void open();
  void save();
  void saveAs();
  void create();
  void setEdited(bool v);
  void justEdited();

};

#define GlobalDocument SequenceDoc::instance()
#define GlobalSequence GlobalDocument->sequence()

#endif // SEQUENCEDOC_H
