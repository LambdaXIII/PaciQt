#ifndef SEQUENCEDOC_H
#define SEQUENCEDOC_H

#include <QObject>

class SequenceDoc : public QObject
{
  Q_OBJECT
public:
  ~SequenceDoc();
  static SequenceDoc* instance();

private:
  void init();
  static SequenceDoc *self;
  explicit SequenceDoc(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SEQUENCEDOC_H
