#ifndef MULTILOADER_H
#define MULTILOADER_H

#include <QObject>
#include <QSharedPointer>
#include <QThread>
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
  CANDY_PROPERTY_RO(Format, format)

public:
  Multiloader(QString _path, QString _selectedFilter, QObject *parent = nullptr);
  ~Multiloader();

  const static QMap<Format, std::function<BaseLoader*(QString)>> functionMap;

  const static QMap<Format, std::function<void(BaseLoader*)>> setupMap;

  QSharedPointer<Sequence> getSequence();

  static QString getAllFilters();

signals:


public slots:


protected:
  BaseLoader *workLoader;

  static void setupCsv(BaseLoader *loader);

}; //namespace Multiloader

#endif // MULTILOADER_H
