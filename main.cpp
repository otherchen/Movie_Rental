#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include "Movie.h"
#include "User.h"
#include "lib/queue.h"
#include "Netflix.h"
#include <QApplication>
#include <QPushButton>
#include "loginWindow.h"
#include "signUpWindow.h"
#include "mainWindow.h"
#include "resultWindow.h"

using namespace std;

int main(int argc, char *argv[]){

	Netflix* netflix = new Netflix(argv[1]);
	stringstream ss;

	/****************************************************/

	QApplication app(argc, argv);
	LoginWindow loginWindow(netflix);
	loginWindow.show();

    return app.exec();

	/****************************************************/

	

}