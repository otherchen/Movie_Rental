#ifndef USER_H
#define USER_H

#include <string>
#include "Movie.h"
#include <queue>
//#include "lib/queue.h"
//#include "lib/map.h"
#include <map>

class User {
  public:
    User ();

    User (std::string ID, std::string name);  
    /* constructor that generates a user with the given name and ID.
       While multiple users may have the same name, the ID should be unique
       (e.g., an e-mail address), so that users can log in with it. */

    User (const User & other); // copy constructor

    ~User ();            // destructor

    std::string getID () const;    // returns the ID associated with this user

    std::string getName () const;  // returns the name associated with this user

    std::queue<Movie*> * movieQueue (); 
      /* returns a pointer to the user's movie queue.
         This is the easiest way to ensure that you can modify the queue.
         (If you return by reference, that's also possible, but you'd need
         to be very careful not to invoke any deep copy constructors or
         assignments. A pointer is thus safer.) */

    void rentMovie (Movie *m);
      /* sets the user's currently rented movie to m.
         If the user already has a movie checked out, then it does nothing.
         (So no overwriting the current movie.) */

    void returnMovie ();
      /* returns the movie that the user currently has checked out.
         Does nothing if the user doesn't currently have a movie. */

    Movie* currentMovie ();
      /* returns the user's current checked out movie.
         Returns NULL if the user has no movie checked out. */

    std::map<Movie*, int>* getRatings();

    void setAddress(std::string address);

    std::string getAddress();

    void setCreditCardInfo(std::string num, std::string date, std::string code);

    std::string getCCNumber();

    std::string getCCDate();

    std::string getCCCode();

    void setUpCard(std::string number, double charge);

    void chargeCard(double charge);

    std::pair<std::string, double>* getCard();

    // void setCharge(int num);

    // int getCharge();

    void setPassword(std::string password);

    std::string getPassword();

  private:
    // you get to decide what goes here.
    std::string id;
    std::string name;
    std::string address;
    std::string creditCardNumber;
    std::string creditCardDate;
    std::string creditCardCode;
    std::pair<std::string, double>* creditCard;
    std::string password;
    std::queue<Movie*> *userQueue;
    Movie* checkedOut;
    std::map<Movie*, int>* ratings;
    //Set<Movie*>* ratedMovies;
};

#endif