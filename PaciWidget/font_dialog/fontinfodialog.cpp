#include "fontinfodialog.h"
#include "ui_fontinfodialog.h"

FontInfoDialog::FontInfoDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::FontInfoDialog)
{
  ui->setupUi(this);
}

FontInfoDialog::~FontInfoDialog()
{
  delete ui;
}
