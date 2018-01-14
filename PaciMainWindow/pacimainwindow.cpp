#include "pacimainwindow.h"
#include "ui_pacimainwindow.h"
#include <QFileDialog>
#include <QDebug>

PaciMainWindow::PaciMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PaciMainWindow)
{
  ui->setupUi(this);

  connect(GlobalDocument, &SequenceDoc::editedChanged, ui->trackSideBar, &TrackSideBar::refresh);
  connect(GlobalDocument, &SequenceDoc::sequenceChanged, ui->trackSideBar, &TrackSideBar::refresh);

  connect(ui->trackSideBar, &TrackSideBar::trackSelected, ui->clipsTable, &ClipsTable::acceptNewTrackIndex);

  connect(ui->actionTest, &QAction::triggered, this, &PaciMainWindow::run_test);

  connect(ui->actionOpen, &QAction::triggered, GlobalDocument, &SequenceDoc::open);
}

PaciMainWindow::~PaciMainWindow()
{
  delete ui;
}


void PaciMainWindow::run_test()
{
  QString s;
  QString file = QFileDialog::getOpenFileName(this, "TEXT", QDir::homePath(), "Try(*.txt);;All(*.*)", &s);
  qDebug() << s;
}
