#ifndef MULTILOADER_H
#define MULTILOADER_H

#include <QObject>
#include "formatprofile.h"
#include "candy_macros.h"
#include "sequence.h"
#include "textloader.h"


using namespace FormatProfile;

template<class T> BaseLoader* createInstance(QString _path)
{
  return new T(_path);
}

class Multiloader
  : public QObject
{
  Q_OBJECT
  CANDY_PROPERTY_RO(QString, filename)

public:
  Multiloader(QString _path, QString _selectedFilter, QObject *parent = nullptr);

  const static QMap<Format, std::function<BaseLoader*(QString)>> functionMap;

protected:
  BaseLoader *loader;

}; //namespace Multiloader

#endif // MULTILOADER_H
