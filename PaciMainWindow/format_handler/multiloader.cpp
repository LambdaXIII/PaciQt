#include "multiloader.h"
//#include <QThread>
#include <QProgressDialog>
#include <QApplication>
#include <QDebug>
#include <QLabel>
#include "fcp7xmlloader.h"
#include "csvloader.h"

#include "widgets/csvoptiondialog.h"


using namespace FormatProfile;




Multiloader::Multiloader(QString _path, QString _selectedFilter, QObject *parent)
  : QObject(parent), m_filename(_path)
{
  m_format = searchFormat(_selectedFilter);
  workLoader = Multiloader::functionMap[m_format](filename());
//  workLoader->moveToThread(&workThread);
//  connect(&workThread, &QThread::finished, workLoader, &BaseLoader::deleteLater);
//  connect(&workThread, &QThread::started, workLoader, &BaseLoader::doWork);
//  connect(workLoader, &BaseLoader::resultReady, this, &Multiloader::saveResult);
}

Multiloader::~Multiloader()
{
//  workThread.quit();
//  workThread.wait();
  workLoader->deleteLater();
}

const QMap<Format, std::function<BaseLoader*(QString)>> Multiloader::functionMap =  {
  {PlainText, &createInstance<TextLoader>},
  {Fcp7Xml, &createInstance<Fcp7XMLLoader>},
  {Csv, &createInstance<CsvLoader>}
};

const QMap<Format, std::function<void(BaseLoader*)>> Multiloader::setupMap = {
  {Csv, &Multiloader::setupCsv},
};


QString Multiloader::getAllFilters()
{
  QStringList xs;
  for (Format a : Multiloader::functionMap.keys()) {
    xs << FormatProfile::getFilter(a);
  }
  return xs.join(";;");
}

QSharedPointer<Sequence> Multiloader::getSequence()
{
  if (Multiloader::setupMap.keys().contains(m_format)) {
    auto setupFun = Multiloader::setupMap[m_format];
    setupFun(workLoader);
  }

  QProgressDialog progress(tr("正在解析..."), tr("停止"), 0, 100);
  progress.setWindowModality(Qt::WindowModal);
  progress.setWindowFlags(Qt::Tool);

  QLabel *label = new QLabel();
  label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  progress.setLabel(label);

  connect(workLoader, &BaseLoader::totalProgressUpdated, &progress, &QProgressDialog::setMaximum);
  connect(workLoader, &BaseLoader::currentProgressUpdated, &progress, &QProgressDialog::setValue);
  connect(workLoader, &BaseLoader::messageUpdated, &progress, &QProgressDialog::setLabelText);
  connect(&progress, &QProgressDialog::canceled, workLoader, &BaseLoader::cancelWork);

  Sequence *result_sequence = workLoader->doWork();
//  connect(workLoader, &BaseLoader::resultReady, [&](Sequence * x) {
//    result_sequence = x;
//  });
//  workThread.start();
//  workThread.wait();
  return QSharedPointer<Sequence>(result_sequence);
}

void Multiloader::setupCsv(BaseLoader *loader)
{
  CsvLoader *s = qobject_cast<CsvLoader*>(loader);
  auto *dialog = new CsvOptionDialog(CsvOptionDialog::Loading, QApplication::focusWidget());
  dialog->exec();
  s->setTimebase(dialog->getTimebase());
  s->setUseTimecode(dialog->getUseTimecode());
  dialog->deleteLater();
}
