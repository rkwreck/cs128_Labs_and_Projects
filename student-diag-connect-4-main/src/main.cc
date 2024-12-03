#include <iostream>

#include "functions.hpp"

using namespace std;

int main() {
  vector<vector<char>> board_test = {{'-', '-', '-', 'X'},
                                     {'-', '-', 'X', 'O'},
                                     {'-', 'X', 'O', 'O'},
                                     {'X', 'O', 'O', 'O'}};

  cout << CheckDiagonal(board_test, 'X') << endl;
  cout << CheckDiagonal(board_test, 'O') << endl;

  return 0;
}