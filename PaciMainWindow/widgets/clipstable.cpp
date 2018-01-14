#include "clipstable.h"
#include "clipstablemodel.h"
#include <QDebug>

ClipsTable::ClipsTable(QWidget *parent)
  : QTableView(parent)
{

}


void ClipsTable::acceptNewTrackIndex(int x)
{
  qDebug() << "Accept new trackindex:" << x;
  auto old = model();
  setModel(new ClipsTableModel(this, x));
  old->deleteLater();
}

void ClipsTable::showTC(bool x)
{
  if (model()) {
    auto a = qobject_cast<ClipsTableModel*>( model());
    a->setShowTC(x);

  }
}
