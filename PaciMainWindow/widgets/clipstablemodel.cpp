#include "clipstablemodel.h"
#include "sequencedoc.h"
#include "timebase.h"
#include "configcontroller.h"

ClipsTableModel::ClipsTableModel(QObject *parent, int index)
  : QAbstractTableModel(parent), m_trackIndex(index), m_showTC(false)
{
  m_headers << tr("开始时间") << tr("结束时间") << tr("内容");
  QSettings set;
  m_showTC = set.value(ConfigController::uiGroup + "/table_show_tc").toBool();
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
      return tcConvert(clip->startPoint());
    }
    if (col == 1) {
      return tcConvert(clip->endPoint());
    }
    if (col == 2) {
      return clip->content();
    }
  }

  if (role == Qt::TextAlignmentRole) {
    if (col <= 1)
      return Qt::AlignCenter;
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

QString ClipsTableModel::tcConvert(int frames) const
{
  if (m_showTC) {
    return Timebase::frameToTimecode(frames, GlobalSequence->timebase());
  } else {
    return QString::number(frames);
  }
}

void ClipsTableModel::setShowTC(bool x)
{
  if (x != m_showTC) {
    m_showTC = x;
    QSettings s;
    s.setValue(ConfigController::uiGroup + "/table_show_tc", x);
    emit dataChanged(index(0, 0), index(rowCount(), 1));
  }
}

void ClipsTableModel::setContent(int row, QString new_content)
{
  if (currentTrack()->at(row)->content() != new_content) {
    currentTrack()->at(row)->setContent(new_content);
    GlobalDocument->justEdited();
    emit dataChanged(index(row, 2), index(row, 2), {Qt::DisplayRole});
  }
}
