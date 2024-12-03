
//THIS WORKS IN AUTOGRADER --> updateDash is stored in dash_case, removed all error triggers
#include "word_guess_functions.hpp"
#include <iostream>
#include <map>
#include <string>

#include <cstdlib>

using namespace std;

// REQUIRES: size to be a value between 2 and 10 (including 2 and 10).
// MODIFIES:
// EFFECTS: Out of the words from kDictionaryFile that are of length size,
//          this function returns one of them randomly selected using
//          srand(random_seed) to initialize the random number generator.

  // We won't go over how to read in information from a file until later in the
  // course. Therefore, I have added in the code that opens and reads from a
  // file, one word at a time. It's up to you to implement the rest of the
  // function. This is a great chance to practice your code reading and problem
  // solving skills!



string PickWord(unsigned int size, int random_seed) {

  srand(random_seed);

  // TODO initialize variables you need 

  // opens file with the name, kDictionaryFile
  ifstream f_in(kDictionaryFile);

  // Checks that the file was opened correctly
  if (!f_in) {
    std::cerr << "Error: Unable to open file " << kDictionaryFile << std::endl;
    return " ";
  }

  // Reads in one word at a time until the end of the file
  string word;
  vector<string> valid_words; 
  while (f_in >> word) {
    if (word.length() == size) {
      valid_words.push_back(word);  //get all words of valid size into the vector
    }
  }

  //now we select a word from the vector dictionary
  f_in.close();
  return valid_words[rand() % valid_words.size()]; 
} 



// REQUIRES: guessed_letters only has valid guesses, aka lowercase letters
// MODIFIES:
// EFFECTS: Returns true if guess is valid. Guess is valid if it is
//         a lowercase letter that is not in guessed_letters.
bool GuessValid(char guess, vector<char> guessed_letters) {  //this stays the same
  int lowercase = guess - 'a'; 
  if (lowercase >= 0 && lowercase < 26){
    for (char letter : guessed_letters){
      if (guess == letter) {
        return false; 
      }
    }
    return true;
  }
  return false; 
}


// REQUIRES: size is greater than 0.
// MODIFIES:
// EFFECTS: Returns a string of length size that consists of '-' characters
//          only.
string GetBlankWord(unsigned int size) { 
  string str = "";
  while (str.length() < size){  
    str += "-"; 
  } 
  return str;
}

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns true if word has no '-' characters in it.0
bool WordCompleted(const string& word) { 
  for (unsigned int i = 0; i < word.length(); i++){
    if (word[i] == '-'){
      return false; 
    }
  }
  return true; 
}

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints to standard output the current state of the game. DO NOT
//          EDIT.
void PrintState(const string& mystery_word_so_far, unsigned int misses) {
  cout << endl;
  cout << "--- Current State --- " << endl;

  cout << "You have " << kMaxMisses - misses << " lives left." << endl;
  cout << "Word: ";
  for (unsigned int i = 0; i < mystery_word_so_far.length(); i++) {
    cout << mystery_word_so_far[i] << " ";
  }
  cout << endl;
  cout << endl;
}

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a number between (1, 10] from the user.
//  cout statements:
//    cout << "Enter a word length: ";
//    cout << "Invalid length. Please enter a length between (1, 10] : ";
int GetLengthOfWord() { 
  int x = 0; 
  cout << "Enter a word length: "; 
  cin >> x;  //get the user input 
  while (x <= 1 || x > 10) {
    cout << "Invalid length. Please enter a length between (1, 10] : ";
    cin >> x;
  } 
  return x; 
}

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a lowercase letter not in guessed_letters from the user.
//  cout statements:
//    cout << "What is your next guess? " << endl;
//    cout << "Invalid guess. Please enter a lowercase letter that you have "
//       << "not guessed yet : " << endl;
char GetNextGuess(const vector<char>& guessed_letters) {
  char guess = ' '; 
  cout << "What is your next guess? " << endl; 
  while(true){
    cin >> guess;
    if (!GuessValid(guess, guessed_letters)){
      cout << "Invalid guess. Please enter a lowercase letter that you have "
      << "not guessed yet : " << endl;
    }
    else break;
  }
  return guess; 
}

