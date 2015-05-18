#include <iostream>
#include <fstream>
#include <string>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QLayoutItem>
#include "recommendWindow.h"

using namespace std;

RecommendWindow::RecommendWindow(Netflix* flix, Movie* movie, QWidget* next)
{

  netflix = flix;
  this->next = next;
  this->movie = movie;

  /**************************************************************/

  string currentMovie;
  stringstream ss;
  string frontQueue;
  string costString;

  if(movie != NULL){

    ss << movie->getCost();
    ss >> costString;
    frontQueue = movie->getTitle() + " ($" + costString + ")";
    currentMovie = frontQueue;

  } else {

    currentMovie = "There are no recommendations.";

  }

  QString qCurrentMovie = QString::fromStdString(currentMovie);

  /**************************************************************/

  headerLabel = new QLabel("Movie Recommendation:");
  titleLabel = new QLabel(qCurrentMovie);
  
  addButton = new QPushButton("&Add to my Queue");
  contButton = new QPushButton("&Continue to Main Menu");
  
  QHBoxLayout* botRow;
  botRow = new QHBoxLayout;

  if(movie != NULL){

    botRow->addWidget(addButton);
    botRow->addWidget(contButton);

  } else {

    botRow->addWidget(contButton);

  }

  QVBoxLayout* vLayout = new QVBoxLayout;

  /**************************************************************/

  if(movie != NULL){

      string keyword;
      set<string> keywordSet = movie->getAllKeywords();

      for(set<string>::iterator keyIter = keywordSet.begin(); keyIter != keywordSet.end(); ++keyIter){
                      
        keyword = *keyIter;
        QString qKeyword = QString::fromStdString(keyword);
        keywordLabel = new QLabel(qKeyword);
        vLayout->addWidget(keywordLabel);
                              
      }
  }

  /**************************************************************/

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(headerLabel);
  mainLayout->addWidget(titleLabel);
  mainLayout->addLayout(vLayout);
  mainLayout->addLayout(botRow);

  connect(addButton, SIGNAL(clicked()), this, SLOT(addClicked()));
  connect(contButton, SIGNAL(clicked()), this, SLOT(contClicked()));

  setLayout(mainLayout);
}

void RecommendWindow::addClicked(){


  netflix->enqueueMovie(movie);

  this->hide();
  next->show();
  emit updateQueue();
  delete this;

}

void RecommendWindow::contClicked(){

  this->hide();
  next->show();
  delete this;

}

void RecommendWindow::closeEvent(QCloseEvent *event)
{

  this->hide();
  next->show();
  delete this;

}