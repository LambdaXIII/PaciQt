#ifndef PACIMAINWINDOW_H
#define PACIMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class PaciMainWindow;
}

class PaciMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit PaciMainWindow(QWidget *parent = 0);
  ~PaciMainWindow();

private:
  Ui::PaciMainWindow *ui;

protected slots:
  void run_test();

  void setupFont();
};

#endif // PACIMAINWINDOW_H
