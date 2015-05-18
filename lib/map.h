#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdexcept>
#include <exception>

using namespace std;

class NoSuchElementException: public exception {
  public:
    NoSuchElementException(){
      //constructor
    }
};

template <class FirstType, class SecondType> 
struct Pair {
   FirstType first;
   SecondType second;

   Pair (FirstType first, SecondType second)
      { this->first = first; this->second = second; }
   // we're very nice and give you this piece of difficult code for free :-P
};

template <class keyType, class valueType>
struct MapItem
{
  keyType key;
  valueType value;
  MapItem<keyType, valueType> *prev, *next;
};

template <class keyType, class valueType>
class Map
{
  public:
    Map ();  // constructor for a new empty map

    Map (const Map<keyType, valueType> & other); // deep copy constructor

    ~Map (); // destructor

    int size () const; // returns the number of key-value pairs

    void add (const keyType key, const valueType value); 
      /* Adds a new association between the given key and the given value.
         If the key already has an association, it should do nothing.
      */

    void remove (const keyType key);
     /* Removes the association for the given key.
        If the key has no association, it should do nothing. */

    Pair<keyType, valueType> getPair (const keyType & key) const;

    const valueType & get (const keyType & key) const;
     /* Returns the value associated with the given key
        and throws an exception if it cannot be found */

    void merge (const Map<keyType, valueType> & other);
     /* Adds all the key-value associations of other to the current map.
        If both maps (this and other) contain an association for the same
        key, then the one of this is used. */

    void print () const;
     /* Prints out all the key/value pairs in the map */

    Map<keyType, valueType> & operator=(const Map<keyType, valueType> & other);
     /* overloads "=" operator */

    bool operator==(const Map<keyType, valueType> & other);
     /* overloads "==" operator */

    MapItem<keyType, valueType>* getHead() const;

    // void first();
    //  /* sets current to head */

    // void next();
    //  /* sets current to current->next */

    // const keyType & getCurrentKey ();
    //  /* gets current key */

    // const valueType & getCurrentValue ();
    //  /* gets current value */

    Map<keyType, valueType> mapIntersection(const Map<keyType, valueType> & other) const;
     /* gets intersection of two maps */

    bool isEmpty();

    class Iterator {
        private:
             MapItem <keyType, valueType>* index;

         /* add any constructors that you feel will be helpful,
            and choose whether to make them public or private. */

        public:
          Iterator();

          Iterator(MapItem <keyType, valueType>* start);

          Pair<keyType, valueType> operator* () const;
              // return the current (key, value) pair the iterator is at

          Map<keyType,valueType>::Iterator operator++ ();
              // advances the iterator (pre-increment)

          Map<keyType,valueType>::Iterator operator= (const Map<keyType,valueType>::Iterator & other);
              // assigns the other iterator to this iterator and returns this

          bool operator== (const Map<keyType,valueType>::Iterator & other) const;
              // returns whether this iterator is equal to the other iterator

          bool operator!= (const Map<keyType,valueType>::Iterator & other) const;
              // returns whether this iterator is not equal to the other iterator

          /* Optionally, if you think that it makes your code easier to write,
              you may also overload other operators: */

          /* You may define a public copy constructor and/or default constructor
              if you think it would be helpful. */
    };

    Map<keyType,valueType>::Iterator begin () const;
    // returns an iterator initialized to the first element

    Map<keyType,valueType>::Iterator end () const;
       /* returns an iterator initialized past the last element,
          to designate that the end of the map has been reached. */

  private:
     /* The head and tail of the linked list you're using to store
        all the associations. */

     MapItem <keyType, valueType> *head, *tail;
     MapItem <keyType, valueType> *current;

     /* If you like, you can add further data fields and private
        helper methods. */
};

template <class keyType, class valueType>
Map<keyType, valueType> & Map<keyType, valueType>::operator=(const Map<keyType, valueType> & other){

    if(*this == other){
      return *this;
    }

    if(head != 0){
      MapItem<keyType, valueType>* tempHead = head;
      MapItem<keyType, valueType>* tempNext = head->next;

      while(tempHead != 0){
        remove(head->key);
        tempNext = tempHead->next;
        tempHead = tempNext;
      }

      head = 0;
      tail = 0;
      current = 0;
    }

    merge(other);
    return *this;

}

template <class keyType, class valueType>
bool Map<keyType, valueType>::operator==(const Map<keyType, valueType> & other){

  int size = this->size();
  NoSuchElementException NoSuchElement;

  if(size != other.size()){
    return false;
  }

  if(head != 0){
    MapItem<keyType, valueType>* tempHead = head;
    MapItem<keyType, valueType>* tempNext = head->next;

      while(tempHead != 0){

        bool exists = true;

        try {
          other.get(tempHead->key);
        } catch(NoSuchElementException & e) {
          exists = false;
        }

        if(exists == false){
          return false;
        }

        tempNext = tempHead->next;
        tempHead = tempNext;
      }

      return true;

    }

}

