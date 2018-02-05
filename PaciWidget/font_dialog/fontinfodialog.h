#ifndef FONTINFODIALOG_H
#define FONTINFODIALOG_H

#include <QDialog>

namespace Ui {
  class FontInfoDialog;
}

class FontInfoDialog : public QDialog
{
  Q_OBJECT

public:
  explicit FontInfoDialog(QWidget *parent = 0);
  ~FontInfoDialog();

private:
  Ui::FontInfoDialog *ui;
};

#endif // FONTINFODIALOG_H
