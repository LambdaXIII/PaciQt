#ifndef CLIPSTABLE_H
#define CLIPSTABLE_H

#include <QObject>
#include <QWidget>
#include <QTableView>
#include "candy_macros.h"

class ClipsTable : public QTableView
{


public:
  explicit ClipsTable(QWidget *parent = nullptr);

public slots:
  void acceptNewTrackIndex(int x);
  void showTC(bool x);
};

#endif // CLIPSTABLE_H
