#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include "Netflix.h"

class SignUpWindow : public QWidget
{
  Q_OBJECT

 public:
  SignUpWindow(Netflix* flix, QWidget* parent = NULL);
  void closeEvent(QCloseEvent *event);

  // Help define initial size
  QSize sizeHint() const { return QSize( 300, 100 ); }
  // Not totally useful in the main widget/window
  QSize minimumSizeHint() const { return QSize( 200, 150 ); }

 private slots:

  void confirmClicked();
  void cancelClicked();

 private:
  QLabel* headerLabel;
  QLineEdit* userIDText;
  QLineEdit* nameText;
  QLineEdit* addressText;
  QLineEdit* ccNumText;
  QLineEdit* ccDateText;
  QLineEdit* ccCodeText;
  QLineEdit* passwordText;
  QPushButton* confirmButton;
  QPushButton* cancelButton;
  Netflix* netflix;
  QWidget* parent;

};

#endif