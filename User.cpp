#include "User.h"
#include <iostream>

using namespace std;

User::User (){
	this->id = "";
	this->name = "";
	this->address = "";
	this->creditCardNumber = "";
	this->creditCardDate = "";
	this->creditCardCode = "";
	creditCard = new pair<string, double>;
	this->creditCard->first = "";
	this->creditCard->second = 0;
	this->password = "";
	userQueue = new queue<Movie*>;
	ratings = new map<Movie*, int>;
	checkedOut = 0;
}

User::User (string ID, string name){
	this->id = ID;
	this->name = name;
	this->address = "";
	this->creditCardNumber = "";
	this->creditCardDate = "";
	this->creditCardCode = "";
	creditCard = new pair<string, double>;
	this->creditCard->first = "";
	this->creditCard->second = 0;
	this->password = "";
	userQueue = new queue<Movie*>;
	ratings = new map<Movie*, int>;
	checkedOut = 0;
} 

User::User (const User & other){
	this->id = other.getID();
	this->name = other.getName();
}

User::~User (){
	delete userQueue;
}            

string User::getID () const{
	return id;
}  

string User::getName () const{
	return name;
} 

queue<Movie*> * User::movieQueue (){
	return userQueue;
}
/* returns a pointer to the user's movie queue.
This is the easiest way to ensure that you can modify the queue.
(If you return by reference, that's also possible, but you'd need
to be very careful not to invoke any deep copy constructors or
assignments. A pointer is thus safer.) */

void User::rentMovie (Movie *m){

	if(checkedOut == 0){
		checkedOut = m;
	}

}
/* sets the user's currently rented movie to m.
If the user already has a movie checked out, then it does nothing.
(So no overwriting the current movie.) */

void User::returnMovie (){
	checkedOut = 0;
}
/* returns the movie that the user currently has checked out.
Does nothing if the user doesn't currently have a movie. */

Movie* User::currentMovie (){

	return checkedOut;

}
/* returns the user's current checked out movie.
Returns NULL if the user has no movie checked out. */

map<Movie*, int>* User::getRatings(){

	return ratings;

}

void User::setAddress(string address){
	this->address = address;
}

std::string User::getAddress(){
	return address;
}

void User::setCreditCardInfo(string num, string date, string code){
	creditCardNumber = num;
	creditCardDate = date;
	creditCardCode = code;
}

std::string User::getCCNumber(){
	return creditCardNumber;
}

std::string User::getCCDate(){
	return creditCardDate;
}

std::string User::getCCCode(){
	return creditCardCode;
}

void User::setUpCard(string number, double charge){
	creditCard->first = number;
	creditCard->second = charge;
}

void User::chargeCard(double charge){
	creditCard->second = creditCard->second + charge;
}

std::pair<string, double>* User::getCard(){
	return creditCard;
}

void User::setPassword(string password){
	this->password = password;
}

std::string User::getPassword(){
	return password;
}