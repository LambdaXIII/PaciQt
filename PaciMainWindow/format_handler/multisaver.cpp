#include "multisaver.h"
#include <QProgressDialog>
#include <QInputDialog>
#include <QApplication>
#include <QMessageBox>
#include <QSettings>
#include "configcontroller.h"
#include "fcp7xmlsaver.h"
#include "textsaver.h"
#include "csvsaver.h"
#include "srtsaver.h"
#include "widgets/csvoptiondialog.h"
#include "widgets/trackselector.h"

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
  {Csv, &createInstance<CsvSaver>},
  {Srt, &createInstance<SrtSaver>}
};

const QMap<Format, std::function<void(BaseSaver*)>> Multisaver::setupMap = {
  {Fcp7Xml, &Multisaver::setupFcp7Xml},
  {Csv, &Multisaver::setupCsv},
  {Srt, &Multisaver::setupSrt}
};

void Multisaver::showInfomation()
{
  auto info = workSaver->info();
  auto setting_key = formatNames[format()] + "_saver_info_showed";
  if (! info.isEmpty()) {
    QSettings settings;
    settings.beginGroup(ConfigController::warningGroup);
    if (! settings.value(setting_key).toBool()) {
      QMessageBox::information(QApplication::focusWidget(), tr("重要提示"), info, QMessageBox::Ok);
      settings.setValue(setting_key, true);
    }
    settings.endGroup();
  }
}

void Multisaver::save()
{
  showInfomation();

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

void Multisaver::setupText(BaseSaver *saver)
{
  TextSaver *s = qobject_cast<TextSaver*>(saver);
  s->setTrackIndex(TrackSelector::getSelectedTrackIndex(saver->sequence(), QApplication::focusWidget()));
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
  s->setTrackIndex(TrackSelector::getSelectedTrackIndex(saver->sequence(), QApplication::focusWidget()));
  auto *dialog = new CsvOptionDialog(CsvOptionDialog::Saving, QApplication::focusWidget());
  dialog->exec();
  s->setUseTimecode(dialog->getUseTimecode());
  dialog->deleteLater();
}

void Multisaver::setupSrt(BaseSaver *saver)
{
  SrtSaver *s = qobject_cast<SrtSaver*>(saver);

  if (s->sequence()->trackBox()->size() > 1) {
    auto export_all = QMessageBox::question(
                        QApplication::focusWidget(),
                        tr("导出全部轨道吗？"),
                        tr("因为 SRT 字幕支持字幕叠加，所以是否要导出全部轨道？"), QMessageBox::Yes, QMessageBox::No);
    if (export_all == QMessageBox::Yes) {
      s->setTrackIndex(-1);
    } else {
      s->setTrackIndex(TrackSelector::getSelectedTrackIndex(saver->sequence()));
    }
  }
}
