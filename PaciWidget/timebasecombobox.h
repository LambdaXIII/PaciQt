#ifndef TIMEBASECOMBOBOX_H
#define TIMEBASECOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include "timebase.h"

class TimebaseComboBox : public QComboBox
{
  Q_OBJECT
public:
  explicit TimebaseComboBox(QWidget *parent = nullptr);

  QString currentProfile() const;
  Timebase* currentTimebase() const;

signals:
  void currentProfileChanged(QString &profile);
};

#endif // TIMEBASECOMBOBOX_H
