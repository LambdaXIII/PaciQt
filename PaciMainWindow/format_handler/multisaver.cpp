#include "multisaver.h"
#include <QProgressDialog>


Multisaver::Multisaver(SeqPtr sequence_ptr, QString _path, QString _selectedFilter, QObject *parent)
  : QObject(parent), m_filename(_path), m_sequence(sequence_ptr)
{
  m_format = searchFormat(_selectedFilter);

  workSaver = Multisaver::saverMap[m_format](sequence(), filename());
  workSaver->moveToThread(&workThread);
//  connect(&workThread, &QThread::started, workSaver, &BaseSaver::doWork);
//  connect(&workThread, &QThread::finished, workSaver, &BaseSaver::deleteLater);


}


Multisaver::~Multisaver()
{
//  workThread.quit();
//  workThread.wait();
  workSaver->deleteLater();
}

const QMap<Format, std::function<BaseSaver*(SeqPtr, QString)>> Multisaver::saverMap = {
  {PlainText, &createInstance<TextSaver>},
};

const QMap<Format, std::function<void(BaseSaver*)>> Multisaver::setupMap = {};

void Multisaver::save()
{
  if (Multisaver::setupMap.keys().contains(m_format)) {
    auto setupFun = Multisaver::setupMap[m_format];
    setupFun(workSaver);
  }

  QProgressDialog progress(tr("正在保存..."), tr("停止"), 0, 100);
  connect(workSaver, &BaseSaver::totalProgressUpdated, &progress, &QProgressDialog::setMaximum);
  connect(workSaver, &BaseSaver::currentProgressUpdated, &progress, &QProgressDialog::setValue);
  connect(workSaver, &BaseSaver::messageUpdated, &progress, &QProgressDialog::setLabelText);
  connect(&progress, &QProgressDialog::canceled, workSaver, &BaseSaver::cancelWork);

//  workThread.start();
//  workThread.wait();

  workSaver->doWork();
}
