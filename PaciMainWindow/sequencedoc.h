#ifndef SEQUENCEDOC_H
#define SEQUENCEDOC_H

#include <QObject>
#include <QSharedPointer>
#include "sequence.h"

class SequenceDoc : public QObject
{
  Q_OBJECT
public:
  ~SequenceDoc();
  static SequenceDoc* instance();
  explicit SequenceDoc(QObject *parent = nullptr);

  inline bool edited()
  {
    return m_edited;
  }

  inline QString currentFilename()
  {
    return m_currentFilename;
  }

  inline QSharedPointer<Sequence> sequence()
  {
    return m_sequence;
  }



private:
  void init();
  static SequenceDoc *self;

  bool m_edited;
  QString m_currentFilename;

  QSharedPointer<Sequence> m_sequence;


signals:
  void sequenceOpened();
  void sequenceSaved();
  void sequenceCreated();
  void editedChanged(bool e);
  void currentFilenameChanged(QString f);
  void sequenceChanged();


public slots:
  void open(QString filenaame);
  void save();
  void saveAs(QString filename);
  void create();
  void setEdited(bool v);
  void justEdited();
  void setCurrentFilename(QString v);
  void setSequence(QSharedPointer<Sequence> s);
};

#define GlobalDocument SequenceDoc::instance()

#endif // SEQUENCEDOC_H
