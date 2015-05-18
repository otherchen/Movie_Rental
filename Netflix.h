#ifndef NETFLIX_H
#define NETFLIX_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include "Movie.h"
#include "User.h"
#include <stdexcept>
#include <exception>
#include <vector>
#include "lib/md5.h"
//#include "graph.h"

using namespace std;

class Netflix {

  public:
  	Netflix();
  	/* constructor that initializes the data structures */

  	Netflix(char* mainFileName);
  	/* constructor that initializes the data structures and calls the load functions */

  	~Netflix();
  	/* deletes all the dynamically allocated variables */

  	bool loadFiles(const char* mainFileName);
  	/* takes in the command line argument and obtains two text file names 
  	   it returns true if successful and false if not */

  	bool loadUsers(const char* userFileName);
  	/* reads in all the user information from a text file 
  	   it returns true if successful and false if not */

  	bool loadMovies(const char* movieFileName);
  	/* reads in all the movie information from a text file 
  	   it returns true if successful and false if not */

  	void loginMenu();
  	/* prints out the login menu */

  	bool login(string loginID, string password);
  	/* checks if user exists and if it does, sets current user and procedes with program 
  	   it returns true if successful and false if not */

    User* getUser();
    /* returns current user */

  	bool createUser(string newID, string fullName, string address, string ccNum, string ccDate, string ccCode, string password);
    /* allows user to choose new userID that does not already exist and adds new user to data structure
       it returns true if successful and false if not */

    int updateUser(string address, string ccNum, string ccDate, string ccCode, string password);

  	// void checkedOutMovie();
    Movie* checkedOutMovie();
  	/* prints the current checked out movie and its keywords */

  	void userMenu();
  	/* prints the user menu */

  	queue<Movie*>* searchTitle(string title);
  	/* searches for movie by title where capitalization doesn't matter */

  	queue<Movie*>* searchKeyword(string keyword);
  	/* searches for movies by their keywords */

    queue<Movie*>* searchActor(string actor);

  	void turnInMovie();
  	/* returns the user's current checked out movie */

    bool ratingExists();
    /* returns if there is a rating for the checked out movie*/

    void addRating(int num); 
    /* adds new rating to ratings Map */

  	void queueMenu();
  	/* prints out the movie queue menu */

  	Movie* frontOfQueue();
  	/* prints out the movie at the front of the queue */

  	bool orderMovie();
  	/* checks out the movie at the front of the queue */

  	void removeMovie();
  	/* removes the movie from the front of the queue */

  	void requeueMovie();
  	/* takes the movie from the front to the back of the queue */

    void enqueueMovie(Movie* selection);
    /* queues a given movie */

  	void logout();
  	/* writes all of the data back into the user file and goes back to the login menu */

  	string capitalize(string anyString);
  	/* returns an uppercase version of the provided string */

    bool emptyQueue();

    double basicSimilarity(User* first, User* second);
    /* calculates the basic similarity between two users */

    void dijkstra(int src);

    double interest(Movie* movie);

    Movie* recommend();
    
  private:
	map<string, User*>* users;
	map<string, Movie*>* movies;
	map<string, Set<Movie*>*>* keywords;
  map<string, Set<Movie*>*>* actors;
  map<Movie*, Set<User*>*>* movieRatings; //keeps track of you rated which movies
  queue<Movie*>* movieQueue;
  vector< vector<double> > similarities;
	User* currentUser;
  string userFileName;
  string movieFileName;
  double* distance;

  //dijkstra's private function
  int getClosestNode(int numOfVertices, bool mark[], double distance[]);

};

#endif