#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include "Netflix.h"

class ProfileWindow : public QWidget
{
  Q_OBJECT

 public:
  ProfileWindow(Netflix* flix, QWidget* parent = NULL);
  void closeEvent(QCloseEvent *event);

  // Help define initial size
  QSize sizeHint() const { return QSize( 300, 100 ); }
  // Not totally useful in the main widget/window
  QSize minimumSizeHint() const { return QSize( 200, 150 ); }

 private slots:

  void updateClicked();
  void cancelClicked();

 private:
  QLabel* addressLabel;
  QLabel* ccNumLabel;
  QLabel* ccDateLabel;
  QLabel* ccCodeLabel;
  QLabel* passwordLabel;
  QLabel* headerLabel;
  QLabel* chargeLabel;
  QLineEdit* addressText;
  QLineEdit* ccNumText;
  QLineEdit* ccDateText;
  QLineEdit* ccCodeText;
  QLineEdit* passwordText;
  QPushButton* updateButton;
  QPushButton* cancelButton;
  Netflix* netflix;
  QWidget* parent;

};

#endif