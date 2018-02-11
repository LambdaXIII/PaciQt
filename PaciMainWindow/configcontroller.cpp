#include "configcontroller.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
//#include "candy_macros.h"

ConfigController::ConfigController(QObject *parent) : QObject(parent)
{}

const QString ConfigController::warningGroup = "warnings";
const QString ConfigController::uiGroup = "ui";

void ConfigController::resetWarnings()
{
  QSettings s;
  s.beginGroup(warningGroup);
  s.remove("");
  qDebug() << "[ConfigController] All warnings reset.";
  s.endGroup();
}

QString ConfigController::lastFileDialogPath()
{
  QSettings s;
  s.beginGroup(uiGroup);
  QString p = s.value("lastFileDialogPath").toString();
  if (p.isEmpty())
    s.setValue("lastFileDialogPath", QDir::homePath());
  return s.value("lastFileDialogPath").toString();
}

void ConfigController::setLastFileDialogPath(QString x)
{
  QFileInfo f(x);
  QString res = f.isDir() ? f.absolutePath() : f.dir().absolutePath();
  QSettings s;
  s.beginGroup(uiGroup);
  s.setValue("lastFileDialogPath", res);
  s.endGroup();
}
