#include "multiloader.h"
//#include <QThread>
#include <QProgressDialog>
#include <QApplication>
#include <QDebug>

using namespace FormatProfile;




Multiloader::Multiloader(QString _path, QString _selectedFilter, QObject *parent)
  : QObject(parent), m_filename(_path)
{
  m_format = searchFormat(_selectedFilter);
  workLoader = Multiloader::functionMap[m_format](filename());
  workLoader->moveToThread(&workThread);
  connect(&workThread, &QThread::finished, workLoader, &BaseLoader::deleteLater);
  connect(&workThread, &QThread::started, workLoader, &BaseLoader::doWork);
//  connect(workLoader, &BaseLoader::resultReady, this, &Multiloader::saveResult);
}

Multiloader::~Multiloader()
{
  workThread.quit();
  workThread.wait();
}

const QMap<Format, std::function<BaseLoader*(QString)>> Multiloader::functionMap =  {
  {PlainText, &createInstance<TextLoader>},
};

const QMap<Format, std::function<void(BaseLoader*)>> Multiloader::setupMap = {
  {PlainText, &Multiloader::setupPlainText},
};

/*
void Multiloader::saveResult(Sequence *result)
{
  m_result = result;
}
*/

QSharedPointer<Sequence> Multiloader::getSequence()
{
  if (Multiloader::setupMap.keys().contains(m_format)) {
    auto setupFun = Multiloader::setupMap[m_format];
    setupFun(workLoader);
  }

  QProgressDialog progress(tr("正在解析..."), tr("停止"), 0, 100);
  connect(workLoader, &BaseLoader::totalProgressUpdated, &progress, &QProgressDialog::setMaximum);
  connect(workLoader, &BaseLoader::currentProgressUpdated, &progress, &QProgressDialog::setValue);
  connect(workLoader, &BaseLoader::messageUpdated, &progress, &QProgressDialog::setLabelText);
  connect(&progress, &QProgressDialog::canceled, workLoader, &BaseLoader::cancelWork);
  Sequence *result_sequence;
  connect(workLoader, &BaseLoader::resultReady, [&](Sequence * x) {
    result_sequence = x;
  });
  workThread.start();
  workThread.wait();
  return QSharedPointer<Sequence>(result_sequence);
}

void Multiloader::setupPlainText(BaseLoader *loader)
{
  qDebug() << "普通文本导入器额外操作测试函数启动。";
}
