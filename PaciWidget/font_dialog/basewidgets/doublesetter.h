#ifndef DOUBLESETTER_H
#define DOUBLESETTER_H

#include <QWidget>
#include <QDoubleSpinBox>
#include "candy_macros.h"

class DoubleSetter : public QDoubleSpinBox
{
  Q_OBJECT
  CANDY_PROPERTY_RO(double, defaultValue)

public:
  explicit DoubleSetter(double _min, double _max, double _def, double _cur, QWidget *parent = nullptr);

signals:

public slots:
};

#endif // DOUBLESETTER_H
