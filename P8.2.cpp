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

using namespace std;

int main() {
    // 1. Load dictionary
    vector<string> dictionary;
    ifstream dictFile("C:\\Users\\james\\Downloads\\CSC 242\\P8.2\\dictionary.txt"); // Replace with your dictionary file path

    if (!dictFile.is_open()) {
        cerr << "Error opening dictionary file." << endl;
        return 1;
    }

    string word;
    while (getline(dictFile, word)) {
        dictionary.push_back(word);
    }
    dictFile.close();

    // 2. Open the file to be checked
    ifstream textFile("C:\\Users\\james\\Downloads\\CSC 242\\P8.2\\mispelled.txt"); // Replace with your text file path you wish to check for spelling mistakes
    if (!textFile.is_open()) {
        cerr << "Error opening text file." << endl;
        return 1;
    }

    // 3. Check each word
    while (textFile >> word) {
        // Convert word to lowercase for case-insensitive comparison
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (find(dictionary.begin(), dictionary.end(), word) == dictionary.end()) {
            cout << "Misspelled word: " << word << endl;
        }
    }

    textFile.close();

    return 0;
}