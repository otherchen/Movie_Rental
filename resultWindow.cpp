#include <iostream>
#include <fstream>
#include <string>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QLayoutItem>
#include "resultWindow.h"

using namespace std;

ResultWindow::ResultWindow(Netflix* flix, queue<Movie*>* searchQueue, QWidget* parent)
{

  netflix = flix;
  this->parent = parent;
  this->searchQueue = searchQueue;

  /**************************************************************/

  string currentMovie;
  Movie* movie = searchQueue->front();
  //Set<string> keywordSet = movie->getAllKeywords();
  stringstream ss;
  string frontQueue;
  string costString;

  ss << movie->getCost();
  ss >> costString;
  frontQueue = movie->getTitle() + " ($" + costString + ")";

  if(!searchQueue->empty()){

    currentMovie = frontQueue;

  } else {

    currentMovie = "No movies in the queue.";

  }

  QString qCurrentMovie = QString::fromStdString(currentMovie);

  /**************************************************************/


  /**************************************************************/

  headerLabel = new QLabel("Movie Info:");
  titleLabel = new QLabel(qCurrentMovie);
  nextButton = new QPushButton("&Next Movie");
  addButton = new QPushButton("&Add to my Queue");
  backButton = new QPushButton("&Return to Main Menu");
  
  QHBoxLayout* botRow;

  if(searchQueue->size() > 1){

    botRow = new QHBoxLayout;
    botRow->addWidget(nextButton);
    botRow->addWidget(addButton);
    botRow->addWidget(backButton);

  } else if (searchQueue->size() == 1){

    botRow = new QHBoxLayout;
    botRow->addWidget(addButton);
    botRow->addWidget(backButton);

  }

  vLayout = new QVBoxLayout;

  /**************************************************************/

  string keyword;
  set<string> keywordSet = movie->getAllKeywords();

  // typename Set<string>::Iterator keyIter, keyEnd;
  // keyIter = keywordSet.begin();
  // keyEnd = keywordSet.end();

  for(set<string>::iterator keyIter = keywordSet.begin(); keyIter != keywordSet.end(); ++keyIter){

  // for(; keyIter != keyEnd; ++keyIter){
                  
    keyword = *keyIter;
    QString qKeyword = QString::fromStdString(keyword);
    keywordLabel = new QLabel(qKeyword);
    vLayout->addWidget(keywordLabel);
                          
  }

  /**************************************************************/

  mainLayout = new QVBoxLayout;
  mainLayout->addWidget(headerLabel);
  mainLayout->addWidget(titleLabel);
  mainLayout->addLayout(vLayout);
  mainLayout->addLayout(botRow);

  connect(nextButton, SIGNAL(clicked()), this, SLOT(nextClicked()));
  connect(addButton, SIGNAL(clicked()), this, SLOT(addClicked()));
  connect(backButton, SIGNAL(clicked()), this, SLOT(backClicked()));

  setLayout(mainLayout);
}

void ResultWindow::nextClicked(){

  // if(!searchQueue->empty()){
  //   searchQueue->pop();
  // } else if(searchQueue->empty()){

    string keyword;
    Movie* movie;

    // try{
    //   movie = searchQueue->front();
    // } catch (EmptyQueueException & e){
    //   exists = false;
    // }

    if(!searchQueue->empty()){

      searchQueue->pop();
      movie = searchQueue->front();

      stringstream ss;
      string frontQueue;
      string costString;

      ss << movie->getCost();
      ss >> costString;
      frontQueue = movie->getTitle() + " ($" + costString + ")";    

      QString qTitle = QString::fromStdString(frontQueue);
      titleLabel->setText(qTitle);

      set<string> keywordSet = movie->getAllKeywords();
      // typename Set<string>::Iterator keyIter, keyEnd;
      // keyIter = keywordSet.begin();
      // keyEnd = keywordSet.end();
  
      for(set<string>::iterator keyIter = keywordSet.begin(); keyIter != keywordSet.end(); ++keyIter){
    

      // for(; keyIter != keyEnd; ++keyIter){
                      
        keyword = *keyIter;
        QString qKeyword = QString::fromStdString(keyword);
        keywordLabel->setText(qKeyword);
        //keywordLabel = new QLabel(qKeyword);
        //vLayout->addWidget(keywordLabel);
        //keywordLabel->setText(qKeyword);
                              
      }
    }

    if(searchQueue->size() <= 1){
      nextButton->setEnabled(false);
    }

}

void ResultWindow::addClicked(){

  //netflix->orderMovie();
  // bool isEmpty = false;
  // try{
  //   searchQueue->front();
  // } catch(EmptyQueueException & e){
  //   isEmpty = true;
  // }

  if(!searchQueue->empty()){
    netflix->enqueueMovie(searchQueue->front());
  }

  this->hide();
  parent->show();
  emit updateQueue();
  delete this;
  //update display

}

void ResultWindow::backClicked(){

  this->hide();
  parent->show();
  delete this;


}

void ResultWindow::closeEvent(QCloseEvent *event)
{

  this->hide();
  parent->show();
  delete this;

}