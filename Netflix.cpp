#include "Netflix.h"

Netflix::Netflix(){

    users = new map<string, User*>;
    movies = new map<string, Movie*>;
    keywords = new map<string, Set<Movie*>*>;
    actors = new map<string, Set<Movie*>*>;
    movieRatings = new map<Movie*, Set<User*>*>;

}
/* constructor that initializes the data structures */

Netflix::Netflix(char* mainFileName){

    users = new map<string, User*>;
    movies = new map<string, Movie*>;
    keywords = new map<string, Set<Movie*>*>;
    actors = new map<string, Set<Movie*>*>;
    movieRatings = new map<Movie*, Set<User*>*>;

    loadFiles(mainFileName);

}
/* constructor that initializes the data structures and calls the load functions */

Netflix::~Netflix(){

    delete users;
    delete movies;
    delete keywords;
    delete actors;
    delete movieRatings;
    delete[] distance;

}
/* deletes all the dynamically allocated variables */

bool Netflix::loadFiles(const char* mainFileName){

    ifstream mainFile;
    mainFile.open(mainFileName);

    if(mainFile.fail()){
        cout << "Main file does not exist! Please enter valid filename." << endl;
        return false;
    }

    getline(mainFile, userFileName);
    getline(mainFile, movieFileName);

    mainFile.close();

    loadMovies(movieFileName.c_str());
    loadUsers(userFileName.c_str());

    distance = new double[users->size()];

    /****************** creating similarity graph *******************/


    similarities.resize(users->size(), vector<double>(users->size()));
    //for(int i = 0; i < similarities.size())

    int iCount = 0;
    int jCount = 0;

    for(map<string, User*>::iterator iIter = users->begin(); iIter != users->end(); iIter++){

      jCount = 0;

      for(map<string, User*>::iterator jIter = users->begin(); jIter != users->end(); jIter++){
       
        similarities[iCount][jCount] = basicSimilarity(iIter->second, jIter->second);
        // cout << similarities[iCount][jCount] << " |";
        // cout << "similarities[" << iCount << "]" << "[" << jCount << "]" << endl;

        jCount++;

      }

      iCount++;

    }

    return true;

}
/* takes in the command line argument and obtains two text file names 
   it returns true if successful and false if not */

