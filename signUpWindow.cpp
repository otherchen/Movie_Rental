#include <iostream>
#include <fstream>
#include <string>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QMessageBox>
#include "signUpWindow.h"

using namespace std;

SignUpWindow::SignUpWindow(Netflix* flix, QWidget* parent)
{

  netflix = flix;
  this->parent = parent;
  headerLabel = new QLabel("Fill out all fields below, thank you!");
  
  confirmButton = new QPushButton("&Confirm");
  cancelButton = new QPushButton("&Cancel");

  userIDText = new QLineEdit;
  nameText = new QLineEdit;
  addressText = new QLineEdit;
  ccNumText = new QLineEdit;
  ccDateText = new QLineEdit;
  ccCodeText = new QLineEdit;
  passwordText = new QLineEdit;
  
  QFormLayout* fLayout = new QFormLayout;
  fLayout->addRow(headerLabel);
  fLayout->addRow("&User ID:", userIDText);
  fLayout->addRow("&Name:", nameText);
  fLayout->addRow("&Address:", addressText);
  fLayout->addRow("&Credit Card Number:", ccNumText);
  fLayout->addRow("&Expiration Date:", ccDateText);
  fLayout->addRow("&Verification Code:", ccCodeText);
  fLayout->addRow("&Password:", passwordText);

  QHBoxLayout* botRow = new QHBoxLayout;
  botRow->addWidget(confirmButton);
  botRow->addWidget(cancelButton);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addLayout(fLayout);
  mainLayout->addLayout(botRow);

  connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirmClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));

  setLayout(mainLayout);
}

void SignUpWindow::confirmClicked(){

    string userID = userIDText->text().toStdString();
    string fullName = nameText->text().toStdString();
    string address = addressText->text().toStdString();
    string ccNum = ccNumText->text().toStdString();
    string ccDate = ccDateText->text().toStdString();
    string ccCode = ccCodeText->text().toStdString();
    string password = passwordText->text().toStdString();

    if (userID == "" || fullName == "" || address == "" || ccNum == "" ||
        ccDate == "" || ccCode == "" || password == "") {

      QMessageBox msgBox;
      msgBox.setWindowTitle("Please Try Again.");
      msgBox.setText("Don't leave any fields blank!");
      msgBox.exec();
      return;

    }

    bool success = netflix->createUser(userID, fullName, address, ccNum, ccDate, ccCode, password);

    if(success){

      this->hide();
      parent->show();

    } else {

      //Error message: userID already taken
      QMessageBox msgBox;
      msgBox.setWindowTitle("Please Try Again.");
      msgBox.setText("Sorry, User ID is already taken.");
      msgBox.exec();

    }

    userIDText->setText("");
    nameText->setText("");
    addressText->setText("");
    ccNumText->setText("");
    ccDateText->setText("");
    ccCodeText->setText("");
    passwordText->setText("");

}

void SignUpWindow::cancelClicked(){

  this->hide();
  parent->show();

}

void SignUpWindow::closeEvent(QCloseEvent *event)
{
    // if (maybeSave()) {
    //     writeSettings();
    //     event->accept();
    // } else {
    //     event->ignore();
    // }
  this->hide();
  parent->show();

}
