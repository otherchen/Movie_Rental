#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QString>
#include "Netflix.h"
#include "resultWindow.h"
#include "profileWindow.h"

class MainWindow : public QWidget
{
  Q_OBJECT

 public:
  MainWindow(Netflix* flix, QWidget* parent = NULL);
  void closeEvent(QCloseEvent *event);

 private slots:

  void returnClicked();
  void rentClicked();
  void deleteClicked();
  void requeueClicked();
  void searchTitleClicked();
  void searchKeywordClicked();
  void searchActorClicked();
  void logoutClicked();
  void updateQueue();
  void profileClicked();

 private:
  QLabel* headerLabel;
  QLabel* currentMovieLabel;
  QLabel* frontOfQueueLabel;
  QLabel* movieHeader;
  QLabel* queueHeader;
  QLabel* searchHeader;
  QLineEdit* searchText;
  QPushButton* returnButton;
  QPushButton* rentButton;
  QPushButton* deleteButton;
  QPushButton* requeueButton;
  QPushButton* searchTitleButton;
  QPushButton* searchKeywordButton;
  QPushButton* searchActorButton;
  QPushButton* logoutButton;
  QPushButton* profileButton;
  Netflix* netflix;
  QWidget* parent;
  ResultWindow* resultWindow;
  ProfileWindow* profileWindow;

};

#endif