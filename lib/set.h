#ifndef SET_H
#define SET_H

#include <iostream>
#include "map.h"
#include "mergeSort.h"
#include <set>

using namespace std;

template <class T>
class Set : public std::set<T>
//class MyContainer : public std::vector<MyObject>
{
  public:
    // Set ();  // constructor for a new empty set

    // Set (const Set<T> & other); // deep copy constructor

    // ~Set (); // destructor

    // int size () const; // returns the number of elements in the set

    // void add (const T item); 
    //   /* Adds the item to the set.
    //      If the item is already in the set, it should do nothing.
    //   */

    // void remove (const T item);
    //  /* Removes the item from the set.
    //     If the item was not in the set, it should do nothing. */

    // bool contains (const T item) const;
    //  /* Returns whether the item is in the set. */

    // void merge (const Set<T> & other);
    //   Adds all elements of other to this set. 
    //     However, will not create duplicates, i.e., it ignores elements
    //     already in the set. 

    // const Map<T, int> getStorage() const;
    //  /* Returns the Map item */

    // void setStorage(const Map<T, int> & other);
    //  /* Sets the internal storage */

    // void print();
    //  /* prints values */

    // Set<T> & operator=(const Set<T> & other);
    //  /* overloading "=" operator */

    // bool operator==(const Set<T> & other);
    //  /* overloading "=" operator */

    // // void first();
    // //  /* sets current to head */

    // // void next();
    // //   sets current to current->next 

    // // const T & getCurrent ();
    // //  /* returns current value */

    Set<T> setUnion (const Set<T> & other) const;
    // Returns the union of this and other. Does not alter this.

    Set<T> setIntersection (const Set<T> & other) const;
    // Returns the intersection of this and other. Does not alter this.

    // public:
    // class Iterator {
    //      /* add any constructors that you feel will be helpful,
    //         and choose whether to make them public or private. */

    //     public:
    //        Iterator();

    //        Iterator(typename Map<T, int>::Iterator otherIter);
           
    //        T operator* () const;
    //           // return the item the iterator is at

    //        Set<T>::Iterator operator++ ();
    //           // advances the iterator (pre-increment)

    //        Set<T>::Iterator operator= (const Set<T>::Iterator & other);
    //           // assigns the other iterator to this iterator and returns this

    //        bool operator== (const Set<T>::Iterator & other) const;
    //           // returns whether this iterator is equal to the other iterator

    //        bool operator!= (const Set<T>::Iterator & other) const;
    //           // returns whether this iterator is not equal to the other iterator

    //        /* Optionally, if you think that it makes your code easier to write,
    //           you may also overload other operators: */

    //        /* You may define a public copy constructor and/or default constructor
    //           if you think it would be helpful. */

    //     private:
    //       typename Map<T, int>::Iterator iterator;
    //       Set<T>* whom;
    };

//     typename Set<T>::Iterator begin () const;
//     // returns an iterator initialized to the first element

//     typename Set<T>::Iterator end () const;
//     /* returns an iterator initialized past the last element,
//       to designate that the end of the map has been reached. */

//   private:
//     Map<T, int> internalStorage;
//      /* You should use a Map (your own implementation) to store your set.
//         It is part of your assignment to figure out what types you 
//         need for the keyType and valueType. */

//     MapItem<T, int> *current;

//      /* If you like, you can add further data fields and private
//         helper methods. */
// };

// template <class T>
// Set<T> & Set<T>::operator=(const Set<T> & other){
//   internalStorage = other.getStorage();
//   //changed
//   return *this;
// }

// template <class T>
// bool Set<T>::operator==(const Set<T> & other){
//   if(internalStorage == other.getStorage()){
//     return true;
//   } else {
//     return false;
//   }
// }

// template <class T>
// Set<T>::Set(){
//     //Map already initialized
// }

// template <class T>
// Set<T>::Set(const Set<T> & other){
//     internalStorage = other.getStorage();
// }

// template <class T>
// Set<T>::~Set(){
//     //Map will destruct itself
// }

