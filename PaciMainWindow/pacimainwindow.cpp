#include "pacimainwindow.h"
#include "ui_pacimainwindow.h"
#include <QFileDialog>
#include <QDebug>

PaciMainWindow::PaciMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PaciMainWindow)
{
  ui->setupUi(this);
  connect(ui->actionTest, &QAction::triggered, this, &PaciMainWindow::run_test);
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