template <class keyType, class valueType>
Map<keyType, valueType>::Map(){

    head = 0;
    tail = 0;
    current = 0;

}

template <class keyType, class valueType>
Map<keyType, valueType>::Map(const Map<keyType, valueType> & other){

    head = 0;
    tail = 0;
    current = 0;

    merge(other);
 
}

template <class keyType, class valueType>
Map<keyType, valueType>::~Map(){

  if(head !=0){
    MapItem<keyType, valueType>* tempHead = head;
    MapItem<keyType, valueType>* tempNext = head->next;

    while(tempHead != 0){
      tempNext = tempHead->next;
      delete tempHead;
      tempHead = tempNext;
    }
  } 
}

template <class keyType, class valueType>
int Map<keyType, valueType>::size() const{

  int count = 0;

  if(head != 0){

      MapItem<keyType, valueType>* tempHead = head;
      MapItem<keyType, valueType>* tempNext = head->next;

      while(tempHead != 0){
        tempNext = tempHead->next;
        tempHead = tempNext;
        count++;
      }

  }

   return count;
}

template <class keyType, class valueType>
void Map<keyType, valueType>::add(const keyType key, const valueType value){
   
  bool exists = true;
  NoSuchElementException NoSuchElement;

  try {
    get(key);
  } catch (NoSuchElementException & e) {
    exists = false;
  }

  if (exists == false){

    MapItem<keyType, valueType>* newItem = new MapItem<keyType, valueType>;

    if(head == 0){

      head = newItem;
      tail = newItem;
      head->prev = 0;
      head->next = 0;
      tail->prev = 0;
      tail->next = 0;
      current = head;

    } else {

      tail->next = newItem;
      newItem->prev = tail;
      newItem->next = 0;
      tail = newItem;

    }

    tail->key = key;
    tail->value = value;
  }

}

template <class keyType, class valueType>
void Map<keyType, valueType>::remove (const keyType key){

  if(head != 0){
    MapItem<keyType, valueType>* toRemove = head;
    MapItem<keyType, valueType>* toRemoveNext = head->next;

    if(toRemove->key == key){
      head = head->next;
    } else {

      while(toRemove != 0){

          if(toRemove->key == key){
            toRemove->prev->next = toRemove->next;
            if(toRemove->next != 0){
               toRemove->next->prev = toRemove->prev;
               break;
            } else {
               tail = toRemove->prev;
               break;
            }
          } 

          toRemoveNext = toRemove->next;
          toRemove = toRemoveNext;
      }

    }
   delete toRemove;
  }

}

template <class keyType, class valueType>
Pair<keyType, valueType> Map<keyType, valueType>::getPair (const keyType & key) const{

  if(head != 0){

    Pair<keyType, valueType> pair;
    MapItem<keyType, valueType>* tempHead = head;
    MapItem<keyType, valueType>* tempNext = head->next;

    while(tempHead != 0){

      if(tempHead->key == key){
        pair.first = tempHead->key;
        pair.second = tempHead->value;
        return pair;
      }

      tempNext = tempHead->next;
      tempHead = tempNext;
    }

  } 
    NoSuchElementException NoSuchElement;
    throw NoSuchElement;
    //return valueType();

}

template <class keyType, class valueType>
const valueType & Map<keyType, valueType>::get (const keyType & key) const{

  if(head != 0){

    MapItem<keyType, valueType>* tempHead = head;
    MapItem<keyType, valueType>* tempNext = head->next;

    while(tempHead != 0){

      if(tempHead->key == key){
         return tempHead->value;
      }

      tempNext = tempHead->next;
      tempHead = tempNext;
    }

  } 
    NoSuchElementException NoSuchElement;
    throw NoSuchElement;
    //return valueType();

}

template <class keyType, class valueType>
void Map<keyType, valueType>::merge (const Map<keyType, valueType> & other){
 
  if(other.head != 0){
 
      MapItem<keyType, valueType>* tempHead = other.head;
      MapItem<keyType, valueType>* tempNext = other.head->next;
      NoSuchElementException NoSuchElement;

      while(tempHead != 0){

        keyType tempKey = tempHead->key;
        valueType tempValue = tempHead->value;
   
        bool exists = true;

        try {
          get(tempKey);
        } catch (NoSuchElementException & e) {
          exists = false;
        }

        if(exists == false){
          add(tempKey, tempValue);
        } else {
          //If there are repeated keys, keep the old value 
        }

        tempNext = tempHead->next;
        tempHead = tempNext;

      }

  }

}