// template <class T>
// int Set<T>::size() const{

//     int size = 0;
//     size = internalStorage.size();
//     return size;

// }

// template <class T>
// void Set<T>::add(const T item){

//     internalStorage.add(item, 0);

// }

// template <class T>
// void Set<T>::remove(const T item){

//     internalStorage.remove(item);

// }

// template <class T>
// bool Set<T>::contains(const T item) const{

//     bool exists = true;

//     try { 
//       internalStorage.get(item);
//     } catch(NoSuchElementException & e) {
//       exists = false;
//     }

//     return exists;

// }

// template <class T>
// void Set<T>::merge(const Set<T> & other){

//     internalStorage.merge(other.getStorage());

// }

// template <class T>
// const Map<T, int> Set<T>::getStorage() const{

//     return internalStorage;

// }

// template <class T>
// void Set<T>::print(){

//     internalStorage.print();

// }

// // template <class T>
// // void Set<T>::first(){

// //     internalStorage.first();

// // }

// // template <class T>
// // void Set<T>::next(){

// //     internalStorage.next();

// // }

// // template <class T>
// // const T & Set<T>::getCurrent(){

// //     return internalStorage.getCurrentKey();

// // }

template <class T>
Set<T> Set<T>::setUnion(const Set<T> & other) const{
// 1. Use your iterators on this and other to produce vectors containing the elements of your two sets.
// 2. Use your Merge Sort implementation for those two vectors to sort them.
// 3. Now that they are sorted, use an O(n) algorithm to compute the intersection/union, and write it into a new vector.
// 4. Finally, go through the vector, and write the elements into a new Set<T>, which you then return.

//     vector<T> thisVector, otherVector, totalVector;
//     T currentItem;

//     // typename Set<T>::Iterator iter, end;
//     // iter = this->begin();
//     // end = this->end();
// //map<Movie*, int>::iterator iter = firstMap->begin(); iter != firstMap->end(); ++iter
//     for(Set<T>::iterator iter = this->begin(); iter != this->end(); ++iter){
//       currentItem = *iter;
//       thisVector.push_back(currentItem);
//     }

//     // iter = other.begin();
//     // end = other.end();

//     for(Set<T>::iterator iter = other.begin(); iter != other.end(); ++iter){
//       currentItem = *iter;
//       otherVector.push_back(currentItem);
//     }

//     MergeSort mSort;
//     thisVector = mSort.sort(thisVector);
//     otherVector = mSort.sort(otherVector);

//     int i = 0, j = 0;

//     while (i != (thisVector.size() + 1) && j != (otherVector.size() + 1)){
//       if(i > thisVector.size()){
//         totalVector.push_back(otherVector[j]);
//         j++;
//       } else if(j > thisVector.size()){
//         totalVector.push_back(thisVector[i]);
//         i++;
//       } else if(thisVector[i] > otherVector[j]){
//         totalVector.push_back(thisVector[i]);
//         i++;
//       } else if(thisVector[i] < otherVector[j]){
//         totalVector.push_back(otherVector[j]);
//         j++;
//       }
//     }

//     Set<T> tempSet(*this);

//     for(int i = 0; i < totalVector.size() + 1; i++){
//         tempSet.add(totalVector[i]);
//     }

//     //tempSet.merge(other);
//     return tempSet;

}

