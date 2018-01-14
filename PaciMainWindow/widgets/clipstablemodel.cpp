#include "clipstablemodel.h"
#include "sequencedoc.h"

ClipsTableModel::ClipsTableModel(QObject *parent, int index)
  : QAbstractTableModel(parent), m_trackIndex(index)
{
  m_headers << tr("开始时间") << tr("结束时间") << tr("内容");
}

Track* ClipsTableModel::currentTrack() const
{
  int i = m_trackIndex;
  if (m_trackIndex >= GlobalSequence->trackBox()->size())
    i = 0;
  return GlobalSequence->trackBox()->at(i);
}

QVariant ClipsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal) {
    if (role == Qt::DisplayRole) {
      return m_headers[section];
    }
  } else {
    if (role == Qt::DisplayRole)
      return section + 1;
  }
  return QVariant();
}

int ClipsTableModel::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;
  return currentTrack()->size();
}

int ClipsTableModel::columnCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;

  return m_headers.size();
}

QVariant ClipsTableModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  int row = index.row();
  int col = index.column();
  Clip *clip = (*currentTrack())[row];

  if (role == Qt::DisplayRole) {
    if (col == 0) {
      return clip->startPoint();
    }
    if (col == 1) {
      return clip->endPoint();
    }
    if (col == 2) {
      return clip->content();
    }
  }

  return QVariant();
}

bool ClipsTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
  beginInsertRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endInsertRows();
  return true;
}

bool ClipsTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
  beginRemoveRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endRemoveRows();
  return true;
}