template <class keyType, class valueType>
void Map<keyType, valueType>::print() const{

  if(head != 0){
    MapItem<keyType, valueType>* tempHead = head;
    MapItem<keyType, valueType>* tempNext = head->next;

    while(tempHead != 0){
      cout << "Key: " << tempHead->key << " / Value: " << tempHead->value << endl;
      tempNext = tempHead->next;
      tempHead = tempNext;
    }
  } else {
    cout << "MAP IS EMPTY!" << endl;
  }

}

template <class keyType, class valueType>
MapItem<keyType, valueType>* Map<keyType, valueType>::getHead() const{
    return head;
}

// template <class keyType, class valueType>
// void Map<keyType, valueType>::first(){
//     NoSuchElementException NoSuchElement;
//     current = head;
//     if (current == 0) {
//       throw NoSuchElement;
//     }
// }

// template <class keyType, class valueType>
// void Map<keyType, valueType>::next(){
//     NoSuchElementException NoSuchElement;
//     if(current->next == 0){
//       throw NoSuchElement;
//     } else {
//       current = current->next;
//     }
// }

// template <class keyType, class valueType>
// const keyType & Map<keyType, valueType>::getCurrentKey(){
//     NoSuchElementException NoSuchElement;
//     if(current == 0){
//       throw NoSuchElement;
//       //return keyType();
//     } else {
//       return current->key;
//     }
// }

// template <class keyType, class valueType>
// const valueType & Map<keyType, valueType>::getCurrentValue(){
//     NoSuchElementException NoSuchElement;
//     if(current == 0){
//       throw NoSuchElement;
//       //return valueType();
//     } else {
//       return current->value;
//     }
// }

template <class keyType, class valueType>
Map<keyType, valueType> Map<keyType, valueType>::mapIntersection(const Map<keyType, valueType> & other) const {

    Map<keyType, valueType> tempMap;
    NoSuchElementException NoSuchElement;

    if(head != 0){
    MapItem<keyType, valueType>* tempHead = head;
    MapItem<keyType, valueType>* tempNext = head->next;

      while(tempHead != 0){

        bool exists = true;

        try {
          other.get(tempHead->key);
        } catch(NoSuchElementException & e) {
          exists = false;
        }

        if(exists == true){
          tempMap.add(tempHead->key, tempHead->value);
        }

        tempNext = tempHead->next;
        tempHead = tempNext;
      }

    }

    return tempMap;
}

template <class keyType, class valueType>
typename Map<keyType,valueType>::Iterator Map<keyType,valueType>::begin () const{

    return Map<keyType,valueType>::Iterator(head);

}
     // returns an iterator initialized to the first element

template <class keyType, class valueType>
typename Map<keyType,valueType>::Iterator Map<keyType,valueType>::end () const{

    return Map<keyType,valueType>::Iterator(0);

}
    /* returns an iterator initialized past the last element,
      to designate that the end of the map has been reached. */

/************************* Iterator Functions ******************************/

template <class keyType, class valueType>
Map<keyType, valueType>::Iterator::Iterator(){

    index = 0;
    
}

template <class keyType, class valueType>
Map<keyType, valueType>::Iterator::Iterator(MapItem<keyType, valueType>* start){

    index = start;

}

template <class keyType, class valueType>
Pair<keyType, valueType> Map<keyType, valueType>::Iterator::operator* () const{

    keyType key = index->key;
    valueType value = index->value;
    Pair<keyType, valueType> pair(key, value);

    return pair;

}
    // return the current (key, value) pair the iterator is at

template <class keyType, class valueType>
typename Map<keyType,valueType>::Iterator Map<keyType, valueType>::Iterator::operator++ (){

    index = index->next;
    return *this;

}
    // advances the iterator (pre-increment)

template <class keyType, class valueType>
typename Map<keyType,valueType>::Iterator Map<keyType,valueType>::Iterator::operator= (const Map<keyType,valueType>::Iterator & other){

    this->index = other.index;
    return *this;

}
    // assigns the other iterator to this iterator and returns this

template <class keyType, class valueType>
bool Map<keyType,valueType>::Iterator::operator== (const Map<keyType,valueType>::Iterator & other) const{

    bool equals = false;

    if(this->index == other.index){
      equals = true;
    }

    return equals;

}
    // returns whether this iterator is equal to the other iterator

template <class keyType, class valueType>
bool Map<keyType,valueType>::Iterator::operator!= (const Map<keyType,valueType>::Iterator & other) const{
    bool notEquals = false;

    if(this->index != other.index){
      notEquals = true;
    }

    return notEquals;
}

template <class keyType, class valueType>
bool Map<keyType,valueType>::isEmpty(){
  if(head == 0){
    return true;
  } else {
    return false;
  }
}

#endif