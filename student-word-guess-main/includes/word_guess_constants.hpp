#ifndef WORD_GUESS_CONSTANTS_HPP
#define WORD_GUESS_CONSTANTS_HPP
#include <string>

using namespace std;

// test cases given assume these values

const int kMaxMisses = 5;
const int kRandomSeed = 5500;
const int kMinWordLength = 2;   // inclusive
const int kMaxWordLength = 10;  // inclusive
const string kDictionaryFile = "includes/dictionary.txt";

#endif
