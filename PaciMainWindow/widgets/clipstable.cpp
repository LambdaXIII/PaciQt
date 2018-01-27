#include "clipstable.h"
#include "clipstablemodel.h"
#include <QPainter>
#include <QDebug>

ClipsTable::ClipsTable(QWidget *parent)
  : QTableView(parent)
{
  connect(this, &ClipsTable::doubleClicked, this, &ClipsTable::resendDoubleClip);
}

void ClipsTable::paintEvent(QPaintEvent *event)
{
  QTableView::paintEvent(event);
  if ((!model()) || this->model()->rowCount() == 0) {
    QPainter painter(this->viewport());
    painter.setFont(QFont("Heiti SC", 15));
    painter.setPen(QPen(Qt::black));
    painter.drawText(rect(), Qt::AlignCenter, tr("没东西呀"));
  }
}

void ClipsTable::acceptNewTrackIndex(int x)
{
//  qDebug() << "Accept new trackindex:" << x;
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

void ClipsTable::resendDoubleClip(const QModelIndex &index)
{
  int row = index.row();
  auto m = qobject_cast<ClipsTableModel*>(model());
  Clip *c = m->currentTrack()->at(row);
  emit clipDoubleClicked(row, c);
}

void ClipsTable::setContent(int row, QString content)
{
  auto m = qobject_cast<ClipsTableModel*>(model());
  m->setContent(row, content);
}
