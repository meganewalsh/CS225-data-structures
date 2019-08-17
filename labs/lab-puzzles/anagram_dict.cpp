/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"
#include <iostream>
#include <algorithm> /* I wonder why this is included... */
#include <fstream>
using std::string;
using std::vector;
using std::ifstream;
using namespace std;
vector<string> findValue(string);
/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    vector<string> words;

    if (wordsFile.is_open()) {
    	while (getline(wordsFile, word)) {
        	words.push_back(word);
    	}
    }

    for (size_t a = 0; a < words.size(); a++){
	string word = words[a];
        std::sort(word.begin(), word.end());
        if (dict.find(word) == dict.end()){
	    vector<string> V;
	    V.push_back(words[a]);
            dict[word] = V;
	}
	else
	    (dict.find(word)->second).push_back(words[a]);
    }
}


vector<string> findValue(string word){

    string chars;
    vector<string> V;

    for (size_t a = 0; a < word.length(); a++){
       chars += word[a];
    }
    std::sort(chars.begin(), chars.end());
    V.push_back(chars);
    return V;
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (size_t a = 0; a < words.size(); a++){
	string word = words[a];
        std::sort(word.begin(), word.end());
        if (dict.find(word) == dict.end()){
	    vector<string> V;
	    V.push_back(words[a]);
            dict[word] = V;
	}
	else
	    (dict.find(word)->second).push_back(words[a]);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
     /* Your code goes here! */

  string w = word;
  std::sort(w.begin(), w.end());
  
  if (dict.find(w) != dict.end()){
      return dict.find(w)->second;	
  }

  return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;

    for (auto & it : dict){
        vector<string> anag = get_anagrams(it.first);
     
        if (anag.size() > 1)
          ret.push_back(anag);

    }

 return ret;
}


