#ifndef VALUEWIDGETBASE_H
#define VALUEWIDGETBASE_H

template<class V>
class ValueWidgetBase
{
public:
  ValueWidgetBase(V default_value): m_defaultValue(default_value)
  {}

protected:
  V m_value;
  V m_defaultValue;

public:
  virtual void setValue(V x)
  {
    if (m_value != x) {
      m_value = x;
    }
  }

  virtual V value()
  {
    return m_value;
  }

  virtual V defaultValue()
  {
    return m_defaultValue;
  }

  virtual void resetValue()
  {
    setValue(defaultValue());
  }

}

#endif // VALUEWIDGETBASE_H
