#include "multisaver.h"
#include <QProgressDialog>
#include <QInputDialog>
#include <QApplication>
#include "fcp7xmlsaver.h"
#include "textsaver.h"
#include "csvsaver.h"

Multisaver::Multisaver(SeqPtr sequence_ptr, QString _path, QString _selectedFilter, QObject *parent)
  : QObject(parent), m_filename(_path), m_sequence(sequence_ptr)
{
  m_format = searchFormat(_selectedFilter);

  workSaver = Multisaver::saverMap[m_format](sequence(), filename());
}


Multisaver::~Multisaver()
{
//  workThread.quit();
//  workThread.wait();
  workSaver->deleteLater();
}

const QMap<Format, std::function<BaseSaver*(SeqPtr, QString)>> Multisaver::saverMap = {
  {PlainText, &createInstance<TextSaver>},
  {Fcp7Xml, &createInstance<Fcp7XMLSaver>},
  {Csv, &createInstance<CsvSaver>}
};

const QMap<Format, std::function<void(BaseSaver*)>> Multisaver::setupMap = {
  {Fcp7Xml, &Multisaver::setupFcp7Xml},
  {Csv, &Multisaver::setupCsv}
};

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

QString Multisaver::getAllFilters()
{
  QStringList xs;
  for (Format a : Multisaver::saverMap.keys()) {
    xs << FormatProfile::getFilter(a);
  }
  return xs.join(";;");
}


void Multisaver::setupFcp7Xml(BaseSaver *saver)
{
  Fcp7XMLSaver *s = qobject_cast<Fcp7XMLSaver*>(saver);
  QMap<QString, bool> map {{tr("空心字"), true}, {tr("普通文本"), false}};
  QString res = QInputDialog::getItem(QApplication::focusWidget(), tr("想导出哪种字幕？"), tr("请选择字幕生成器类型"), map.keys());
  s->setUseOutlineText(map[res]);
}

void Multisaver::setupCsv(BaseSaver *saver)
{
  CsvSaver *s = qobject_cast<CsvSaver*>(saver);
  QStringList xs;
  xs << tr("时间码") << tr("帧数");
  QString res = QInputDialog::getItem(QApplication::focusWidget(), tr("时间的表示方式"), tr("选择时间的保存方式"), xs);
  s->setUseTimecode(res == tr("时间码"));
}
