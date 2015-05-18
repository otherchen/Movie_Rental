#include <iostream>
#include <fstream>
#include <string>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QMessageBox>
#include "loginWindow.h"

using namespace std;

LoginWindow::LoginWindow(Netflix* flix, QWidget* parent)
{

  netflix = flix;
  headerLabel = new QLabel("Welcome to Netflix!");
  
  loginButton = new QPushButton("&Login");
  newUserButton = new QPushButton("&New User");
  quitButton = new QPushButton("&Quit");
  loginButton->setDefault(true);

  userIDText = new QLineEdit;
  passwordText = new QLineEdit;
  
  QFormLayout* fLayout = new QFormLayout;
  fLayout->addRow("", headerLabel);
  fLayout->addRow("&Login:", userIDText);
  fLayout->addRow("&Password:", passwordText);
  
  QHBoxLayout* botRow = new QHBoxLayout;
  botRow->addWidget(loginButton);
  botRow->addWidget(newUserButton);
  botRow->addWidget(quitButton);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addLayout(fLayout);
  mainLayout->addLayout(botRow);

  connect(userIDText, SIGNAL(returnPressed()),loginButton,SIGNAL(clicked()));
  connect(passwordText, SIGNAL(returnPressed()),loginButton,SIGNAL(clicked()));
  connect(loginButton, SIGNAL(clicked()), this, SLOT(loginClicked()));
  connect(newUserButton, SIGNAL(clicked()), this, SLOT(newUserClicked()));
  connect(quitButton, SIGNAL(clicked()), this, SLOT(quitClicked()));

  setLayout(mainLayout);

  signUpWindow = new SignUpWindow(flix, this);
  //resultWindow = new ResultWindow(flix, this);

}

LoginWindow::~LoginWindow(){

}

void LoginWindow::loginClicked(){

    string userID = userIDText->text().toStdString();
    string password = passwordText->text().toStdString();
    bool success = netflix->login(userID, password);

    if(success){

      this->hide();
      mainWindow = new MainWindow(netflix, this);
      //mainWindow->show();

      recommendWindow = new RecommendWindow(netflix, netflix->recommend(), mainWindow);
      connect(recommendWindow, SIGNAL(updateQueue()), mainWindow, SLOT(updateQueue()));
      recommendWindow->show();

    } else {

      //create pop up box with error message
      QMessageBox msgBox;
      msgBox.setWindowTitle("Please Try Again.");
      msgBox.setText("Improper UserID or Password.");
      msgBox.exec();

    }

    passwordText->setText("");

}

void LoginWindow::newUserClicked(){

  this->hide();
  signUpWindow->show();

}

void LoginWindow::quitClicked(){

  this->close();

}