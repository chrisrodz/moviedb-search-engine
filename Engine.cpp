/* Christian A. Rodriguez
CCOM 3034 Data Structures
Engine class implementation for final project
*/

#include "Engine.h"
#include <ctype.h>

// Implementation of Engine()
Engine::Engine() {

    vector<string> stopWords = vector<string>(); // Empty vector to store stopwords
    ParsedFile stop("./stopwords.txt") ;         // Read stopwords from file
    stopWords = stop.readAndTokenize() ;         // Tokenize all stopwords
    
    // Associate stopwords to map
    for(int i = 0 ; i < stopWords.size() ; i++)
        stops.insert(stopWords[i]) ;
}

// Implementation of index()
void Engine::index(string dir) {

    vector<string> files = vector<string>();     // All files in dir
    vector<string> words = vector<string>();	 // All words in a specific file
    string curr ;								 // Specific word to be indexed

    getdir(dir,files);
    
    // Tokenize ALL of the words in all of the movies
    for(unsigned int i = 0 ; i < files.size() ; i++) {
        ParsedFile movie(dir + files[i]) ;
        
        // Get all words in the ith movie of the map
        words = movie.readAndTokenize() ;
        
        // Iterate through all words in the ith movie
        for(unsigned int j = 0 ; j < words.size() ; j++) {
            
            // Clean the current word
            curr = clean(words[j]) ;
            
            // If curr is not a stop word add it to the frequency table
            if(stops.find(curr) == stops.end())
                freqTable[curr][files[i]]++;
            
        }
    }
}

//Implementation of displayMulti()
void Engine::displayMulti(std::tr1::unordered_map<string, unsigned int> table) {

    // If the map is empty there is nothing to be done.
    if(table.empty()) {
        cout << "No movies matched your search. Sorry" << endl << endl ;
        return ;
    }
    
    std::tr1::unordered_map<string, unsigned int>::iterator it2 ;
    string big ;
    
    // Iterate three times to get the three movies with highest frequencies
    for(int i = 0 ; i < 3 ; i++) { 
    
    // If the intersection is empty the job is done
        if(table.size() == 0) {
            cout << "No more movies." << endl << endl ;
            return ;
        }
        
        // Assume the movie with highest frequency is the first one
        big = table.begin()->first ;
        
        // Iterate through the rest of the movies and if one with higher frequency
        // is found swap it with big
        for(it2 = table.begin() ; it2 != table.end() ; it2++)
            if(table[big] < it2->second)
                big = it2->first;
        
        // Print the movie with highest frequency
        cout << "Movie " << i+1 << ": " << big << endl ;
        
        // Erase that movie from the map
        table.erase(big) ;
    }
    cout << endl ;
}

// Implementation of singleSearch()
void Engine::singleSearch(vector<string> word) {
    
    // If the movie is not in the frequency table, then break
    if(freqTable.count(word[0]) == 0) {
        cout << word[0] << " is not in any movie. Sorry" << endl << endl ;
        return;
    }
    
    std::tr1::unordered_map<string, unsigned int>single = freqTable[word[0]];
    
    // Call displayMulti to finish the job!
    displayMulti(single) ;
}

// Implementation of multiSearch()
void Engine::multiSearch(vector<string> words) {
    
    if(freqTable.count(words[0]) == 0) {
        cout << words[0] << " is not in any movie. Sorry" << endl << endl ;
        return;
    }
    else if(freqTable.count(words[1]) == 0) {
        cout << words[1] << " is not in any movie. Sorry" << endl << endl ;
        return;
    }
    
    // Map for the movies in the intersection
    std::tr1::unordered_map<string, unsigned int>intersection;
    
    std::tr1::unordered_map<string, unsigned int>::iterator it1 ;
    
    // Iterate through all movies that contain both words and save the ones that
    // intersect with the sum of frequencies in the intersection map.
    for(it1 = freqTable[words[0]].begin() ; it1 != freqTable[words[0]].end() ; ++it1) {
        if(freqTable[words[1]].find(it1->first) != freqTable[words[1]].end())
            intersection[it1->first] = (it1->second)+(freqTable[words[1]][it1->first]) ;
    }
    
    // Call displayMulti to finish the job!
    displayMulti(intersection) ;
}

// Implementation of clean()
string clean(string word) {
    
    // Iterate through all the characters in the string
    for(int i = 0 ; i < word.size() ; i++) {
        
        // If it's an uppercase char convert to lower case
        word[i] = tolower(word[i]) ;
            
        // If it's a symbol erase it from the string	
        if(!islower(word[i]) && word.size() - i == 2) {
            word.erase(i) ;
            return word;
        }
        else if(!islower(word[i])) {
            word.erase(i,1) ;
            i-- ;
        }
    }
    // Return the cleaned word
    return word ;
}

