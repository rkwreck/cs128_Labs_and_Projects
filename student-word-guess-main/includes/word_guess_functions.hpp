#ifndef WORD_GUESS_FUNCTIONS_HPP
#define WORD_GUESS_FUNCTIONS_HPP

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "word_guess_constants.hpp"

using namespace std;

// REQUIRES: size to be a value between 2 and 10 (including 2 and 10).
// MODIFIES:
// EFFECTS: Out of the words from kDictionaryFile that are of length size,
//          this function returns one of them randomly selected using
//          srand(random_seed) to initialize the random number generator.
string PickWord(unsigned int size, int random_seed);

// REQUIRES: guessed_letters only has valid guesses, aka lowercase letters
// MODIFIES:
// EFFECTS: Returns true if guess is valid. Guess is valid if it is
//          a lowercase letter that is not in guessed_letters.
bool GuessValid(char guess, vector<char> guessed_letters);

// REQUIRES: size is greater than 0.
// MODIFIES:
// EFFECTS: Returns a string of length size that consists of '-' characters
//          only.
string GetBlankWord(unsigned int size);

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns true if word has no '-' characters in it.
bool WordCompleted(const string& word);

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints to standard output the current state of the game. DO NOT
//          EDIT.
void PrintState(const string& mystery_word_so_far, unsigned int misses);

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a number between (1, 10] from the user.
//  cout statements:
//    cout << "Enter a word length: ";
//    cout << "Invalid length. Please enter a length between (1, 10] : ";
int GetLengthOfWord();

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a lowercase letter not in guessed_letters from the user.
//  cout statements:
//    cout << "What is your next guess? " << endl;
//    cout << "Invalid guess. Please enter a lowercase letter that you have "
//       << "not guessed yet : " << endl;
char GetNextGuess(const vector<char>& guessed_letters);

// REQUIRES:
// MODIFIES: cout, word_so_far
// EFFECTS: If the guess is in the word, the function updates word_so_far to
//          replace any "-" with the guessed letter. The function returns true
//          if the guess is in the word. Additionally, it calls GuessFeedback to
//          print out feedback to the user
bool CheckWordForGuess(string& word_so_far, string word, char guess);

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints feedback to the user if the guess is in the word.
//  cout statements:
//    cout << "The letter \'" << guess << "\' is not in the word." << endl;
//    cout << "The letter \'" << guess << "\' is in the word!" << endl;
void GuessFeedback(bool correct_guess, char guess);

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Returns true if word_so_far has no '-' characters or if misses
//          equals kMaxMisses. In both cases it also prints out feedback.
//  cout statements:
//    cout << "You win! You guessed the word, " << word_so_far << "." << endl;
//    cout << "You used up your last guess and lost!" << endl;
//    cout << "The word was, " << solution << "." << endl;
bool CheckEndConditions(const string& word_so_far,
                        unsigned int misses,
                        const string& solution);

#endif
