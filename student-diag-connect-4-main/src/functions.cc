#include "functions.hpp"

#include <iostream>
#include <vector>

using namespace std;

// REQUIRES: board is a rectangle and only has the characters, '-', 'X', and
// 'O'. player_char is either 'X' or 'O'.
// MODIFIES:
// EFFECTS: Returns true if there are 4 player_char characters in a diagonal on
// the board.

bool CheckDiagonal(const vector<vector<char>>& board, char player_char) {

  int count = 0;

   //left diagonal 
  for (int i = 0; i < board.size(); i++){ //assume board is always square
    if (board[i][i] == player_char) {  //this auto-checks for dashes as well
      count++; 
    } else {
      count = 0;  //reset every time 
    }
    if (count == 4){  //we found a diagonal 
      return true; 
    }
    cout << i << ", " << i << endl;
  }
  
  //count = 0;

  //right diagonal, from (max, max) to (max - 4, max - 4)
  int index = 0; 
  for (int i = board.size()-1; i >= 0; i--){
    if (board[i][index] == player_char) {
      count++; 
    } else {
      count = 0;  //reset every time 
    }
    if (count == 4){  //we found a diagonal 
      return true; 
    }
    index++;
    cout << index << ", " << i << endl;
  }

  /*
      0    1    2    3
  0 {'-', '-', '-', 'X'},
  1 {'-', '-', 'X', 'O'},
  2 {'-', 'X', 'O', 'O'},
  3 {'X', 'O', 'O', 'O'};
  */

  return false;  
}



  //int row = board.size();  //convert from vector to int
  //int col = board[0].size(); //convert from char to int

  //left diagonals
  /*
  for(int i = 0; i <= board.size() - 4 ; i++){
    for(int j = 0; j <= board[i].size() - 4; j++){
      if (board.at(i).at(j) != '-' &&    // check for dashes  
      board[i][j] == board[i + 1][j + 1] &&
      board[i][j] == board[i + 2][j + 2] &&
      board[i][j] == board[i + 3][j + 3] && 
      board[i][j] == player_char) {
        return true; 
      }
    }
  }
  
  */


 /*
  //right diagonals, from (max, max) to (max - 4, max - 4)
  for(int i = board.size() - 1; i >= 4; i--){
    for(int j = board[i].size() - 1; j >= 4; j--){
      if (board[i][j] != '-' &&    // check for dashes  
      board[i][j] == board[i - 1][j + 1] &&
      board[i][j] == board[i - 2][j + 2] &&
      board[i][j] == board[i - 3][j + 3] && 
      board[i][j] == player_char) {
        return true; 
      }
    }
  }
  */