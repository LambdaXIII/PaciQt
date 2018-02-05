#include "doublesetter.h"

DoubleSetter::DoubleSetter(double _min, double _max, double _def, double _cur, QWidget *parent)
  : QDoubleSpinBox(parent), m_defaultValue(_def)
{
  setMaximum(_max);
  setMinimum(_min);
  setValue(_cur);
}
