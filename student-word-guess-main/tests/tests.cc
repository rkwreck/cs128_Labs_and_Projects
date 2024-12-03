// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Jule Schatz                    Environment : ubuntu:bionic               //
//  Date ......: 2024/03/14                     Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>
#include <string>
#include <vector>

#include "word_guess_functions.hpp"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
// Public Test Cases //
///////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("PickWord Test", "[PickWord]") {
  string output = PickWord(5, 5301);
  REQUIRE(output.size() == 5);

  string output2 = PickWord(5, 514);
  REQUIRE(output != output2);
}

TEST_CASE("GuessValid Test", "[GuessValid]") {
  vector<char> guessed_letters = {'a', 'c', 'z'};
  REQUIRE(GuessValid('6', guessed_letters) == false);
  REQUIRE(GuessValid('a', guessed_letters) == false);
  REQUIRE(GuessValid('j', guessed_letters) == true);
}

TEST_CASE("GetBlankWord Test", "[GetBlankWord]") {
  string res1 = GetBlankWord(4);
  REQUIRE(res1.length() == 4);
  REQUIRE(res1[0] == '-');
  REQUIRE(res1[1] == '-');
  REQUIRE(res1[2] == '-');
  REQUIRE(res1[3] == '-');

  string res2 = GetBlankWord(1);
  REQUIRE(res2.length() == 1);
  REQUIRE(res2[0] == '-');
}

TEST_CASE("WordCompleted Test", "[WordCompleted]") {
  string word1 = "d";
  string word2 = "a-a-";
  string word3 = "----";
  string word4 = "adx";

  REQUIRE(WordCompleted(word1) == true);
  REQUIRE(WordCompleted(word2) == false);
  REQUIRE(WordCompleted(word3) == false);
  REQUIRE(WordCompleted(word4) == true);
}

TEST_CASE("PrintState Test", "[PrintState]") {
  cout << "Test PrintState on your own, this test passes no matter what."
       << endl;
  REQUIRE(true);
}

TEST_CASE("GetLengthOfWord Test", "[GetLengthOfWord]") {
  cout << "Test GetLengthOfWord on your own, this test passes no matter what."
       << endl;
  REQUIRE(true);
}

TEST_CASE("GetNextGuess Test", "[GetNextGuess]") {
  cout << "Test GetNextGuess on your own, this test passes no matter what."
       << endl;
  REQUIRE(true);
}

TEST_CASE("CheckWordForGuess Test", "[CheckWordForGuess]") {
  string word1 = "---a";
  string word2 = "a---";
  string word3 = "----";
  string word4 = "--a-";

  CheckWordForGuess(word1, "bcca", 'b');
  CheckWordForGuess(word2, "abcb", 'b');
  CheckWordForGuess(word3, "back", 'b');
  CheckWordForGuess(word4, "aaaa", 'b');

  REQUIRE(word1 == "b--a");
  REQUIRE(word2 == "ab-b");
  REQUIRE(word3 == "b---");
  REQUIRE(word4 == "--a-");
}

TEST_CASE("GuessFeedback Test", "[GuessFeedback]") {
  cout << "Test GuessFeedback on your own, this test passes no matter what."
       << endl;

  GuessFeedback(true, 'b');
  GuessFeedback(false, 'b');

  REQUIRE(true);
}

TEST_CASE("CheckEndConditions Test", "[CheckEndConditions]") {
  string word1 = "---a";
  string word2 = "aaa";
  string word3 = "b";
  string word4 = "---";

  REQUIRE(CheckEndConditions(word1, kMaxMisses, "solution"));
  REQUIRE(CheckEndConditions(word1, kMaxMisses - 1, "solution") == false);

  REQUIRE(CheckEndConditions(word2, kMaxMisses, "solution"));
  REQUIRE(CheckEndConditions(word2, kMaxMisses - 1, "solution"));

  REQUIRE(CheckEndConditions(word3, kMaxMisses, "solution"));
  REQUIRE(CheckEndConditions(word3, 0, "solution"));

  REQUIRE(CheckEndConditions(word4, kMaxMisses, "solution"));
  REQUIRE(CheckEndConditions(word4, 0, "solution") == false);
}