bool Netflix::loadUsers(const char* userFileName){

    ifstream userFile;
    userFile.open(userFileName);

    if(userFile.fail()){
      cout << "User file does not exist! Please enter valid filename." << endl;
      return false;
    }

    stringstream ss;
    string line;
    string command;
    string tempID;
    string tempName;
    string tempCheckedOut;
    Movie* checkedOut;
    queue<Movie*> tempQueue;
    map<Movie*, int> tempRatings;
    bool hasMovie = false;

    string tempAddress = "";
    string tempCCNum = "";
    string tempCCDate = "";
    string tempCCCode = "";
    double tempCharge = 0;
    string chargeString = "";
    string tempPassword = "";
    string subLabel = "";

    while(!userFile.eof()){


      getline(userFile, line);
      ss << line;
      getline(ss, command, ' ');

      if (command == "BEGIN") {

        string subCommand;
        string tempString;
        ss >> tempString;

        if(tempString == "QUEUE"){

          getline(userFile, subCommand);

          while(subCommand != "END QUEUE"){

            subCommand = capitalize(subCommand);
            
            try{
              tempQueue.push((movies->find(subCommand))->second);
            } catch(out_of_range & e){
              cout << "Warning: Queued movie does not exist in movie file" << endl << endl;
            }

            getline(userFile, subCommand);

          }

        } else if (tempString == "RATINGS"){

          getline(userFile, subCommand);
          Movie* ratedMovie;
          string ratedTitle;
          string ratingString;
          int rating;

          while(subCommand != "END RATINGS"){

            ss.ignore(10000, '\n');
            ss.clear();

            ss << subCommand;
            getline(ss, ratingString, ' ');
            getline(ss, ratedTitle);

            ss.ignore(10000, '\n');
            ss.clear();

            ss << ratingString;
            ss >> rating;

            ratedTitle = capitalize(ratedTitle);

            try{ 
              ratedMovie = movies->find(ratedTitle)->second;
              tempRatings.insert(pair<Movie*, int>(ratedMovie, rating));

            } catch(out_of_range & e){
              cout << "Warning: Rated movie does not exist in movie file" << endl << endl;
            }



            getline(userFile, subCommand);

          }

        } else {

          tempID = tempString;

        }

      } else if (command == "NAME:") {

        getline(ss, tempName);

      } else if (command == "ADDRESS:") {

        getline(ss, tempAddress);

      } else if (command == "CREDIT") {

        getline(ss, subLabel, ' ');
        getline(ss, subLabel, ' ');

        if(subLabel == "NUMBER:"){

          getline(ss, tempCCNum);

        } else if (subLabel == "DATE:"){

          getline(ss, tempCCDate);

        } else if (subLabel == "CODE:"){

          getline(ss, tempCCCode);

        }

      } else if (command == "CHARGE:") {

        getline(ss, chargeString);

        ss.ignore(10000, '\n');
        ss.clear();

        if(chargeString == ""){
          tempCharge = 0;
        } else {
          ss << chargeString;
          ss >> tempCharge;
        }

      } else if (command == "PASSWORD:") {

        getline(ss, tempPassword);

      } else if (command == "MOVIE:") {

        getline(ss, tempCheckedOut);     
        tempCheckedOut = capitalize(tempCheckedOut);
        hasMovie = true;

        try{
          checkedOut = movies->find(tempCheckedOut)->second;
        } catch(out_of_range & e){
          cout << "Warning: Queued movie does not exist in movie file" << endl << endl;
        }
        
      } else if (command == "END") {

        User* newUser = new User(tempID, tempName);
        newUser->setAddress(tempAddress);
        newUser->setCreditCardInfo(tempCCNum, tempCCDate, tempCCCode);
        newUser->setUpCard(tempCCNum, tempCharge);
        newUser->setPassword(tempPassword);
        users->insert(pair<string, User*>(tempID, newUser));
        movieQueue = newUser->movieQueue();

        while(!tempQueue.empty()){

          if(!tempQueue.empty()){
            movieQueue->push(tempQueue.front());
            tempQueue.pop();
          } else {
            break;
          }

        }

        map<Movie*, int>* userRatings = newUser->getRatings();

        // typename Map<Movie*, int>::Iterator iter, end;
        // iter = tempRatings.begin();
        // end = tempRatings.end();

        for (map<Movie*, int>::iterator iter = tempRatings.begin(); iter != tempRatings.end(); ++iter) {

        // for(; iter != end; ++iter){

          //cout << "User: " << newUser->getName() << " movie: " << iter->first->getTitle() <<  " rating: " << iter->second << endl;
 
          userRatings->insert(pair<Movie*, int>((*iter).first, (*iter).second));
          movieRatings->find((*iter).first)->second->insert(newUser);

          // cout << (*iter).first->getTitle() << " " << newUser->getName() << endl;
          // cout << "SUCCESSFULLY ADDED A USER TO: " << iter->first->getTitle() << endl;
          tempRatings.erase(tempRatings.find((*iter).first));

        } // end of for loop
        
        if(hasMovie == true){
          newUser->rentMovie(checkedOut);
        }

        tempAddress = "";
        tempCCNum = "";
        tempCCDate = "";
        tempCCCode = "";
        tempCharge = 0;
        chargeString = "";
        tempPassword = "";
        subLabel = "";
        
      }

      ss.ignore(10000, '\n');
      ss.clear();

    }

    userFile.close();
    return true;

}
/* reads in all the user information from a text file 
   it returns true if successful and false if not */

