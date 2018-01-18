#include "csvoptiondialog.h"
#include "ui_csvoptiondialog.h"

CsvOptionDialog::CsvOptionDialog(Mode mode, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CsvOptionDialog)
{
  ui->setupUi(this);
  ui->okButton->setDefault(true);
  connect(ui->okButton, &QPushButton::clicked, this, &CsvOptionDialog::accept);

  if (mode == Saving) {
    ui->timebaseGroupBox->setVisible(false);
  }
}

CsvOptionDialog::~CsvOptionDialog()
{
  delete ui;
}

Timebase* CsvOptionDialog::getTimebase()
{
  return ui->timebaseComboBox->currentTimebase();
}

bool CsvOptionDialog::getUseTimecode()
{
  return ui->useTimecodeSelector->useTimecode();
}
