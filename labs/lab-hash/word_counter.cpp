/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */
#include <map>
using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    vector<pair<string, int>> ret;

    std::map<string, int> wordsD;
    std::map<string, int>::iterator it;

    while (infile.good()){
        string word = infile.getNextWord();
	wordsD[word] += 1;
    }

    for (it = wordsD.begin(); it != wordsD.end(); it++){
        if (it->second >= threshold)
            ret.push_back(*it);
    }

    return ret;
}
