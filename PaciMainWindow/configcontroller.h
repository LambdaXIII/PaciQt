#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include <QObject>
#include <QSettings>

class ConfigController : public QObject
{
  Q_OBJECT
public:
  explicit ConfigController(QObject *parent = nullptr);

  static const QString warningGroup;
  static const QString uiGroup;

  static void resetWarnings();

  static QString lastFileDialogPath();
  static void setLastFileDialogPath(QString x);

signals:

public slots:

};

#endif // CONFIGCONTROLLER_H
