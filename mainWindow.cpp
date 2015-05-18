#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
#include <QMessageBox>
#include "mainWindow.h"

using namespace std;

MainWindow::MainWindow(Netflix* flix, QWidget* parent)
{
  netflix = flix;
  this->parent = parent;

  /**************************************************************/

  string id = netflix->getUser()->getID();
  string name = netflix->getUser()->getName();
  string greeting = "Welcome to Netflix, " + name + " (" + id + ")";
  QString qHeader =  QString::fromStdString(greeting);

  /**************************************************************/

  string currentMovie;

  if(netflix->checkedOutMovie() != 0){

    //cout << netflix->checkedOutMovie() << endl;
    currentMovie = netflix->checkedOutMovie()->getTitle();

  } else {

    currentMovie = "No movie checked out.";

  }

  QString qCurrentMovie = QString::fromStdString(currentMovie);

  /**************************************************************/
  stringstream ss;
  string frontQueue;
  string costString;

  if(!netflix->emptyQueue()){
    ss << netflix->frontOfQueue()->getCost();
    ss >> costString;
    frontQueue = netflix->frontOfQueue()->getTitle() + " ($" + costString + ")";
  } else {
    frontQueue = "Movie queue is empty.";
  }

  // try {
  //   frontQueue = netflix->frontOfQueue()->getTitle();
  // } catch (out_of_range & e) {
  //   frontQueue = "Movie queue is empty.";
  // }

  QString qFrontQueue = QString::fromStdString(frontQueue);

  /**************************************************************/

  string queuedMovie;

  headerLabel = new QLabel(qHeader);
  currentMovieLabel = new QLabel(qCurrentMovie);
  frontOfQueueLabel = new QLabel(qFrontQueue);
  movieHeader = new QLabel("Your Current Movie");
  queueHeader = new QLabel("Your Movie Queue");
  searchHeader = new QLabel("Search for a Movie");
  
  returnButton = new QPushButton("&Return Movie");
  rentButton = new QPushButton("&Rent Movie");
  deleteButton = new QPushButton("&Delete from Queue");
  requeueButton = new QPushButton("&Move to Back of Queue");
  searchTitleButton = new QPushButton("&Search by Title");
  searchKeywordButton = new QPushButton("&Search by Keyword");
  searchActorButton = new QPushButton("&Search by Actor");
  logoutButton = new QPushButton("&Logout");
  profileButton = new QPushButton("Profile");

  searchText = new QLineEdit;

  QHBoxLayout* botRow = new QHBoxLayout;
  botRow->addWidget(rentButton);
  botRow->addWidget(deleteButton);
  botRow->addWidget(requeueButton);

  QHBoxLayout* searchRow = new QHBoxLayout;
  searchRow->addWidget(searchTitleButton);
  searchRow->addWidget(searchKeywordButton);
  searchRow->addWidget(searchActorButton);

  QFormLayout* fLayout = new QFormLayout;
  fLayout->addRow("&Search:", searchText);

  QVBoxLayout* topLayout = new QVBoxLayout;
  topLayout->addWidget(movieHeader);
  topLayout->addWidget(currentMovieLabel);
  topLayout->addWidget(returnButton);

  QVBoxLayout* midLayout = new QVBoxLayout;
  midLayout->addWidget(queueHeader);
  midLayout->addWidget(frontOfQueueLabel);
  midLayout->addLayout(botRow);

  QVBoxLayout* botLayout = new QVBoxLayout;
  botLayout->addWidget(searchHeader);
  botLayout->addLayout(fLayout);
  botLayout->addLayout(searchRow);
  botLayout->addWidget(logoutButton);

  QHBoxLayout* headLayout = new QHBoxLayout;
  headLayout->addWidget(headerLabel);
  headLayout->addWidget(profileButton);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addLayout(headLayout);
  mainLayout->addLayout(topLayout);
  mainLayout->addLayout(midLayout);
  mainLayout->addLayout(botLayout);

  connect(returnButton, SIGNAL(clicked()), this, SLOT(returnClicked()));
  connect(rentButton, SIGNAL(clicked()), this, SLOT(rentClicked()));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
  connect(requeueButton, SIGNAL(clicked()), this, SLOT(requeueClicked()));
  connect(searchTitleButton, SIGNAL(clicked()), this, SLOT(searchTitleClicked()));
  connect(searchKeywordButton, SIGNAL(clicked()), this, SLOT(searchKeywordClicked()));
  connect(searchActorButton, SIGNAL(clicked()), this, SLOT(searchActorClicked()));
  connect(logoutButton, SIGNAL(clicked()), this, SLOT(logoutClicked()));
  connect(profileButton, SIGNAL(clicked()), this, SLOT(profileClicked()));

  setLayout(mainLayout);
}

