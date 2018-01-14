#ifndef CLIPSTABLEMODEL_H
#define CLIPSTABLEMODEL_H

#include <QAbstractTableModel>
#include "track.h"


class ClipsTableModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  explicit ClipsTableModel(QObject *parent = nullptr, int index = 0);

  Track* currentTrack() const;

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  // Add data:
  bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//  bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

  // Remove data:
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
//  bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

private:
  int m_trackIndex;
  QStringList m_headers;
  bool m_showTC;
  QString tcConvert(int frames) const;

public slots:
  void setShowTC(bool x);
};

#endif // CLIPSTABLEMODEL_H