template <class T>
Set<T> Set<T>::setIntersection(const Set<T> & other) const{

// 1. Use your iterators on this and other to produce vectors containing the elements of your two sets.
// 2. Use your Merge Sort implementation for those two vectors to sort them.
// 3. Now that they are sorted, use an O(n) algorithm to compute the intersection/union, and write it into a new vector.
// 4. Finally, go through the vector, and write the elements into a new Set<T>, which you then return.

    vector<T> thisVector, otherVector, totalVector;
    T currentItem;

    // typename Set<T>::Iterator iter, end;
    // iter = this->begin();
    // end = this->end();

    //for(; iter != end; ++iter){
    for(typename Set<T>::iterator iter = this->begin(); iter != this->end(); ++iter){
      currentItem = *iter;
      thisVector.push_back(currentItem);
    }

    // iter = other.begin();
    // end = other.end();

    //for(; iter != end; ++iter){
    for(typename Set<T>::iterator iter = other.begin(); iter != other.end(); ++iter){
      currentItem = *iter;
      otherVector.push_back(currentItem);
    }

    MergeSort mSort;
    thisVector = mSort.sort(thisVector);
    otherVector = mSort.sort(otherVector);
    
    int i = 0, j = 0;

    while (i != (thisVector.size()) && j != (otherVector.size())){
      if(i > thisVector.size()){
        // totalVector.push_back(otherVector[j]);
        // j++;
        break;
      } else if(j > thisVector.size()){
        // totalVector.push_back(thisVector[i]);
        // i++;
        break;
      } else if (thisVector[i] == otherVector[j]){
        if(thisVector[i] == NULL || otherVector[j] == NULL){
          break;
        } else {
          totalVector.push_back(thisVector[i]);
          i++;
          j++;

        }
      } else if(thisVector[i] > otherVector[j]){
        // totalVector.push_back(thisVector[i]);
        // i++;
        j++;
      } else if(thisVector[i] < otherVector[j]){
        // totalVector.push_back(otherVector[j]);
        // j++;
        i++;
      }
    }

    Set<T> tempSet;

    for(int i = 0; i < totalVector.size(); i++){
      tempSet.insert(totalVector[i]);
    }

    // Set<T> tempSet(*this);

    // for(int i = 0; i < totalVector.size() + 1; i++){
    //     tempSet.add(totalVector[i]);
    // }

    //tempSet.merge(other);
    // return tempSet;

    // Set<T> tempSet;
    // Map<T, int> tempMap;

    // tempMap = internalStorage.mapIntersection(other.getStorage());
    // tempSet.setStorage(tempMap);

    return tempSet;

}

// template <class T>
// void Set<T>::setStorage(const Map<T, int> & other){
//     internalStorage = other;
// }

// template <class T>
// typename Set<T>::Iterator Set<T>::begin () const{

//     return Set<T>::Iterator(internalStorage.begin());

// }
// // returns an iterator initialized to the first element

// template <class T>
// typename Set<T>::Iterator Set<T>::end () const{

//     return Set<T>::Iterator(internalStorage.end());

// }
// /* returns an iterator initialized past the last element,
// to designate that the end of the map has been reached. */


// /********************************** Iterator Functions ************************************/

// template <class T>
// Set<T>::Iterator::Iterator(){

// }

// template <class T>
// Set<T>::Iterator::Iterator(typename Map<T,int>::Iterator otherIter){

//   iterator = otherIter;
//   // whom = whoIAmTraversing;
//   // typename Map<T, int>::Iterator iter(*internalStorage, start);
//   // iterator = iter;

// }

// template <class T>
// T Set<T>::Iterator::operator* () const{
//    return (*iterator).first;
// }
// // return the item the iterator is at

// template <class T>
// typename Set<T>::Iterator Set<T>::Iterator::operator++ (){
//    ++iterator;
//    return *this;
// }
// // advances the iterator (pre-increment)

// template <class T>
// typename Set<T>::Iterator Set<T>::Iterator::operator= (const Set<T>::Iterator & other){
//     this->iterator = other.iterator;
//     return *this;
// }
// // assigns the other iterator to this iterator and returns this

// template <class T>
// bool Set<T>::Iterator::operator== (const Set<T>::Iterator & other) const{

//   bool equals = false;

//   if(iterator == other){
//     equals = true;
//   }

//   return equals;

// }
// // returns whether this iterator is equal to the other iterator

// template <class T>
// bool Set<T>::Iterator::operator!= (const Set<T>::Iterator & other) const{

//   bool notEquals = false;

//   if(this->iterator != other.iterator){
//     notEquals = true;
//   }

//   return notEquals;

// }
// // returns whether this iterator is not equal to the other iterator

#endif