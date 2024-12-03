

//THIS WORKS IN AUTOGRADER --> updateDash is stored in dash_case, removed all error triggers

#include "word_guess_functions.hpp"
#include <map>
#include <string>
#include <vector> 
#include <cstring> 
#include <iostream> 

using namespace std;

string SelectMode(){
  //figure out the modes 
  cout << "Select a mode, neutral or evil : ";
  string answer;
  cin >> answer;

  while (answer != "neutral" && answer != "evil") {
    cout << "Invalid. Please pick neutral, or evil : ";
    cin >> answer;
  }
  
  return answer; 
}

// Write your driver for part 1 here

void RegularMode() {
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
  

}

//driver 2 

string updateDash(string dash_case, string word, char letter){
  for (unsigned int j = 0; j < word.size(); j++){
    if (letter == word[j]){
      //add the letter to the blank word
      dash_case[j] = letter; 
    }
  }
  return dash_case; 
}

//PICK THE INITIAL VECTOR OF WORDS WITH THE CORRECT LENGTH 
vector<string> FirstEvilVector(unsigned int size, int random_seed){
  
  srand(random_seed);

  // opens file with the name, kDictionaryFile
  ifstream f_in(kDictionaryFile);

  vector<string> valid_words;  //vector of words we will work with 
  // Checks that the file was opened correctly
  if (!f_in) {
    std::cerr << "Error: Unable to open file " << kDictionaryFile << std::endl;
    return valid_words;
  }

  // Reads in one word at a time until the end of the file
  string word; 
  while (f_in >> word) {
    if (word.length() == size) {
      valid_words.push_back(word);  //get all words of valid size into the vector
    }
  }

  return valid_words; 
}


// CREATE THE MAP WITH THE NEW FILTER 
vector<string> pickEvilGroup(vector<string> current_words, char letter, int size){

  map<string, vector<string>> filtered_map; 

    for (unsigned int i = 0; i < current_words.size(); i++){
    string word = current_words[i]; //pick a word from the vector

    string dash_case = GetBlankWord(size); //make a new case each time we iterate through the words

    dash_case = updateDash(dash_case, word, letter); 

    //now that we have finished making the case, see if it exists in the map
    filtered_map[dash_case].push_back(word); //word will become a vector, dash_case becomes a key if it doesn't already exist
    
    }

    //now we see which vector is largest --> that one is best potential group
    int x_length = 0; 
    vector<string> final_list; 
    for (const auto& key : filtered_map) {
        if (key.second.size() > x_length){
            x_length = key.second.size(); 
            final_list = key.second; 
        }
    }

    return final_list; 
} 


void EvilMode() {
    unsigned int x = GetLengthOfWord(); 
    //cout << "done get length of word" << endl;
    vector<string> word_group = FirstEvilVector(x, kRandomSeed); //vector based on the length
    //cout << "done first vector" << endl;
    string game_so_far = GetBlankWord(x); //return blank dashes of the word size
    //cout << "done get blank word" << endl;

    unsigned int misses = 0;   //var to count errors 
    vector<char> guessed_letters; 

    PrintState(game_so_far, misses);   //printing the lives left 

  while(!CheckEndConditions(game_so_far, misses, word_group[0]) && !word_group.empty()) {
    //cout << "in here" << endl; 
    char guess = GetNextGuess(guessed_letters);  //ask for the next guess
    //cout << "passed get next guess" << endl;
    guessed_letters.push_back(guess);

    word_group = pickEvilGroup(word_group, guess, x);

    if (!CheckWordForGuess(game_so_far, word_group[0], guess)){
      misses++;
    } else {
      game_so_far = updateDash(game_so_far, word_group[0], guess); 
    }

    PrintState(game_so_far, misses); 
    
  } 

}   


int main() {
    string mode = SelectMode(); 
    if (mode == "neutral"){
        RegularMode(); 
    } else {
        EvilMode(); 
    }

    return 1; 
}






//THIS ONE DOESNT WORK IN AUTOGRADER: 

