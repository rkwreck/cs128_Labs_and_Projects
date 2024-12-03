#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <vector>

using namespace std;

// REQUIRES: board is a rectangle and only has the characters, '-', 'X', and
// 'O'. player_char is either 'X' or 'O'.
// MODIFIES:
// EFFECTS: Returns true if there are 4 player_char characters in a diagonal on
// the board.
bool CheckDiagonal(const vector<vector<char>>& board, char player_char);

#endif
