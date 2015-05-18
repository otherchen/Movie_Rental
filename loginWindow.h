#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include "Netflix.h"
#include "mainWindow.h"
#include "signUpWindow.h"
#include "resultWindow.h"
#include "recommendWindow.h"

class LoginWindow : public QWidget
{
  Q_OBJECT

 public:
  LoginWindow(Netflix* flix, QWidget* parent = NULL);
  ~LoginWindow();

  // Help define initial size
  QSize sizeHint() const { return QSize( 300, 100 ); }
  // Not totally useful in the main widget/window
  QSize minimumSizeHint() const { return QSize( 200, 150 ); }

 private slots:

  void loginClicked();
  void newUserClicked();
  void quitClicked();

 private:
  QLabel* loginLabel;
  QLabel* headerLabel;
  QLineEdit* userIDText;
  QLineEdit* passwordText;
  QPushButton* loginButton;
  QPushButton* newUserButton;
  QPushButton* quitButton;

  Netflix* netflix;
  SignUpWindow* signUpWindow;
  MainWindow* mainWindow;
  RecommendWindow* recommendWindow;
  //ResultWindow* resultWindow;

};

#endif
