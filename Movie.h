#ifndef MOVIE_H
#define MOVIE_H

//#include "lib/set.h"
//#include <set>
#include "lib/set.h"
#include <string>

class Movie {
  public: 
    Movie();

    Movie (std::string title);       // constructor for a movie with the given title

    Movie (const Movie & other);  // copy constructor

    ~Movie ();                  // destructor

    std::string getTitle () const;   // returns the title of the movie

    void addKeyword (std::string keyword); 
      /* Adds the (free-form) keyword to this movie.
         If the exact same keyword (up to capitalization) was already
         associated with the movie, then the keyword is not added again. */

    const Set<std::string> & getAllKeywords () const;
      /* Returns a set of all keywords associated with the movie. */

    void addActor(std::string actor);

    const Set<std::string> & getAllActors () const;

    void setCost(double num);

    double getCost();

    Movie & operator=(const Movie & other);
     /* overloads "=" operator */

    bool operator==(const Movie & other);
     /* overloads "==" operator */

  private:
    // you get to decide what goes here
    std::string title;
    Set<std::string> keyWords;
    Set<std::string> actors;
    double rentalCost;
};

#endif