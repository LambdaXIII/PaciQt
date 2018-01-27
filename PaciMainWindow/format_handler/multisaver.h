#ifndef MULTISAVER_H
#define MULTISAVER_H

#include <QObject>
#include <QSharedPointer>
#include <QThread>
#include "formatprofile.h"
#include "candy_macros.h"
#include "sequence.h"
#include "base/basesaver.h"


using namespace FormatProfile;

typedef QSharedPointer<Sequence> SeqPtr;

template<class T> BaseSaver* createInstance(SeqPtr seq, QString _path)
{
  return new T(seq.data(), _path);
}


class Multisaver : public QObject
{
  Q_OBJECT
  CANDY_PROPERTY_RO(QString, filename)
  CANDY_PROPERTY_RO(SeqPtr, sequence)
  CANDY_PROPERTY_RO(Format, format)

public:
  explicit Multisaver(SeqPtr sequence_ptr, QString _path, QString _selectedFilter, QObject *parent = nullptr);
  ~Multisaver();

  const static QMap<Format, std::function<BaseSaver*(SeqPtr, QString)>> saverMap;

  const static QMap<Format, std::function<void(BaseSaver*)>> setupMap;

  static QString getAllFilters();

protected:
  BaseSaver *workSaver;
//  QThread workThread;

  static void setupText(BaseSaver *saver);
  static void setupFcp7Xml(BaseSaver *saver);
  static void setupCsv(BaseSaver *saver);
  static void setupSrt(BaseSaver *saver);

  void showInfomation();

signals:

public slots:
  void save();
};

#endif // MULTISAVER_H
