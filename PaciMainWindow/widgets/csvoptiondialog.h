#ifndef CSVOPTIONDIALOG_H
#define CSVOPTIONDIALOG_H

#include <QDialog>
#include "timebase.h"

namespace Ui {
class CsvOptionDialog;
}

class CsvOptionDialog : public QDialog
{
  Q_OBJECT

public:
  enum Mode {Saving, Loading};

  explicit CsvOptionDialog(CsvOptionDialog::Mode mode = Loading, QWidget *parent = 0);
  ~CsvOptionDialog();

  Timebase* getTimebase();
  bool getUseTimecode();

private:
  Ui::CsvOptionDialog *ui;

};

#endif // CSVOPTIONDIALOG_H
