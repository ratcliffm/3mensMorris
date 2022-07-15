/*! \file main.cpp
    \brief The main source file for lab 4 three men's morris.
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "brain.h"
#include "three_mens_morris.h"

using namespace std;

// create for loop for which phase
// if pieces < 3

int main() {
  // main input loop goes here.
  // sets up the board
  Board board(3, vector<int>(3, 0));
  Move ret;

  // GameOver(board);
  // begins the loop to ask for user input
  int game_over = 0;
  PrintBoard(board);

  while (!game_over) {

    // determine which phase we are in
    int gamePhase;
    int numCount = 0;
    for (unsigned int row = 0; row < board.size(); ++row) {
      for (unsigned int col = 0; col < board[row].size(); ++col) {
        if (board[row][col] == 2) {
          ++numCount;
        }
        if (numCount < 3) {
          gamePhase = 1;
        } else {
          gamePhase = 2;
        }
      }
    }

    // initialize invalid move for P1 so our loop will start
    BoardIndex b;
    b.first = -1;
    b.second = -1;
    ret.first = b;
    ret.second = b;

    // gets user move from parse space that returned a ret

    while (!ValidMove(gamePhase, 1, board, ret)) {
      string input;
      string gamePhaseStyle;
      if (gamePhase == 1) {
        gamePhaseStyle = "a1";
      }
      if (gamePhase == 2) {
        gamePhaseStyle = "a1b2";
      }
      cout << "You are currently in game phase " << gamePhase
           << ". Please enter your move in a " << gamePhaseStyle << " style"
           << endl;
      getline(cin, input);
      ret = ParseMove(gamePhase, input);
    }
    if (gamePhase == 2) {
      SetPlayerAtSpace(board, 0, ret.first);
    }
    SetPlayerAtSpace(board, 1, ret.second);
    cout << "Player 1 moved:" << endl; 
    PrintBoard(board);
    game_over = GameOver(board); 
    cout << "Waiting for player 2 move..." << endl; 
    // call for computer's move by initalizing as an invalid move then loop to
    // move
    BoardIndex OneIntPair;
    Move computerMove;
    OneIntPair.first = -1;
    OneIntPair.second = -1;
    computerMove.first = OneIntPair;
    computerMove.second = OneIntPair; 

    while (!ValidMove(gamePhase, 2, board, computerMove)) { 
     computerMove = GalaxyBrain(board);
     ValidMove(gamePhase, 2,board, computerMove);
    }
     SetPlayerAtSpace(board, 2, computerMove.second);
     if (gamePhase == 2) {
       SetPlayerAtSpace(board, 0, computerMove.first);}
  cout << "Player 2 moved:" << endl; 
  PrintBoard(board);
  game_over = GameOver(board); 
  }

  return 0;
}

/**
 * \brief Determines if the game is over.
 * \param board The current board state.
 * \return -1 if the game is not over, 0 if the game is a draw, 1 if player 1
 *         has won, 2 if player 2 has won.
 */
int GameOver(const Board board) {  
  // Determine winner, if any.
  for (unsigned int row = 0; row < board.size(); ++row) {
    for (unsigned int col = 0; col < board[row].size(); ++col) {
      if ((board[row][0] == 1) && (board[row][1] == 1) && board[row][2] == 1){
        cout << "Congratulations, you win!" << endl; 
        return 1;
      } else if ((board[0][col] == 1) && (board[1][col] == 1) && board[2][col] == 1){
        cout << "Congratulations, you win!" << endl; 
        return 1;
      } else if ((board[row][0] == 2) && (board[row][1] == 2) && board[row][2] == 2){
        cout << "Oh no, player 2 has won this round" << endl;
        return 2;
      } else if ((board[0][col] == 2) && (board[1][col] == 2) && board[2][col] == 2){
        cout << "Oh no, player 2 has won this round" << endl;
        return 2;
      } 
    }
  }
  return 0;
}

/**
 *  \brief Prints the board to standard error (cerr).
 *  \param board The current board state to be printed.
 */
void PrintBoard(Board board) {  
  for (unsigned int row = 0; row < board.size(); ++row) {
    for (unsigned int col = 0; col < board[row].size(); ++col) {
      cerr << board[row][col];
    }
    cerr << endl;
  }
}

/**
 * \brief Returns the player occupying the space.
 * \param space The BoardIndex of the space.
 * \return The integer representing the player at the space.
 *         0 for unoccupied. 1 for player 1. 2 for player 2.
 */
int PlayerAtSpace(const Board board,
                  const BoardIndex space) { 
  for (unsigned int row = 0; row < board.size(); ++row) {
    for (unsigned int col = 0; col < board[row].size(); ++col) {
      if (board[space.first][space.second] == 1) {
        return 1;
      }
      if (board[space.first][space.second] == 2) {
        return 2;
      }
    }
  }
  return 0;
}

