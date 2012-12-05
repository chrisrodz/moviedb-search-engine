/* Christian A. Rodriguez
CCOM 3034 Data Structures
Client file for final project
*/

#include "Engine.h"


string toLower(string word) ;
    /*----------------------------------------------------------------------
      Convert a string to all lower cases.

      Precondition:  None
      Postcondition: The string's content is converted to lower case.
    -----------------------------------------------------------------------*/
    
void beginSearch(Engine movies) ;
    /*----------------------------------------------------------------------
      Starts the loop for searching in the engine and will continue until the
      user indicates otherwise.

      Precondition:  None
      Postcondition: The user is prompted to write the words to be searched
          until he is done.
    -----------------------------------------------------------------------*/

int main()
{   
    cout << "Welcome to the movie search engine!\n"
         << "Please wait while the engine loads...\n" ;
         
    Engine movies ;
    movies.index("./moviesdb/") ;
    
    cout << "Loading is complete." << endl << endl ;
    
    beginSearch(movies) ;
    
    cout << "Thank you for using my search engine!" << endl << endl ;
    return 0 ;

}

// Implementation of toLower()
string toLower(string word) {
    string converted = "" ;
    for(int i = 0 ; i < word.length() ; i++)
        converted += tolower(word[i]) ;
    return converted ;
}

void beginSearch(Engine movies) {
    vector<string> wordForSearch = vector<string>() ;
    string word ;
    char choice ;
    int qty ;
    
    do{
        cout << "Would you like to search for 1 or 2 words? " ;
        cin >> qty ;
        
        if(qty == 1) {
            cout << "Enter the word: " ;
            cin >> word ;
            cout << endl ;
            wordForSearch.push_back(toLower(word)) ;
            movies.singleSearch(wordForSearch);
        }
        else if(qty == 2){
            cout << "\nPlease tell me the words you want to search for: " << endl ;
        	for (int i = 0 ; i < 2 ; i++) {
            	cout << i+1 << ": " ;
            	cin >> word ;
            	wordForSearch.push_back(toLower(word)) ;
        	}
        	movies.multiSearch(wordForSearch) ;
        }
        wordForSearch.clear();
        cout << "Do you wish to go again?(y/n) " ;
        cin >> choice ;
    }while(tolower(choice) != 'n');
}