// REQUIRES:
// MODIFIES: cout, word_so_far
// EFFECTS: If the guess is in the word, the function updates word_so_far to
//          replace any "-" with the guessed letter. The function returns true
//          if the guess is in the word. Additionally, it calls GuessFeedback to
//          print out feedback to the user
bool CheckWordForGuess(string& word_so_far, string word, char guess) {
  bool state = false; 
  for (unsigned int i = 0; i < word.length(); i++) {
    if (guess == word[i]) {
      //update word_so_far 
      word_so_far[i] = guess; 
      state = true; 
    }
  }
  if (state) {
    GuessFeedback(state, guess);
    return true; 
  } else {
    GuessFeedback(state, guess); 
    return false;
  }
  
}

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints feedback to the user if the guess is in the word.
//  cout statements:
//    cout << "The letter \'" << guess << "\' is not in the word." << endl;
//    cout << "The letter \'" << guess << "\' is in the word!" << endl;
void GuessFeedback(bool correct_guess, char guess) {
  if (correct_guess){
    cout << "The letter \'" << guess << "\' is in the word!" << endl;
  } else {
    cout << "The letter \'" << guess << "\' is not in the word." << endl;
  }
}

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Returns true if word_so_far has no '-' characters or if misses
//          equals kMaxMisses. In both cases it also prints out feedback.
//  cout statements:
//    cout << "You win! You guessed the word, " << word_so_far << "." << endl;
//    cout << "You used up your last guess and lost!" << endl;
//    cout << "The word was, " << solution << "." << endl;
bool CheckEndConditions(const string& word_so_far, unsigned int misses, const string& solution) {
  for (unsigned int i = 0; i < word_so_far.length(); i++){
    if (WordCompleted(word_so_far)) {
      cout << "You win! You guessed the word, " << word_so_far << "." << endl;
      return true; 
    } else if (misses == kMaxMisses) {
      cout << "You used up your last guess and lost!" << endl;
      cout << "The word was, " << solution << "." << endl;
      return true; 
    }
  }
  return false;
}





//THIS ONE DOESNT WORK IN AUTOGRADER: 