/**
 * \brief Updates the board to put a player a particular space.
 * \param board The current board state. **This is a reference parameter**.
 *        Any modifications to the board in this function will be reflected
 *        outside the function.
 * \param player The player to move to the space.
 * \param space The space on the board to update.
 *
 * For example, if player 1 is moving to 0,0, this function toggles the
 * space at 0,0 from 0 to 1.
 * No error checking is done here. It is assumed that the move is valid.
 */
void SetPlayerAtSpace(Board &board, const int player, const BoardIndex space) {
  board[space.first][space.second] =
      player;  
}

/**
 * \brief Parses a user-supplied string into a Move type.
 * \param phase The phase of the game.
 * \param move The string supplied by the user.
 * \return A move type containing the row/column indices of the move.
 */
Move ParseMove(int phase, const string move) { 
  Move ret;
  if (phase == 1) {
    ret.first = ParseSpace("a0");
    ret.second = ParseSpace(move);
  }
  if (phase == 2) {
    string stringA = move.substr(0, 2);
    string stringB = move.substr(2, 2);
    ret.first = ParseSpace(stringA);
    ret.second = ParseSpace(stringB);
  }
  return ret;
}

/** ParseSpace
 *  \brief Parses a two-character string into a BoardIndex.
 *  \param space A string provided of the form "a1", "c3", etc.
 *
 *  This is the main function that turns user input into a pair of
 *  row / column indices. Note that this expects a two-character string,
 *  not the entire string of a phase 2 move.
 */
BoardIndex ParseSpace(const string &space) { 
  BoardIndex ret;
  char col = space.at(0);
  char row = space.at(1);

  if (col == 'a') {
    ret.second = 0;
  } else if (col == 'b') {
    ret.second = 1;
  } else if (col == 'c') {
    ret.second = 2;
  }
  ret.first = row - '0' - 1;

  return ret;
}

/**
 * \brief Determines if a move is valid.
 * \param phase The current game phase.
 * \param player The player that is moving.
 * \param board The current board state.
 * \param move The proposed move.
 * \return true if the move is valid. false if the move is not valid.
 *
 * This function implements the rules of the game. A move is valid if
 * - The source and destination spaces are valid. During phase 1 only the
 *   destination space is checked. During phase 2, both are checked.
 * - The destination space is not occupied.
 * - The source is occupied by the player (cannot move another player's piece).
 *   This is only checked during phase 2.
 * - The destination is adjacent to the source. This is only checked during
 * phase 2.
 */
bool ValidMove(int phase, int player, const Board board, Move move) {

  // Phase one loop
  while (phase == 1) {
    BoardIndex ret;
    ret = move.second;
    int row = ret.first;
    int col = ret.second;

    if (row < 0 || row > 2) {
      // cerr << "Invalid move: out of range" << endl; 
      // prints each time due to first invalid error to begin loop 
      return false;
    }
    if (col < 0 || col > 2) {
      // cerr << "Invalid move: out of range" << endl; 
      // prints each time due to loop
      return false;
    }
    if (board[row][col] != 0) {
      // cerr << "Invalid move: space occupied" << endl; 
      // continuosly prints while looking for computer move 
      return false;

    } else {
      return true;
    }
  }

  // for phase two
  while (phase == 2) {
    BoardIndex sourcePair = move.first;
    BoardIndex destinationPair = move.second;

    int row = destinationPair.first;
    int col = destinationPair.second;
    if (row < 0 || row > 2) {
      // cerr << "Invalid move: out of range" << endl; 
      // prints each time no matter what cause of beginning 
      return false;
    }
    if (col < 0 || col > 2) {
      // cerr << "Invalid move: out of range" << endl; 
      // prints everytime at begining 
      return false;
    }
    if (board[row][col] != 0) {
      // cerr << "Invalid move: space taken" << endl; 
      // loops endlessly during computer move  
      return false;
    }

    // use abs value of row greater than 1 return false
    // abs value of col > 1 return false
    int destinationFirst = row;            // row
    int sourceFirst = sourcePair.first;    // row
    int destinationSecond = col;           // col
    int sourceSecond = sourcePair.second;  // col
    if ((fabs(destinationFirst - sourceFirst)) > 1 || (fabs(destinationSecond - sourceSecond)) > 1) {
      // cerr << "Invalid move" << endl; 
      // loops endlessly during computer move  
      return false;
    } if ((fabs(destinationFirst - sourceFirst) == 1) && (fabs(destinationSecond - sourceSecond) == 1)) {
      // cerr << "Invalid move" << endl;
      // loops endlessly during computer move  
      return false; 
      } else {
      return true;
    }
  }
  // all else return true
  return true;
}
