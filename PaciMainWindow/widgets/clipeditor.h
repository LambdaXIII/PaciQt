#ifndef CLIPEDITOR_H
#define CLIPEDITOR_H

#include <QWidget>
#include "sequencedoc.h"

namespace Ui {
class ClipEditor;
}

class ClipEditor : public QWidget
{
  Q_OBJECT

public:
  explicit ClipEditor(QWidget *parent = 0);
  ~ClipEditor();

private:
  Ui::ClipEditor *ui;

protected:
  Clip *m_currentClip;
  int m_currentIndex;

signals:
  void editingDone(int row, QString content);

public slots:
  void whenSequenceChanged();
  void editClip(int row, Clip *clip);
  void applyEditing();
};

#endif // CLIPEDITOR_H
