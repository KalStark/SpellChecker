// HashSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP
#include <iostream>
#include <functional>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();
    void destory();
    void resize();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);
    void copy(const HashSet& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    HashFunction hashFunction;
    
    struct Node
    {
        T key;
        Node* next;
    };
        void destory(Node** Dying_Table, int space);



    Node* start;
    Node* prev;
    Node** table;
    int cap;
    int hash_size;

};



template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}
{
    table = new Node* [DEFAULT_CAPACITY];
    for(int i = 0; i <DEFAULT_CAPACITY; i++)
    {
        table[i] = nullptr;
    }
    start = nullptr;
    prev = nullptr;
    cap = DEFAULT_CAPACITY;
    hash_size= 0;
}


template <typename T>
HashSet<T>::~HashSet()
{
destory(table, cap);

}

template <typename T>
void HashSet<T>::destory(Node** Dying_Table, int space)
{
for(int i = 0; i <space; i++)
{
    Node* temp = Dying_Table[i];
    while(temp!=nullptr)
    {
        Node* temp2 = temp;
        temp = temp->next;
        delete temp2;
    }
}
delete[] Dying_Table;
}

template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction}
{
    table = new Node* [DEFAULT_CAPACITY];
    for(int i = 0; i <DEFAULT_CAPACITY; i++)
    {
        table[i] = nullptr;
    }
    start = nullptr;
    prev = nullptr;
    cap = DEFAULT_CAPACITY;
    hash_size= 0;
    copy(s );





}
template <typename T>
void HashSet<T>::copy(const HashSet& s) 
{
   int old = s.cap;

    Node** their_table = s.table;

    for(int i = 0; i< old ; i++)
    {
        if(their_table[i] != nullptr)
        {
            Node* temp1;
                
            Node* temp2 = their_table[i];

            while(temp2 != nullptr)
            {    
                add(temp2->key);

                temp1= temp2;

                temp2 = temp2->next;

            }
       
        }
    }



}

template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
    destory(table, cap);

    hashFunction = s.hashFunction;

    table = new Node* [DEFAULT_CAPACITY];
    for(int i = 0; i <DEFAULT_CAPACITY; i++)
    {
        table[i] = nullptr;
    }
    start = nullptr;
    prev = nullptr;
    cap = DEFAULT_CAPACITY;
    hash_size= 0;
    copy(s);

    }

    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{

int value = hashFunction(element) % cap;
start = table[value];
prev = nullptr;
while(start != nullptr)
{

    prev = start;
    start= start ->next;
}

if(start == nullptr)
{

    start = new Node;
    start->key= element;
    start->next=nullptr;
    
        if(prev == nullptr)
        {

            table[value] = start;
        }
        else
        {

            prev->next=start;
        }
    
}
else
{
    start->key = element;
}

hash_size++;

if(hash_size==((cap*.8)+cap))
{
    resize();
}

}



template <typename T>
void HashSet<T>::resize()
{

    int old_cap = cap;
    cap = cap*2;
    Node** old_table = table;
    table = new Node*[cap];
    hash_size = 0;
    for(int i = 0; i <cap;i++)
    {
        table[i]=nullptr;
    }
    for(int i = 0; i< old_cap ; i++)
    {
        if(old_table[i] != nullptr)
        {

            Node* s_temp = old_table[i];

            while(s_temp != nullptr)
            {    
                add(s_temp->key);
                s_temp = s_temp->next;

            }
       
        }
    }

destory(old_table, old_cap);
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{

int value = hashFunction(element) % cap;

Node* search = table[value];


while(search != nullptr)
{   
    if(search->key == element)
    { 
        return true;   
    }
search = search->next;
}

    return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    return hash_size;
}



#endif // HASHSET_HPP