bool Netflix::loadMovies(const char* movieFileName){

    ifstream movieFile;
    movieFile.open(movieFileName);
    queue<Movie*> tempQueue;

    if(movieFile.fail()){
      cout << "Movie file does not exist! Please enter valid filename." << endl;
      return false;
    }

    stringstream ss;
    string line;
    string command;
    string movieTitle;
    string movieKeyword;
    Movie* tempMovie;
    string currentKey;
    Set<string> keywordSet;
    string currentActor;
    string movieActor;
    Set<string> actorSet;
    double cost = 0;
    string costString;

    /* As long as there's more lines in the file, it
    loops and stores the information in the movies map */

    while(!movieFile.eof()){

      getline(movieFile, line);
      ss << line;
      getline(ss, command, ' ');

      if (command == "BEGIN") {

        getline(ss, movieTitle);
        Movie* newMovie = new Movie(movieTitle);
        tempMovie = newMovie;

      } else if (command == "KEYWORD:"){

        getline(ss, movieKeyword);
        tempMovie->addKeyword(movieKeyword);

        if(keywords->find(movieKeyword) == keywords->end()){

          Set<Movie*>* movieSet = new Set<Movie*>;
          movieKeyword = capitalize(movieKeyword);
          keywords->insert(pair<string, Set<Movie*>* >(movieKeyword, movieSet));

        }

      } else if (command == "ACTOR:"){

        getline(ss, movieActor);
        tempMovie->addActor(movieActor);

        if(actors->find(movieActor) == actors->end()){

          Set<Movie*>* movieSet = new Set<Movie*>;
          movieActor = capitalize(movieActor);
          actors->insert(pair<string, Set<Movie*>* >(movieActor, movieSet));

        }

      } else if(command == "COST:") {

        getline(ss, costString);

        ss.ignore(10000, '\n');
        ss.clear();

        if (costString == ""){
          cost = 0;
        } else {
          ss << costString;
          ss >> cost;
        }

        tempMovie->setCost(cost);

      } else if(command == "END") {

        movieTitle = capitalize(movieTitle);
        bool exists = true;

        try{
          movies->find(movieTitle)->second;
        } catch(out_of_range & e){
          exists = false;
        }

        if(movies->find(movieTitle) == movies->end()){
          movies->insert(pair<string, Movie*>(movieTitle, tempMovie));
        }

        Set<User*>* userSet = new Set<User*>;
        movieRatings->insert(pair<Movie*, Set<User*>*>(tempMovie, userSet));

        Set<Movie*>* currentSet;
        keywordSet = tempMovie->getAllKeywords();

        for (Set<string>::iterator iter = keywordSet.begin(); iter != keywordSet.end(); iter++){

          currentKey = *iter;
          currentKey = capitalize(currentKey);
          currentSet = keywords->find(currentKey)->second;
          currentSet->insert(tempMovie);

        }

        Set<Movie*>* currentSet2;
        actorSet = tempMovie->getAllActors();

        for (Set<string>::iterator iter = actorSet.begin(); iter != actorSet.end(); iter++){

          currentActor = *iter;
          currentActor = capitalize(currentActor);
          currentSet2 = actors->find(currentActor)->second;
          currentSet2->insert(tempMovie);

        }

      }

      ss.ignore(10000, '\n');
      ss.clear();

    }

    movieFile.close();
    return true;

}
/* reads in all the movie information from a text file 
   it returns true if successful and false if not */

void Netflix::loginMenu(){

    cout << "1. Log in" << endl;
    cout << "2. Create new user" << endl;
    cout << "3. Quit" << endl << endl;
    cout << "Option: ";

}
/* prints out the login menu */

bool Netflix::login(string loginID, string password){

    bool exists = false;

    if(users->find(loginID) != users->end()){

      User* attemptUser = users->find(loginID)->second;

      if(attemptUser->getPassword() == md5(password)){
     
        currentUser = users->find(loginID)->second;
        movieQueue = currentUser->movieQueue();
        exists = true;

      }

    } 

    return exists;

}
/* checks if user exists and if it does, sets current user and procedes with program 
   it returns true if successful and false if not */

User* Netflix::getUser(){

    return currentUser;

}

bool Netflix::createUser(string newID, string fullName, string address, string ccNum, string ccDate, string ccCode, string password){

    string newUserID = newID;
    string newUserName = fullName;

    if((users->find(newUserID) == users->end() && newUserID != "") && fullName != ""){

      User* tempUser = new User(newUserID, newUserName);
      tempUser->setAddress(address);
      tempUser->setCreditCardInfo(ccNum, ccDate, ccCode);
      tempUser->setUpCard(ccNum, 0);
      tempUser->setPassword(md5(password));

      users->insert(pair<string, User*>(newUserID, tempUser));

      ofstream userFile;
      userFile.open(userFileName.c_str(), std::ios_base::app | std::ios_base::out);
      userFile << endl << "BEGIN " << newUserID << endl;
      userFile << "NAME: " << newUserName << endl;
      userFile << "BEGIN QUEUE" << endl;
      userFile << "END QUEUE" << endl;
      userFile << "BEGIN RATINGS" << endl;
      userFile << "END RATINGS" << endl;
      userFile << "END";
      userFile.close();

      //cout << "Your account has been created!" << endl << endl;
      return true;

    } else {
      //cout << "User ID already exists, please try again." << endl << endl;
      return false;
    }

}
/* allows user to choose new userID that does not already exist and adds new user to data structure
   it returns true if successful and false if not */

