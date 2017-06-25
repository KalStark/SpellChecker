// BSTSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP
#include <iostream>
#include "Set.hpp"



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();


    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);



    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
        struct Node
    {
        T key;
        Node* left;
        Node* right;

    };
    void help_add(Node* next, const T& element);
    void deleteall(Node* all);
    void copy(Node* s, Node*& root);
    int bst_size;



    Node* root;


};


template <typename T>
BSTSet<T>::BSTSet()
{
root = nullptr;
bst_size = 0;
}

template <typename T>
BSTSet<T>::~BSTSet()
{



    deleteall(root);

}
template <typename T>
void BSTSet<T>::deleteall(Node* all)
{

        if(all == nullptr)
    { 
        return;
    }

    deleteall(all->left);



    deleteall(all->right);
        delete all;


}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
{   
    root= nullptr;
    Node* curr = s.root;

    bst_size = 0;

    copy(curr, root);


}
template <typename T>
void BSTSet<T>::copy(Node* curr, Node* & root)
{
if(curr== nullptr)
{
return;
}
else
{    

    root = new Node;
    bst_size++;
    root->key = curr->key;
    root->left = nullptr;
    root->right= nullptr;
    copy(curr->left, root->left);

    copy(curr->right, root->right);

}

}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
    if (this != &s)
    {
        deleteall(root);
        root=nullptr;
        Node* curr = s.root;
        copy(curr);
    }

    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{


        if(root== nullptr)
        {
            root = new Node;
            bst_size++;
            root->key = element;
            root->left = nullptr;
            root->right= nullptr;
            return;
        }
    help_add(root, element);




}


template <typename T>
void BSTSet<T>::help_add(Node* next, const T& element)
{

      if(next->key > element)
            { 

        if(next->left== nullptr) 
        {
            next->left= new Node;
            Node* curr = next->left;
            curr-> key = element;

            bst_size++;
            curr->left = nullptr;
            curr->right= nullptr;
            return;
        }
                    help_add(next->left, element);



            }
            else
            {

        if(next->right== nullptr)
        {
            next->right= new Node;
            Node* curr = next->right;
            curr-> key = element;

            bst_size++;
            curr->left = nullptr;
            curr->right= nullptr;
            return;
        }

                    help_add(next->right, element);

            }
        


}




template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
    Node* curr = root;
    while( curr!= nullptr)
    {
        if(curr->key == element)
        {
            return true;
        }
        if(curr->key > element)
        {
            curr = curr->left;
        }
        else
        {
            curr= curr->right;
        }
    }
    return false;
}



template <typename T>
unsigned int BSTSet<T>::size() const
{ 
    return bst_size;
}




#endif // BSTSET_HPP

