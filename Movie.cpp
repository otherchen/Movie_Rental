#include "Movie.h"
#include <iostream>
#include <cctype>

using namespace std;

Movie & Movie::operator=(const Movie & other){
	this->title = other.getTitle();
	this->keyWords = other.getAllKeywords();
	return *this;
}

bool Movie::operator==(const Movie & other){
	if(this->title == other.getTitle() && this->keyWords == other.getAllKeywords()){
		return true;
	} else {
		return false;
	}
}

Movie::Movie(){
	this->title = "noTitle";
}

Movie::Movie (string title){
	this->title = title;
}      

Movie::Movie (const Movie & other){
	this->title = other.getTitle();
	this->keyWords = other.getAllKeywords();
}  

Movie::~Movie (){
	//automatic destructor
}                  

string Movie::getTitle () const {
	return title;
}   

void Movie::addKeyword (string keyword){

	bool exists = false;
	exists = (keyWords.find(keyword) != keyWords.end());

	if(exists == false){
		keyWords.insert(keyword);
	}

} 

const Set<string> & Movie::getAllKeywords () const{
	return keyWords;
}

void Movie::addActor(std::string actor){

	if(actors.find(actor) == actors.end()){
		actors.insert(actor);
	}

}

const Set<string> & Movie::getAllActors () const{
	return actors;
}

void Movie::setCost(double num){
	rentalCost = num;
}

double Movie::getCost(){
	return rentalCost;
}