int Netflix::updateUser(string address, string ccNum, string ccDate, string ccCode, string password){

    int result = 0;

    if(address == "" && ccNum == "" && ccDate == "" && ccCode == "" && password == ""){
      return -1;
    }

    if(address != ""){  
      currentUser->setAddress(address);
    }

    if((ccNum != "" && ccDate != "" && ccCode != "") && (ccNum != "" || ccDate != "" || ccCode != "")){
      currentUser->setCreditCardInfo(ccNum, ccDate, ccCode);
      currentUser->setUpCard(ccNum, 0);
    } else if (ccNum != "" || ccDate != "" || ccCode != ""){
      result = -2;
    }

    if(password != ""){
      currentUser->setPassword(md5(password));
    }

    return result;
}

// void Netflix::checkedOutMovie(){
Movie* Netflix::checkedOutMovie(){

    Movie* checkedOut = currentUser->currentMovie();
    return checkedOut;

}
/* prints the current checked out movie and its keywords */

void Netflix::userMenu(){

    cout << "1. Search for a movie by title" << endl;
    cout << "2. Search for a movie by keyword" << endl;
    cout << "3. Return the current movie" << endl;
    cout << "4. View Queue" << endl;
    cout << "5. Logout" << endl << endl;
    cout << "Option: ";

}
/* prints the user menu */

queue<Movie*>* Netflix::searchTitle(string title){

    string movieTitle = title;
    Movie* chosenMovie;
    queue<Movie*>* tempQueue = new queue<Movie*>;
    //string currentKeyword;
    //Set<string> keywordSet;
    bool exists = true;

    movieTitle = capitalize(movieTitle);

    if(movies->find(movieTitle) != movies->end()){
      chosenMovie = movies->find(movieTitle)->second;
    // if(exists == true){
      tempQueue->push(chosenMovie);
      
    } 

    return tempQueue;

}
/* searches for movie by title where capitalization doesn't matter */

queue<Movie*>* Netflix::searchKeyword(string keyword){

    Set<Movie*>* tempMovieSet;
    Set<string> keywordSet;
    Movie* tempMovie;
    string chosenKeyword = keyword;
    string currentKeyword;
    queue<Movie*>* tempQueue = new queue<Movie*>;
    stringstream ss;

    chosenKeyword = capitalize(chosenKeyword);

    if(keywords->find(chosenKeyword) != keywords->end()){

      tempMovieSet = keywords->find(chosenKeyword)->second;

      int size = 0;
      size = tempMovieSet->size();

      for(Set<Movie*>::iterator head = tempMovieSet->begin(); head != tempMovieSet->end(); ++head){

        tempMovie = *head;
        tempQueue->push(tempMovie);

      }

  } else {

    if(movies->find(chosenKeyword) != movies->end()){
      return searchTitle(chosenKeyword);
    } else if (searchTitle(chosenKeyword)->empty()){
      return searchActor(chosenKeyword);
    }

  }

  return tempQueue;

}
/* searches for movies by their keywords */

queue<Movie*>* Netflix::searchActor(string actor){

    Set<Movie*>* tempMovieSet;
    Set<string> actorSet;
    Movie* tempMovie;
    string chosenActor = actor;
    string currentActor;
    queue<Movie*>* tempQueue = new queue<Movie*>;
    stringstream ss;

    chosenActor = capitalize(chosenActor);

    if(actors->find(chosenActor) != actors->end()){

      tempMovieSet = actors->find(chosenActor)->second;

      int size = 0;
      size = tempMovieSet->size();

      for(Set<Movie*>::iterator head = tempMovieSet->begin(); head != tempMovieSet->end(); ++head){

        tempMovie = *head;
        tempQueue->push(tempMovie);

      }

  } 

  return tempQueue;

}

void Netflix::turnInMovie(){

    currentUser->returnMovie();

}
/* returns the user's current checked out movie */

bool Netflix::ratingExists(){

    bool exists = true;

    if(currentUser->getRatings()->find(currentUser->currentMovie()) == currentUser->getRatings()->end()){
      exists = false;
    }

    if(currentUser->currentMovie() == NULL){
      return true;
    } else {
      return exists;
    }

}
/* returns if there is a rating for the checked out movie*/

void Netflix::addRating(int num){

  currentUser->getRatings()->insert(pair<Movie*, int>(currentUser->currentMovie(), num));

}
/* adds new rating to ratings Map */

