#ifndef USETIMECODESELECTOR_H
#define USETIMECODESELECTOR_H

#include <QWidget>
#include <QRadioButton>

class UseTimecodeSelector : public QWidget
{
  Q_OBJECT
public:
  explicit UseTimecodeSelector(QWidget *parent = nullptr);
  bool useTimecode() const;

protected:
  QRadioButton *useTimecodeButton;
  QRadioButton *useFrameButton;

signals:
  void useTimecodeChanged(bool use);

//protected slots:
//  void handleCheckedAction();

public slots:
  void setUseTimecode(bool x);
};

#endif // USETIMECODESELECTOR_H
