#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include <QObject>

class ConfigController : public QObject
{
  Q_OBJECT
public:
  explicit ConfigController(QObject *parent = nullptr);

  static const QString warningGroup;

  static void resetWarnings();
signals:

public slots:

};

#endif // CONFIGCONTROLLER_H
