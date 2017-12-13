#include "pacimainwindow.h"
#include "ui_pacimainwindow.h"

PaciMainWindow::PaciMainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::PaciMainWindow)
{
  ui->setupUi(this);
}

PaciMainWindow::~PaciMainWindow()
{
  delete ui;
}
