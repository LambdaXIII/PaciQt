#ifndef CLIPSTABLE_H
#define CLIPSTABLE_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include "candy_macros.h"
#include "clip.h"

class ClipsTable : public QTableView
{
  Q_OBJECT
public:
  explicit ClipsTable(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *event) override;

signals:
  void clipDoubleClicked(int row, Clip *clip);

public slots:
  void acceptNewTrackIndex(int x);
  void showTC(bool x);
  void setContent(int row, QString content);

protected slots:
  void resendDoubleClip(const QModelIndex &index);
};

#endif // CLIPSTABLE_H
