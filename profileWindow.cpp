#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QMessageBox>
#include "profileWindow.h"

using namespace std;

ProfileWindow::ProfileWindow(Netflix* flix, QWidget* parent)
{

  netflix = flix;
  this->parent = parent;

  string chargeText;
  stringstream ss;
  ss << netflix->getUser()->getCard()->second;
  ss >> chargeText;
  chargeText = "Total: $" + chargeText;

  QString qAddress = QString::fromStdString(netflix->getUser()->getAddress());
  QString qCCNum = QString::fromStdString(netflix->getUser()->getCCNumber());
  QString qCCDate = QString::fromStdString(netflix->getUser()->getCCDate());
  QString qCCCode = QString::fromStdString(netflix->getUser()->getCCCode());
  QString totalCharge = QString::fromStdString(chargeText);
  //QString qPassword = QString::fromStdString(netflix->getUser()->getName());

  chargeLabel = new QLabel(totalCharge);
  headerLabel = new QLabel("Feel free to change your information!");
  addressLabel = new QLabel(qAddress);
  ccNumLabel = new QLabel(qCCNum);
  ccDateLabel = new QLabel(qCCDate);
  ccCodeLabel = new QLabel(qCCCode);
  passwordLabel = new QLabel("**********");
  
  updateButton = new QPushButton("&Update");
  cancelButton = new QPushButton("&Cancel");

  addressText = new QLineEdit;
  ccNumText = new QLineEdit;
  ccDateText = new QLineEdit;
  ccCodeText = new QLineEdit;
  passwordText = new QLineEdit;

  // QString qAddress2 = QString::fromStdString("&Address:");
  // QString qCCNum2 = QString::fromStdString("&Credit Card Number:");
  // QString qCCDate2 = QString::fromStdString("&Expiration Date:");
  // QString qCCCode2 = QString::fromStdString("&Verification Code:");
  // QString qPassword2 = QString::fromStdString("&Password:");

  // QGridLayout* gridLayout = new QGridLayout;
  // gridLayout->addWidget(qAddress2, 0, 0);
  // gridLayout->addWidget(addressLabel, 0, 1);
  // gridLayout->addWidget(addressText, 0, 2);
  // gridLayout->addWidget(qCCNum2, 1, 0);
  // gridLayout->addWidget(ccNumLabel, 1, 1);
  // gridLayout->addWidget(ccNumText, 1, 2);
  // gridLayout->addWidget(qCCDate2, 2, 0);
  // gridLayout->addWidget(ccDateLabel, 2, 1);
  // gridLayout->addWidget(ccDateText, 2, 2);
  // gridLayout->addWidget(qCCCode2, 3, 0);
  // gridLayout->addWidget(ccCodeLabel, 3, 1);
  // gridLayout->addWidget(ccCodeText, 3, 2);
  // gridLayout->addWidget(qPassword2, 4, 0);
  // gridLayout->addWidget(passwordLabel, 4, 1);
  // gridLayout->addWidget(passwordText, 4, 2);

  QFormLayout* leftLayout = new QFormLayout;
  leftLayout->addRow("&Address:", addressLabel);
  leftLayout->addRow("&Credit Card Number:", ccNumLabel);
  leftLayout->addRow("&Expiration Date:", ccDateLabel);
  leftLayout->addRow("&Verification Code:", ccCodeLabel);
  leftLayout->addRow("&Password:", passwordLabel);
  
  QFormLayout* rightLayout = new QFormLayout;
  //rightLayout->addRow(headerLabel);
  rightLayout->addRow(addressText);
  rightLayout->addRow(ccNumText);
  rightLayout->addRow(ccDateText);
  rightLayout->addRow(ccCodeText);
  rightLayout->addRow(passwordText);

  QHBoxLayout* botRow = new QHBoxLayout;
  botRow->addWidget(updateButton);
  botRow->addWidget(cancelButton);

  QHBoxLayout* hLayout = new QHBoxLayout;
  hLayout->addLayout(leftLayout);
  hLayout->addLayout(rightLayout);

  QHBoxLayout* headLayout = new QHBoxLayout;
  headLayout->addWidget(headerLabel);
  headLayout->addWidget(chargeLabel);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addLayout(headLayout);
  mainLayout->addLayout(hLayout);
  mainLayout->addLayout(botRow);



  connect(updateButton, SIGNAL(clicked()), this, SLOT(updateClicked()));
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));

  setLayout(mainLayout);

}

void ProfileWindow::updateClicked(){

    string address = addressText->text().toStdString();
    string ccNum = ccNumText->text().toStdString();
    string ccDate = ccDateText->text().toStdString();
    string ccCode = ccCodeText->text().toStdString();
    string password = passwordText->text().toStdString();

    int result = netflix->updateUser(address, ccNum, ccDate, ccCode, password);

    if(result == 0){

      this->hide();
      parent->show();

    } else if (result == -1){

      QMessageBox msgBox;
      msgBox.setWindowTitle("Please Try Again.");
      msgBox.setText("None of the fields were changed!");
      msgBox.exec();

    } else if (result == -2){

      QMessageBox msgBox;
      msgBox.setWindowTitle("Please Try Again.");
      msgBox.setText("Attempted to change credit card but some fields were blank!");
      msgBox.exec();

    }

    addressText->setText("");
    ccNumText->setText("");
    ccDateText->setText("");
    ccCodeText->setText("");
    passwordText->setText("");

}

void ProfileWindow::cancelClicked(){

  this->hide();
  parent->show();

}

void ProfileWindow::closeEvent(QCloseEvent *event)
{

  this->hide();
  parent->show();

}
