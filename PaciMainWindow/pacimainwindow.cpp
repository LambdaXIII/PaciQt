#include "pacimainwindow.h"
#include "ui_pacimainwindow.h"
#include "configcontroller.h"
#include <QFileDialog>
#include <QDebug>

#include "widgets/trackselector.h"

PaciMainWindow::PaciMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PaciMainWindow)
{
  ui->setupUi(this);
  ui->trackSideBar->setVisible(false);

  connect(GlobalDocument, &SequenceDoc::currentFilenameChanged, this, &PaciMainWindow::setWindowFilePath);

  connect(GlobalDocument, &SequenceDoc::editedChanged, ui->trackSideBar, &TrackSideBar::refresh);
  connect(GlobalDocument, &SequenceDoc::sequenceChanged, ui->trackSideBar, &TrackSideBar::refresh);

  connect(ui->trackSideBar, &TrackSideBar::trackSelected, ui->clipsTable, &ClipsTable::acceptNewTrackIndex);

  connect(ui->actionTest, &QAction::triggered, this, &PaciMainWindow::run_test);

  connect(ui->actionCreate, &QAction::triggered, GlobalDocument, &SequenceDoc::create);
  connect(ui->actionOpen, &QAction::triggered, GlobalDocument, &SequenceDoc::open);
  connect(ui->actionSave, &QAction::triggered, GlobalDocument, &SequenceDoc::save);
  connect(ui->actionSaveAs, &QAction::triggered, GlobalDocument, &SequenceDoc::saveAs);

  connect(ui->actionShowTC, &QAction::triggered, ui->clipsTable, &ClipsTable::showTC);

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
  auto a = new TrackSelector(GlobalSequence.data(), this);
  a->exec();
  qDebug() << a->currentTrackIndex();
  a->deleteLater();
}
