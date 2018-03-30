#include "pacimainwindow.h"
#include "ui_pacimainwindow.h"
#include "configcontroller.h"
#include <QFileDialog>
#include <QDebug>
#include "configcontroller.h"
#include "candy_macros.h"

#include "pacifontdesinerdialog.h"
#include <QDebug>

PaciMainWindow::PaciMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PaciMainWindow)
{
  ui->setupUi(this);
  ui->trackSideBar->setVisible(false);

  QSettings s;
  s.beginGroup(ConfigController::uiGroup);
  ui->actionShowTC->setChecked(s.value("table_show_tc").toBool());
  ui->actionSave->setDisabled(true);

  connect(GlobalDocument, &SequenceDoc::currentFilenameChanged, this, &PaciMainWindow::setWindowFilePath);

  connect(GlobalDocument, &SequenceDoc::editedChanged, ui->trackSideBar, &TrackSideBar::refresh);
  connect(GlobalDocument, &SequenceDoc::sequenceChanged, ui->trackSideBar, &TrackSideBar::refresh);
  connect(GlobalDocument, &SequenceDoc::editedChanged, ui->actionSave, &QAction::setEnabled);
  connect(GlobalDocument, &SequenceDoc::sequenceOpened, [&]() {
    ui->actionSetupFont->setEnabled(true);
  });

  connect(ui->trackSideBar, &TrackSideBar::trackSelected, ui->clipsTable, &ClipsTable::acceptNewTrackIndex);

  connect(ui->actionTest, &QAction::triggered, this, &PaciMainWindow::run_test);

  connect(ui->actionCreate, &QAction::triggered, GlobalDocument, &SequenceDoc::create);
  connect(ui->actionOpen, &QAction::triggered, GlobalDocument, &SequenceDoc::open);
  connect(ui->actionSave, &QAction::triggered, GlobalDocument, &SequenceDoc::save);
  connect(ui->actionSaveAs, &QAction::triggered, GlobalDocument, &SequenceDoc::saveAs);

  connect(ui->actionShowTC, &QAction::triggered, ui->clipsTable, &ClipsTable::showTC);

  connect(ui->actionSetupFont, &QAction::triggered, this, &PaciMainWindow::setupFont);

  connect(ui->clipsTable, &ClipsTable::clipDoubleClicked, ui->clipEditor, &ClipEditor::editClip);
  connect(ui->clipEditor, &ClipEditor::editingDone, ui->clipsTable, &ClipsTable::setContent);

  connect(ui->actionResetWarnings, &QAction::triggered, &ConfigController::resetWarnings);

}

PaciMainWindow::~PaciMainWindow()
{
  delete ui;
}


void PaciMainWindow::run_test()
{
  auto a = new PaciFontDesinerDialog(GlobalSequence->fontInfo(), this);
  a->show();
}

void PaciMainWindow::setupFont()
{
  auto d = new PaciFontDesinerDialog(GlobalSequence->fontInfo(), this);
  d->exec();
  if (d->result() == QDialog::Accepted) {
    GlobalSequence->fontInfo()->deleteLater();
    GlobalSequence->setFontInfo(d->currentFontInfo());
    GlobalDocument->justEdited();
  }
}