void Netflix::queueMenu(){
    cout << "1. Order movie" << endl;
    cout << "2. Remove movie from queue" << endl;
    cout << "3. Move movie to back of queue" << endl;
    cout << "4. Return to user menu" << endl << endl;
    cout << "Option: ";
}
/* prints out the movie queue menu */

Movie* Netflix::frontOfQueue(){

    Movie* currentMovie;
    currentMovie = movieQueue->front();
    return currentMovie;

}
/* prints out the movie at the front of the queue */

bool Netflix::orderMovie(){

    if(currentUser->currentMovie() != 0){

        //cout << "Return your current movie before ordering another." << endl << endl; 
        return false; 

    } else if (!emptyQueue()){

          Movie* currentMovie = movieQueue->front();
          currentUser->rentMovie(currentMovie);
          movieQueue->pop();
          return true;

    } else {

        return false;

    }

}
/* checks out the movie at the front of the queue */

void Netflix::removeMovie(){

    // bool isEmpty = currentUser->movieQueue()->isEmpty();

    if(!emptyQueue()){

       movieQueue->pop();

    } 

}
/* removes the movie from the front of the queue */

void Netflix::requeueMovie(){

    // bool isEmpty = currentUser->movieQueue()->isEmpty();
    
    if(!emptyQueue()){

      Movie* currentMovie = movieQueue->front();
      movieQueue->push(currentMovie);
      movieQueue->pop();

    }

}
/* takes the movie from the front to the back of the queue */

void Netflix::enqueueMovie(Movie* selection){

    queue<Movie*>* movies = currentUser->movieQueue();
    movies->push(selection);

}
/* queues a given movie */

void Netflix::logout(){

    ofstream userFile;
    userFile.open(userFileName.c_str());

    for (map<string, User*>::iterator userIter = users->begin(); userIter != users->end(); ++userIter){

    // for(; userIter != userEnd; ++userIter){

      userFile << "BEGIN " << (*userIter).second->getID() << endl;
      userFile << "NAME: " << (*userIter).second->getName() << endl;
      userFile << "ADDRESS: " << (*userIter).second->getAddress() << endl;
      userFile << "CREDIT CARD NUMBER: " << (*userIter).second->getCCNumber() << endl;
      userFile << "CREDIT CARD DATE: " << (*userIter).second->getCCDate() << endl;
      userFile << "CREDIT CARD CODE: " << (*userIter).second->getCCCode() << endl;
      userFile << "CHARGE: " << (*userIter).second->getCard()->second << endl;
      userFile << "PASSWORD: " << (*userIter).second->getPassword() << endl;

      if((*userIter).second->currentMovie()){
          userFile << "MOVIE: " << (*userIter).second->currentMovie()->getTitle() << endl;
      }
              
      userFile << "BEGIN QUEUE" << endl;

      (*userIter).second->movieQueue();
      queue<Movie*>* userMovies = (*userIter).second->movieQueue();

      while(!userMovies->empty()){

          userFile << userMovies->front()->getTitle() << endl;
          userMovies->pop();

      }

      userFile << "END QUEUE" << endl;

      userFile << "BEGIN RATINGS" << endl;

      map<Movie*, int>* tempRatings = (*userIter).second->getRatings();

      for (map<Movie*, int>::iterator iter = tempRatings->begin(); iter != tempRatings->end(); ++iter){

      // for(; iter != end; ++iter){ 

        userFile << (*iter).second << " " << (*iter).first->getTitle() << endl;

      } // end of for loop


      userFile << "END RATINGS" << endl;

      userFile << "END" << endl;

    } // end of for loop

    // somehow return the user to login menu

}
/* writes all of the data back into the user file and goes back to the login menu */

string Netflix::capitalize(string anyString){

    for(int i = 0; i < anyString.size(); i++){
        anyString[i] = toupper(anyString[i]);
    }

    return anyString;
}
/* returns an uppercase version of the provided string */

bool Netflix::emptyQueue(){
    return movieQueue->empty();
}

