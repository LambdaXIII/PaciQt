#ifndef CLIPSTABLE_H
#define CLIPSTABLE_H

#include <QObject>
#include <QWidget>
#include <QTableView>

class ClipsTable : public QTableView
{
public:
  explicit ClipsTable(QWidget *parent = nullptr);

public slots:
  void acceptNewTrackIndex(int x);
};

#endif // CLIPSTABLE_H
