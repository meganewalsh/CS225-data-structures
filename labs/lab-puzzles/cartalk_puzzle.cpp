/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d, const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    /* Your code goes here! */

    ifstream wordsFile(word_list_fname);
    string word;
    vector<string> five_letter_words;

    if (wordsFile.is_open()) {
    	while (getline(wordsFile, word)) {
	    if (word.length() == 5)
            	five_letter_words.push_back(word);
        }
    }

    for (size_t a = 0; a < five_letter_words.size(); a++){
	string Word = five_letter_words[a];
    	string sub1 = Word.substr(1);  			//remove first letter
    	string sub2 = Word[0] + sub1.substr(1);  	//remove second letter

	if (d.homophones(sub1, sub2)){
	    std::tuple<string, string, string> myTuple = std::make_tuple(Word, sub1, sub2);
	    ret.push_back(myTuple);
	}
    }

  return ret;
}