double Netflix::basicSimilarity(User* first, User* second){

  map<Movie*, int>* firstMap = first->getRatings();
  map<Movie*, int>* secondMap = second->getRatings();
  Set<Movie*> firstSet;
  Set<Movie*> secondSet;
  Set<Movie*> intersection;

  for(map<Movie*, int>::iterator iter = firstMap->begin(); iter != firstMap->end(); ++iter){
    
    firstSet.insert((*iter).first);

  }

  for(map<Movie*, int>::iterator iter = secondMap->begin(); iter != secondMap->end(); ++iter){

    secondSet.insert((*iter).first);

  }

  bool isEmpty = false;

  if(firstSet.empty() || secondSet.empty()){
    isEmpty = true;
  } else {
    intersection = firstSet.setIntersection(secondSet);
  }

  double sum = 0;
  int count = 0;
  double similarity = 0;

  if(isEmpty){

    similarity = 0;

  } else {

    int a = 0; //first user's ratings
    int b = 0; //second user's ratings

    //iterate over movies they have both rated
    for(Set<Movie*>::iterator iter = intersection.begin(); iter != intersection.end(); iter++){

      a = firstMap->find(*iter)->second;
      b = secondMap->find(*iter)->second;

      sum = sum + (double)(a - b)/4;
      count++;

    }

    //cout << "*******************************" << endl;

    similarity = sum/count;

    if(similarity < 0){
      similarity = similarity * -1;
    }

  }

  return similarity;

}
    /* calculates the basic similarity between two users */

void Netflix::dijkstra(int src){

    int numOfVertices = users->size();
    double predecessor[numOfVertices];
    bool mark[numOfVertices];
    int source = src;
    

    for(int i = 0; i < numOfVertices; i++) {
      mark[i] = false;
      predecessor[i] = -1;
      distance[i] = 99999;
    }

    distance[src] = 0;

    double minDistance = 99999;
    int closestUnmarkedNode;
    int count = 0;

    while(count < numOfVertices) {

        closestUnmarkedNode = getClosestNode(numOfVertices, mark, distance);
        mark[closestUnmarkedNode] = true;

        for(int i = 0; i < numOfVertices; i++) {

          if((!mark[i]) && (similarities[closestUnmarkedNode][i] > 0) ) {

            if(distance[i] > (distance[closestUnmarkedNode] + similarities[closestUnmarkedNode][i])) {

              distance[i] = (distance[closestUnmarkedNode] + similarities[closestUnmarkedNode][i]);
              predecessor[i] = closestUnmarkedNode;

            }

          }

        }

        count++;

    }

}

int Netflix::getClosestNode(int numOfVertices, bool mark[], double distance[]){

  int minDistance = 99999;
  int closestUnmarkedNode;

  for(int i = 0; i < numOfVertices; i++) {

    if((!mark[i]) && ( minDistance >= distance[i])) {

      minDistance = distance[i];
      closestUnmarkedNode = i;

    }

  }

  return closestUnmarkedNode;
}

double Netflix::interest(Movie* movie){

  double interestingness = 0;
  double R = 0;
  double W = 0;
  int a = 0;
  int b = 0;

  //assigns a to the index of current user
  for(map<string, User*>::iterator head = users->begin(); head != users->end(); head++){
    if(head->second == currentUser){
      break;
    }
    a++;
  }

  //calls dijkstra's on current user
  this->dijkstra(a);

  if(currentUser->getRatings()->find(movie) == currentUser->getRatings()->end()){

    Set<User*>* userSet = movieRatings->find(movie)->second;

    //iterates through everyone who watched the movie
    for(Set<User*>::iterator userIter = userSet->begin(); userIter != userSet->end(); userIter++){

      if(currentUser == *userIter){
        continue;
      }

      b = 0;


      //this is skipping username "Chen" for some reason. It's not finding it in users!!!
      for(map<string, User*>::iterator head = users->begin(); head != users->end(); head++){

        if(head->second == *userIter){
          break;
        }
        b++;
      }

      if(b < 0){
        continue;
      }

      int rating = (*userIter)->getRatings()->find(movie)->second;

      R = R + ((1 - distance[b]) * rating);
      W = W + (1 - distance[b]);

    }

  }

  interestingness = R/W;

  return interestingness;

}

Movie* Netflix::recommend(){

  //iterate over all movies the user hasn't rated and return the one with the largest interest.

  Movie* bestMovie = 0;
  Movie* currMovie;
  double best = 0;
  double current = 0;

  for(map<string, Movie*>::iterator iter = movies->begin(); iter != movies->end(); ++iter){

    if(currentUser->getRatings()->find(iter->second) == currentUser->getRatings()->end()){

      current = interest(iter->second);
      currMovie = iter->second;

      if(current > best){
        best = current;
        bestMovie = iter->second;
      }

    }
  }

  return bestMovie;

}