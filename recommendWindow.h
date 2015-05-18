#ifndef RECOMMENDWINDOW_H
#define RECOMMENDWINDOW_H

#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include "Netflix.h"

class RecommendWindow : public QWidget
{
  Q_OBJECT

 public:
  RecommendWindow(Netflix* flix, Movie* movie, QWidget* next = NULL);
  void closeEvent(QCloseEvent *event);

  // Help define initial size
  QSize sizeHint() const { return QSize( 300, 100 ); }
  // Not totally useful in the main widget/window
  QSize minimumSizeHint() const { return QSize( 200, 150 ); }

 private slots:

  void addClicked();
  void contClicked();

 signals:
  void updateQueue();

 private:
  QLabel* headerLabel;
  QLabel* titleLabel;
  QLabel* keywordLabel;
  QPushButton* addButton;
  QPushButton* contButton;
  Netflix* netflix;
  QWidget* next;
  Movie* movie;

};

#endif