/*
#include "word_guess_functions.hpp"
#include <map>
#include <string>
#include <vector> 
#include <cstring> 
#include <iostream> 

using namespace std;

string SelectMode(){
  //figure out the modes 
  cout << "Select a mode, neutral or evil : ";
  string answer;
  cin >> answer;

  while (answer != "neutral" && answer != "evil") {
    cout << "Invalid. Please pick neutral, or evil : ";
    cin >> answer;
  }
  
  return answer; 
}

// Write your driver for part 1 here

void RegularMode() {
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
  

}

//driver 2 

string updateDash(string dash_case, string word, char letter){
  for (unsigned int j = 0; j < word.size(); j++){
    if (letter == word[j]){
      //add the letter to the blank word
      dash_case[j] = letter; 
    }
  }
  return dash_case; 
}

//PICK THE INITIAL VECTOR OF WORDS WITH THE CORRECT LENGTH 
vector<string> FirstEvilVector(unsigned int size, int random_seed){
  
  srand(random_seed);

  // opens file with the name, kDictionaryFile
  ifstream f_in(kDictionaryFile);

  vector<string> valid_words;  //vector of words we will work with 
  // Checks that the file was opened correctly
  if (!f_in) {
    std::cerr << "Error: Unable to open file " << kDictionaryFile << std::endl;
    return valid_words;
  }

  // Reads in one word at a time until the end of the file
  string word; 
  while (f_in >> word) {
    if (word.length() == size) {
      valid_words.push_back(word);  //get all words of valid size into the vector
    }
  }

  return valid_words; 
}


// CREATE THE MAP WITH THE NEW FILTER 
vector<string> pickEvilGroup(vector<string> current_words, char letter, int size){

  map<string, vector<string>> filtered_map; 

    for (unsigned int i = 0; i < current_words.size(); i++){
    string word = current_words[i]; //pick a word from the vector

    string dash_case = GetBlankWord(size); //make a new case each time we iterate through the words

    dash_case = updateDash(dash_case, word, letter); 
    
    //now that we have finished making the case, see if it exists in the map
    filtered_map[dash_case].push_back(word); //word will become a vector, dash_case becomes a key if it doesn't already exist
    
    }

    //now we see which vector is largest --> that one is best potential group
    size_t x_length = 0; 
    vector<string> final_list; 
    for (const auto& key : filtered_map) {
        if (key.second.size() > x_length){
            x_length = key.second.size(); 
            final_list = key.second; 
        }
    }
    // for (string s : final_list) cout << s << " ";  cout << endl;
    return final_list; 
} 


void EvilMode() {
    unsigned int x = GetLengthOfWord(); 
    cout << "done get length of word" << endl;
    vector<string> word_group = FirstEvilVector(x, kRandomSeed); //vector based on the length
    cout << "done first vector" << endl;
    string game_so_far = GetBlankWord(x); //return blank dashes of the word size
    cout << "done get blank word" << endl;

    unsigned int misses = 0;   //var to count errors 
    vector<char> guessed_letters; 

    PrintState(game_so_far, misses);   //printing the lives left 

  while(!CheckEndConditions(game_so_far, misses, word_group[0]) && !word_group.empty()) {
    cout << "in here" << endl; 
    char guess = GetNextGuess(guessed_letters);  //ask for the next guess
    cout << "passed get next guess" << endl;
    guessed_letters.push_back(guess);

    word_group = pickEvilGroup(word_group, guess, x);

    if (!CheckWordForGuess(game_so_far, word_group[0], guess)){
      misses++;
    } else {
      game_so_far = updateDash(game_so_far, word_group[0], guess); 
    }

    PrintState(game_so_far, misses); 
    
  } 

/*

while (true){
        char guess = GetNextGuess(guessed_letters);  //ask for the next guess
        guessed_letters.push_back(guess);

        word_group = pickEvilGroup(word_group, guess, x); 

        if (!CheckWordForGuess(game_so_far, word_group[0], guess)){
            misses++;
        } else {
            game_so_far = updateDash(game_so_far, word_group[0], guess); 
        }

        PrintState(game_so_far, misses); 
    }


}   


int main() {
    string mode = SelectMode(); 
    if (mode == "neutral"){
        RegularMode(); 
    } else {
        EvilMode(); 
    }

    return 1; 
}




/*

//ADD include statements needed here

#include "word_guess_functions.hpp"

using namespace std;

// Write your driver for part 2 in this file. 

// Create and use your own functions in this file. 
// You do not want your main function over ~40 lines 
// of code to help with readability and reusability. 


// cout statements
// cout << "Select a mode, neutral or evil : ";
// cout << "Invalid. Please pick neutral, or evil : ";
string SelectMode() {}

int main() { string mode = SelectMode(); }

*/





