#include "word_guess_functions.hpp"
#include <map>
#include <string>

using namespace std;

// Write your driver for part 1 here

int main() {

    //figure out the modes 
    /*
  
    cout << "Hi! Regular or evil mode?" << endl;
    string answer;
    cin >> answer;
      */

    unsigned int x = GetLengthOfWord(); //get the length of the word from the user 
    string comp_word = PickWord(x, kRandomSeed); //select a random word of the given length

    string guess = GetBlankWord(x); 

    unsigned int misses = 0; 
    vector<char> guessed_letters; 

    while (true) {
        //print the state:
        PrintState(guess, misses); 
        if (CheckEndConditions(guess, misses, comp_word)) {
            break; 
        }
        //get a new guess from the user, update everything based on the guess
        char letter_guess = GetNextGuess(guessed_letters);   
        guessed_letters.push_back(letter_guess);  

        if (!CheckWordForGuess(guess, comp_word, letter_guess)) { //check if game has ended
            misses++; 
        }   
    }   
     
    return 1; 
}