void MainWindow::returnClicked(){

    if(netflix->ratingExists() == false){

      QMessageBox ratingBox;
      ratingBox.setWindowTitle("Rate this movie.");
      ratingBox.setText("What would you rate this movie?");
      QPushButton *skip = ratingBox.addButton(QPushButton::tr("Skip"), QMessageBox::ActionRole);
      QPushButton *one = ratingBox.addButton(QPushButton::tr("One"), QMessageBox::ActionRole);
      QPushButton *two = ratingBox.addButton(QPushButton::tr("Two"), QMessageBox::ActionRole);
      QPushButton *three = ratingBox.addButton(QPushButton::tr("Three"), QMessageBox::ActionRole);
      QPushButton *four = ratingBox.addButton(QPushButton::tr("Four"), QMessageBox::ActionRole);
      QPushButton *five = ratingBox.addButton(QPushButton::tr("Five"), QMessageBox::ActionRole);
      ratingBox.exec();

      if (ratingBox.clickedButton() == skip){
        ratingBox.close();
      } else if(ratingBox.clickedButton() == one){
        netflix->addRating(1);
      } else if (ratingBox.clickedButton() == two){
        netflix->addRating(2);
      } else if (ratingBox.clickedButton() == three){
        netflix->addRating(3);
      } else if (ratingBox.clickedButton() == four){
        netflix->addRating(4);
      } else if (ratingBox.clickedButton() == five){
        netflix->addRating(5);
      } 

    } 

    netflix->turnInMovie();
    QString qMovie = QString::fromStdString("No movie checked out.");
    currentMovieLabel->setText(qMovie);
    //refresh the checked out movie

}

void MainWindow::rentClicked(){
    
    bool success = netflix->orderMovie();
    
    if(success){

      QString qMovie = QString::fromStdString(netflix->checkedOutMovie()->getTitle());
      currentMovieLabel->setText(qMovie);
      QString qQueue;

      stringstream ss;
      string frontQueue;
      string costString;

      if(!netflix->emptyQueue()){
        ss << netflix->frontOfQueue()->getCost();
        ss >> costString;
        frontQueue = netflix->frontOfQueue()->getTitle() + " ($" + costString + ")";
      }

      if(!netflix->emptyQueue()){
        qQueue = QString::fromStdString(frontQueue);
      } else {
        qQueue = QString::fromStdString("Movie queue is empty.");
      }

      frontOfQueueLabel->setText(qQueue);
      string chargeText;
      //refresh the checked out movie
      //refresh the queued movie

      string cardID = netflix->getUser()->getCard()->first;
      double charge = netflix->checkedOutMovie()->getCost();

      ss << charge;
      ss >> chargeText;

      string text = "Your card: " + cardID + " was charged $" + chargeText;
      QString qText = QString::fromStdString(text);

      QMessageBox msgBox;
      msgBox.setWindowTitle("Enjoy your movie!");
      msgBox.setText(qText);
      msgBox.exec();

      netflix->getUser()->chargeCard(charge);

    }

}

void MainWindow::deleteClicked(){

    netflix->removeMovie();
    QString qQueue;

    stringstream ss;
    string frontQueue;
    string costString;

    if(!netflix->emptyQueue()){
      ss << netflix->frontOfQueue()->getCost();
      ss >> costString;
      frontQueue = netflix->frontOfQueue()->getTitle() + " ($" + costString + ")";
    }

    if(!netflix->emptyQueue()){
      qQueue = QString::fromStdString(frontQueue);
    } else {
      qQueue = QString::fromStdString("Movie queue is empty.");
    }

    // try{
    //   qQueue = QString::fromStdString(netflix->frontOfQueue()->getTitle());
    // } catch(out_of_range & e){
    //   qQueue = QString::fromStdString("Movie queue is empty.");
    // }

    frontOfQueueLabel->setText(qQueue);
    //refresh the queued movie

}