/* 
#include "word_guess_functions.hpp"
#include <iostream>
#include <map>
#include <string>

#include <cstdlib>

using namespace std;

// REQUIRES: size to be a value between 2 and 10 (including 2 and 10).
// MODIFIES:
// EFFECTS: Out of the words from kDictionaryFile that are of length size,
//          this function returns one of them randomly selected using
//          srand(random_seed) to initialize the random number generator.

  // We won't go over how to read in information from a file until later in the
  // course. Therefore, I have added in the code that opens and reads from a
  // file, one word at a time. It's up to you to implement the rest of the
  // function. This is a great chance to practice your code reading and problem
  // solving skills!



string PickWord(unsigned int size, int random_seed) {

  srand(random_seed);

  // TODO initialize variables you need 

  // opens file with the name, kDictionaryFile
  ifstream f_in(kDictionaryFile);

  // Checks that the file was opened correctly
  if (!f_in) {
    std::cerr << "Error: Unable to open file " << kDictionaryFile << std::endl;
    return " ";
  }

  // Reads in one word at a time until the end of the file
  string word;
  vector<string> valid_words; 
  while (f_in >> word) {
    if (word.length() == size) {
      valid_words.push_back(word);  //get all words of valid size into the vector
    }
  }

  //now we select a word from the vector dictionary
  f_in.close();
  return valid_words[rand() % valid_words.size()]; 
} 



// REQUIRES: guessed_letters only has valid guesses, aka lowercase letters
// MODIFIES:
// EFFECTS: Returns true if guess is valid. Guess is valid if it is
//         a lowercase letter that is not in guessed_letters.
bool GuessValid(char guess, vector<char> guessed_letters) {  //this stays the same
  int lowercase = guess - 'a'; 
  if (lowercase >= 0 && lowercase < 26){
    for (char letter : guessed_letters){
      if (guess == letter) {
        return false; 
      }
    }
    return true;
  }
  return false; 
}


// REQUIRES: size is greater than 0.
// MODIFIES:
// EFFECTS: Returns a string of length size that consists of '-' characters
//          only.
string GetBlankWord(unsigned int size) { 
  string str = "";
  while (str.length() < size){  
    str += "-"; 
  } 
  return str;
}

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns true if word has no '-' characters in it.0
bool WordCompleted(const string& word) { 
  for (unsigned int i = 0; i < word.length(); i++){
    if (word[i] == '-'){
      return false; 
    }
  }
  return true; 
}

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints to standard output the current state of the game. DO NOT
//          EDIT.
void PrintState(const string& mystery_word_so_far, unsigned int misses) {
  cout << endl;
  cout << "--- Current State --- " << endl;

  cout << "You have " << kMaxMisses - misses << " lives left." << endl;
  cout << "Word: ";
  for (unsigned int i = 0; i < mystery_word_so_far.length(); i++) {
    cout << mystery_word_so_far[i] << " ";
  }
  cout << endl;
  cout << endl;
}

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a number between (1, 10] from the user.
//  cout statements:
//    cout << "Enter a word length: ";
//    cout << "Invalid length. Please enter a length between (1, 10] : ";
int GetLengthOfWord() { 
  int x = 0; 
  cout << "Enter a word length: "; 
  cin >> x;  //get the user input 
  while (x <= 1 || x > 10) {
    cout << "Invalid length. Please enter a length between (1, 10] : ";
    cin >> x;
  } 
  return x; 
}

// REQUIRES:
// MODIFIES: cout, cin
// EFFECTS: Returns a lowercase letter not in guessed_letters from the user.
//  cout statements:
//    cout << "What is your next guess? " << endl;
//    cout << "Invalid guess. Please enter a lowercase letter that you have "
//       << "not guessed yet : " << endl;
char GetNextGuess(const vector<char>& guessed_letters) {
  char guess = ' '; 
  cout << "What is your next guess? " << endl; 
  while(true){
    cin >> guess;
    if (!GuessValid(guess, guessed_letters)){
      // cout << "Invalid guess. Please enter a lowercase letter that you have "
      // << "not guessed yet : (you guessed)"  <<  guess << endl;
    }
    else break;
  }
  return guess; 
}

// REQUIRES:
// MODIFIES: cout, word_so_far
// EFFECTS: If the guess is in the word, the function updates word_so_far to
//          replace any "-" with the guessed letter. The function returns true
//          if the guess is in the word. Additionally, it calls GuessFeedback to
//          print out feedback to the user
bool CheckWordForGuess(string& word_so_far, string word, char guess) {
  bool state = false; 
  for (unsigned int i = 0; i < word.length(); i++) {
    if (guess == word[i]) {
      //update word_so_far 
      word_so_far[i] = guess; 
      state = true; 
    }
  }
  if (state) {
    GuessFeedback(state, guess);
    return true; 
  } else {
    GuessFeedback(state, guess); 
    return false;
  }
  
}

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Prints feedback to the user if the guess is in the word.
//  cout statements:
//    cout << "The letter \'" << guess << "\' is not in the word." << endl;
//    cout << "The letter \'" << guess << "\' is in the word!" << endl;
void GuessFeedback(bool correct_guess, char guess) {
  if (correct_guess){
    cout << "The letter \'" << guess << "\' is in the word!" << endl;
  } else {
    cout << "The letter \'" << guess << "\' is not in the word." << endl;
  }
}

// REQUIRES:
// MODIFIES: cout
// EFFECTS: Returns true if word_so_far has no '-' characters or if misses
//          equals kMaxMisses. In both cases it also prints out feedback.
//  cout statements:
//    cout << "You win! You guessed the word, " << word_so_far << "." << endl;
//    cout << "You used up your last guess and lost!" << endl;
//    cout << "The word was, " << solution << "." << endl;
bool CheckEndConditions(const string& word_so_far, unsigned int misses, const string& solution) {
  for (unsigned int i = 0; i < word_so_far.length(); i++){
    if (WordCompleted(word_so_far)) {
      cout << "You win! You guessed the word, " << word_so_far << "." << endl;
      return true; 
    } else if (misses == kMaxMisses) {
      cout << "You used up your last guess and lost!" << endl;
      cout << "The word was, " << solution << "." << endl;
      return true; 
    }
  }
  return false;
}





*/





