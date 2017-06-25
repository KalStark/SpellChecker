// AVLSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
            struct Node
    {
        T key;
        int height;
        Node* left;
        Node* right;
    };
    Node* help_add(Node* next, const T& element);
    void deleteall(Node* all);
    void new_height(Node* next);
    int get_height(Node* next);
    int balance(Node* next);
    int get_max(Node* next);   
    Node* rotate_left(Node* next);
    Node* rotate_right(Node* next); 
    void copy(Node* s, Node*& root);

    int avl_size;
    Node* root;

};




template <typename T>
AVLSet<T>::AVLSet()
{
    root = nullptr;
    avl_size=0;
}


template <typename T>
AVLSet<T>::~AVLSet()
{   

    deleteall(root);
}
template <typename T>
void AVLSet<T>::deleteall(Node* all)
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
AVLSet<T>::AVLSet(const AVLSet& s)
{

    root= nullptr;
    Node* curr = s.root;

    avl_size = 0;


    copy(curr, root);




}
template <typename T>
void AVLSet<T>::copy(Node* curr, Node* & root)
{
if(curr==nullptr)
{
    return;
}
else
{  


            root = new Node;
            avl_size++;
            root->key = curr->key;
            root->height = curr->height;
            root->left = nullptr;
            root->right= nullptr;



        copy(curr->left, root->left);



        copy(curr->right, root->right);

}


}

template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
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
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
        if(root== nullptr) 
        {
            root = new Node;

            root->key = element;
            root->height = 0;
            root->left = nullptr;
            root->right= nullptr;
            avl_size++;
            return;
        }

 
   root = help_add(root, element);


}


template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::help_add(Node* next, const T& element)
{
int bal;
 

      if(next->key > element)
        { 
        if(next->left== nullptr) 
        {
            next->left= new Node;
            Node* curr = next->left;
            curr-> key = element;
            curr->height = 0;
            avl_size++;
  

            curr->left = nullptr;
            curr->right= nullptr;

            new_height(next);


            return next;
        }

                    next->left = help_add(next->left, element);





            }
            else
            {

        if(next->right== nullptr)
        {
            next->right= new Node;
            Node* curr = next->right;
            curr-> key = element;
            curr->height = 0;
            avl_size++;


            curr->left = nullptr;
            curr->right= nullptr;
            new_height(next);

            return next;
        }

                   next->right = help_add(next->right, element);


            }


            new_height(next);

            bal = balance(next);

            if(bal > 1)
            { 
                if(element < next->left->key)
                {

                    next = rotate_left(next);
                    return next;
                }
                else
                {

                Node* temp = next->left;
                next->left = rotate_right(temp);
                next = rotate_left(next);

                    return next;

                }
            }
            else if(bal <-1)
            {

                if(element < next->right->key)
                {

                    Node* temp = next->right;
                    next->right = rotate_left(temp);

                   next = rotate_right(next);
                   return next;
                }
                else
                {

                    next = rotate_right(next);
                    return next;
                }
            }

            return next;


}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::rotate_right(Node* next)
{

Node* temp1 = next->right; //temp1 =A
Node* temp2 = temp1->left; //t1
next->right = temp2;
temp1->left = next;

new_height(next);
new_height(temp1);

return temp1;


     


}
template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::rotate_left(Node* next) 
{

Node* temp1 = next->left;
Node* temp2 = temp1->right;
next->left = temp2;

temp1->right = next;
new_height(next);
new_height(temp1);


return temp1;





 
}



template <typename T>
int AVLSet<T>::get_max(Node* next)
{
Node* left = next->left;
Node* right =  next->right;
int l_height=get_height(left);
int r_height=get_height(right);

return ((l_height> r_height) ? l_height :  r_height);
}

template <typename T>
void AVLSet<T>::new_height(Node* next)
{


    next->height = get_max(next)+1;
   

}

template <typename T>
int AVLSet<T>::get_height(Node* next)
{
    if(next == nullptr)
    {
        return -1;
    }
    else
    {
        return next->height;
    }
}
template <typename T>
int AVLSet<T>::balance(Node* next)
{


        return get_height(next->left) - get_height(next->right);


}





template <typename T>
bool AVLSet<T>::contains(const T& element) const
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
unsigned int AVLSet<T>::size() const
{

    return avl_size;
}




#endif // AVLSET_HPP

