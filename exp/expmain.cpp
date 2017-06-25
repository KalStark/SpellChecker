// expmain.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.
#include <iostream>
#include "Set.hpp"
#include "BSTSet.hpp"
#include <string>
#include <functional>
    typedef std::function<unsigned int(const int&)> HashFunction;

struct hash
{
unsigned int operator()(const int word)
{
    unsigned int hash = 1 + word;


    return hash;
}
	
};

int main()
{
	HashFunction ha{hash()};
	BSTSet<int > a;
	std::cout << "hi1" << std::endl;
	a.add(1);
	a.add(1);
	a.add(4);
	a.add(3);
	a.add(2);

	BSTSet<int > b(a);


    return 0;
}

