#include "configcontroller.h"
#include <QSettings>
#include <QDebug>

ConfigController::ConfigController(QObject *parent) : QObject(parent)
{

}

const QString ConfigController::warningGroup = "warnings";

void ConfigController::resetWarnings()
{
  QSettings s;
  s.beginGroup(warningGroup);
  s.remove("");
  qDebug() << "[ConfigController] All warnings reset.";
  s.endGroup();
}
