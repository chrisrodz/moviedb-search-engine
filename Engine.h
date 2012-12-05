/* Christian A. Rodriguez
CCOM 3034 Data Structures
Engine file declarations for final project
*/

#ifndef ENGINE_H
#define ENGINE_H

#include "ParsedFile.h"
#include <tr1/unordered_map>
#include <string>
#include <tr1/unordered_set>

class Engine {
private:
    
    // Frequency table for all words
    std::tr1::unordered_map<string, std::tr1::unordered_map<string, unsigned int> > freqTable ; 
    
    // Map to all stopwords
    std::tr1::unordered_set<string> stops ;

public:

    Engine() ;
    /*----------------------------------------------------------------------
      Construct the Engine object.

      Precondition:  None
      Postcondition: The Engine is created and the stopwords map is created.
    -----------------------------------------------------------------------*/
    
    void index(string dir) ;
    /*----------------------------------------------------------------------
      Indexing of the complete search engine

      Precondition:  None
      Postcondition: Indexes all of the movies, words per movie, and
          calculates the frequency of all words.
    -----------------------------------------------------------------------*/

    void displayMulti(std::tr1::unordered_map<string, unsigned int> table) ;
    /*----------------------------------------------------------------------
      Finds the movies with top three frequencies in a map and displays them

      Precondition:  The map is not empty
      Postcondition: The movies with top three frequencies in the map are
          displayed.
    -----------------------------------------------------------------------*/

    void singleSearch(vector<string> word) ;
    /*----------------------------------------------------------------------
      Word search for single words.

      Precondition:  The word exists in the frequency table
      Postcondition: Uses displayMulti to display the three with highest
          frequencies.
    -----------------------------------------------------------------------*/
    
    void multiSearch(vector<string> words) ;
    /*----------------------------------------------------------------------
      Word search for multiple words.

      Precondition:  Both words are in the frequency table
      Postcondition: Finds the movies that have both words in them and uses
          displayMulti to display the three with highest frequencies.
    -----------------------------------------------------------------------*/

};

string clean(string word) ;
    /*----------------------------------------------------------------------
      Cleans a word of all non-alphabetical symbols

      Precondition:  None
      Postcondition: Returns the same string without non-alphabetical
          symbols.
    -----------------------------------------------------------------------*/

#endif