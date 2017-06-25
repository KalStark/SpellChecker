// WordChecker.cpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.
#include <iostream>
#include "WordChecker.hpp"
#include <algorithm>



WordChecker::WordChecker(const Set<std::string>& words) 
    : words{words}
{

}


bool WordChecker::wordExists(const std::string& word) const 
{
	if(words.contains(word)== true)
	{
		return true;

	}
	else
	{
    	return false;
	}
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{ 
    std::string temp = word;
    std::vector<std::string> True_List;

    for(char letter='A';  letter <= 'Z'; letter++)
   	 {	

		for(int i = 0; i < word.size(); i++ )
		{
		temp = InsertChar(word, letter, i);
		if(words.contains(temp) == true)
			{
				if(True_List.size() == 0)
					{
					True_List.push_back(temp);
					}
					else
					{
						if(True_List.back() != temp)
						{
							True_List.push_back(temp);
						}
					}

			}
		temp = ReplaceChar(word, letter, i);
		if(words.contains(temp) == true)
			{
				if(True_List.size() == 0)
					{
					True_List.push_back(temp);
					}
					else
					{
						if(True_List.back() != temp)
						{
							True_List.push_back(temp);
						}
					}

			}


		}

   	 }
   	 

   	 for(int j =0; j< word.size(); j++)
   	 {
   	 	temp = InsertSpace(word, j);
		if(words.contains(temp) == true)
			{
				if(True_List.size() == 0)
					{
					True_List.push_back(temp);
					}
					else
					{
						if(True_List.back() != temp)
						{
							True_List.push_back(temp);
						}
					}

			}
   	 
			temp =  EraseChar(word, j);
			  	if(words.contains(temp) == true)
				{
					if(True_List.size() == 0)
					{
					True_List.push_back(temp);
					}
					else
					{
						if(True_List.back() != temp)
						{
							True_List.push_back(temp);
						}
					}
				}
			
		if(j+1 < temp.size()) 
			{
			temp = SwapChar(word, j);
	    	if(words.contains(temp) == true)
				{
					True_List.push_back(temp);

				}
			}

   	 }


    return True_List;
}

std::string WordChecker::SwapChar(std::string word, int tracker) const
{
std::swap(word[tracker], word[tracker+1]);
return word;
}
std::string WordChecker::InsertChar(std::string word, char letter, int i) const
{

std::string New_Letter = std::string(1,letter);

word.insert(i, New_Letter);

return word;
}
std::string WordChecker::EraseChar(std::string word, int i) const
{
word.erase(i,1);

return word;
}
std::string WordChecker::ReplaceChar(std::string word, char letter, int i) const
{
std::string New_Letter = std::string(1,letter);
word.replace(i,1,New_Letter);

return word;
}

// fix this it causes duplicates
std::string WordChecker::InsertSpace(std::string word, int i) const
{

word.insert(i, " ");

return word;
}