void MainWindow::requeueClicked(){

    netflix->requeueMovie();
    QString qQueue;

    stringstream ss;
    string frontQueue;
    string costString;

    if(!netflix->emptyQueue()){
      ss << netflix->frontOfQueue()->getCost();
      ss >> costString;
      frontQueue = netflix->frontOfQueue()->getTitle() + " ($" + costString + ")";
    }

    if(!netflix->emptyQueue()){
      qQueue = QString::fromStdString(frontQueue);
    } else {
      qQueue = QString::fromStdString("Movie queue is empty.");
    }

    // try{
    //   qQueue = QString::fromStdString(netflix->frontOfQueue()->getTitle());
    // } catch(out_of_range & e){
    //   qQueue = QString::fromStdString("Movie queue is empty.");
    // }

    frontOfQueueLabel->setText(qQueue);
    //refresh the queued movie

}

void MainWindow::searchTitleClicked(){

    string title = searchText->text().toStdString();
    queue<Movie*>* searchedQueue = new queue<Movie*>;
    searchedQueue = netflix->searchTitle(title);

    if(searchedQueue->empty()){
      
      QMessageBox msgBox;
      msgBox.setWindowTitle("Please Try Again.");
      msgBox.setText("Sorry, movie not found.");
      msgBox.exec();

    } else {

      this->hide();
      resultWindow = new ResultWindow(netflix, searchedQueue, this);
      connect(resultWindow, SIGNAL(updateQueue()), this, SLOT(updateQueue()));
      resultWindow->show();

    }

    searchText->setText("");

}

void MainWindow::searchKeywordClicked(){

    string keyword = searchText->text().toStdString();
    queue<Movie*>* searchedQueue = new queue<Movie*>;
    searchedQueue = netflix->searchKeyword(keyword);

    if(searchedQueue->empty()){
      
      QMessageBox msgBox;
      msgBox.setWindowTitle("Please Try Again.");
      msgBox.setText("Sorry, no matching movies were found.");
      msgBox.exec();

    } else {

      this->hide();
      resultWindow = new ResultWindow(netflix, searchedQueue, this);
      connect(resultWindow, SIGNAL(updateQueue()), this, SLOT(updateQueue()));
      resultWindow->show();
    }

    searchText->setText("");

}

void MainWindow::searchActorClicked(){

    string actor = searchText->text().toStdString();
    queue<Movie*>* searchedQueue = new queue<Movie*>;
    searchedQueue = netflix->searchActor(actor);

    if(searchedQueue->empty()){
      
      QMessageBox msgBox;
      msgBox.setWindowTitle("Please Try Again.");
      msgBox.setText("Sorry, no matching movies were found.");
      msgBox.exec();

    } else {

      this->hide();
      resultWindow = new ResultWindow(netflix, searchedQueue, this);
      connect(resultWindow, SIGNAL(updateQueue()), this, SLOT(updateQueue()));
      resultWindow->show();
    }

    searchText->setText("");

}

void MainWindow::logoutClicked(){
 
    netflix->logout();
    this->hide();
    parent->show();
    delete this;

}

void MainWindow::updateQueue(){

  QString qQueue;

  stringstream ss;
  string frontQueue;
  string costString;

  if(!netflix->emptyQueue()){
    ss << netflix->frontOfQueue()->getCost();
    ss >> costString;
    frontQueue = netflix->frontOfQueue()->getTitle() + " ($" + costString + ")";
  }

  if(!netflix->emptyQueue()){
    qQueue = QString::fromStdString(frontQueue);
  } else {
    qQueue = QString::fromStdString("Movie queue is empty.");
  }

  // try{
  //   qQueue = QString::fromStdString(netflix->frontOfQueue()->getTitle());
  // } catch(out_of_range & e){
  //   qQueue = QString::fromStdString("Movie queue is empty.");
  // }

  frontOfQueueLabel->setText(qQueue);

}

void MainWindow::profileClicked(){

  this->hide();
  profileWindow = new ProfileWindow(netflix, this);
  profileWindow->show();

}

void MainWindow::closeEvent(QCloseEvent *event)
{

    netflix->logout();
    this->hide();
    parent->show();
    delete this;

}