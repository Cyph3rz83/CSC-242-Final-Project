/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 	CSC 242
** Assignment: 	Final Project P8.2
** File: 	Group4.cpp
** Description: This is the solution to first part of final project.
**
** Author: 	Group 4
** Date: 	23 JUN 2025
** -------------------------------------------------------------------------*/
#include <iostream>          
#include <fstream>           
#include <string>           
#include <vector>           
#include <algorithm>        
#include <cctype>            


using namespace std;

// converts all letters to a lower case letter
string cleanWord( string word ) {
    string cleaned; // string that holds the clean version of the word
    for ( char c : word ) { 
        if ( isalpha( c ) || c == '\'' ) { // keep alpahbet letters
            cleaned += tolower( c ); // convert to the clean word
        }
    }
    return cleaned; 
}

// This function compares two words and returns how many characters are different
int editDistance( const string& a , const string& b ) {
    int len = min( a.length() , b.length() ); 
    int distance = 0; 

    for ( int i = 0; i < len; i++ ) { // compare every character
        if ( a[i] != b[i] ) distance++; // if char dont match increase distance
    }

    distance += abs( ( int ) a.length() - ( int ) b.length() ); // add extra distance
    return distance; // difference
}

// this function suggests the closest word from the dictionary for a misspelled word
string suggestWord( const string& input , const vector<string>& dictionary ) {
    int minDistance = 2; // only a 2 char difference bettween words
    string bestMatch = ""; // where we store the closest match

    for ( const string& w : dictionary ) { // check each word in the dictionary
        int dist = editDistance( input , w ); 
        if ( dist < minDistance ) { // is the word closer than the prev one
            minDistance = dist;   // update 
            bestMatch = w;        // save this as the best match
        }
    }

    return bestMatch; // the best match(considering we dont know what the most appropriate word would be based on context and use case).
}

int main() {
    vector<string> dictionary; // dictionary word vector
    string word; 

    // dictionary path
    string dictPath = R"(dictionary.txt)";
    ifstream dictFile( dictPath ); // open directory

    if ( !dictFile.is_open() ) { // pretty self-explanatory
        cerr << "Error opening dictionary file." << endl;
        return 1; 
    }

    
    while ( getline( dictFile , word ) ) {
        transform( word.begin() , word.end() , word.begin() , ::tolower ); // convert to lowercase
        dictionary.push_back( word ); // add to the dictionary
    }

    dictFile.close(); 

    // file we want to spell check
    string inputPath = R"(mispelled.txt)";
    ifstream textFile( inputPath ); // Open the input file

    if ( !textFile.is_open() ) { 
        cerr << "Error opening text file." << endl;
        return 1; 
    }

    // Go through each word in the input file
    while ( textFile >> word ) {
        string cleaned = cleanWord( word ); // make lowercase
        if ( cleaned.empty() ) continue; 

        // Check if the word is in the dictionary
        auto it = find( dictionary.begin() , dictionary.end() , cleaned );

        if ( it == dictionary.end() ) { // If the word is not found
            string suggestion = suggestWord( cleaned , dictionary ); // Try to suggest a similar word
            if ( !suggestion.empty() ) { // if there is a suggestion show it
                cout << "Misspelled word: " << cleaned
                    << "Did you mean: " << suggestion << "?" << endl;
            }
            else {
                // or just show the word is miss-spelled
                cout << "Misspelled word: " << cleaned << endl;
            }
        }
    }

    textFile.close(); 
    return 0; 
}

