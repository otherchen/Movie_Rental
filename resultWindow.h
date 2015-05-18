#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include "Netflix.h"

class ResultWindow : public QWidget
{
  Q_OBJECT

 public:
  ResultWindow(Netflix* flix, queue<Movie*>* searchQueue, QWidget* parent = NULL);
  void closeEvent(QCloseEvent *event);

  // Help define initial size
  QSize sizeHint() const { return QSize( 300, 100 ); }
  // Not totally useful in the main widget/window
  QSize minimumSizeHint() const { return QSize( 200, 150 ); }

 private slots:

  void nextClicked();
  void addClicked();
  void backClicked();

 signals:
  void updateQueue();

 private:
  QLabel* headerLabel;
  QLabel* titleLabel;
  QLabel* keywordLabel;
  QPushButton* nextButton;
  QPushButton* addButton;
  QPushButton* backButton;
  Netflix* netflix;
  QWidget* parent;
  queue<Movie*>* searchQueue;
  QVBoxLayout* vLayout;
  QVBoxLayout* mainLayout;

};

#endif