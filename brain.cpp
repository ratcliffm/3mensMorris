/*! \file brain.cpp
    \brief Computer AI
    This file contain the definition of our advanced
    artificial intelligence system... the Galaxy Brain!
*/

#include "brain.h"
#include <iostream>
#include <random>
using namespace std;

/**
 * \brief Uses sophisticated artificial intelligence to return the next move.
 * \param board The current board state.
 * \return The move to make.
 */
Move GalaxyBrain(const Board board) {
  Move move; 
  // cout << "galxy" << endl; infinite loop testing 

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

  BoardIndex source; 
  BoardIndex destination;
  if (gamePhase == 1) {
    for (unsigned int row = 0; row < board.size(); ++row) {
    for (unsigned int col = 0; col < board[row].size(); ++col) {
        source.first = 1;
        source.second = 1;
    if ((board[row][0] == 1) && (board[row][1] == 1) && (board[row][2] == 0)) {
        destination.first = row;
        destination.second = 2; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[row][0] == 1) && (board[row][2] == 1) && (board[row][1] == 0)) {
        destination.first = row;
        destination.second = 1; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[row][1] == 1) && (board[row][2] == 1) && (board[row][0] == 0)) {
        destination.first = row;
        destination.second = 0;   
        move.first = source;
        move.second = destination; 
        return move;

        } else if ((board[0][col] == 1) && (board[1][col] == 1) && (board[2][col] == 0)) {
        destination.first = 2;
        destination.second = col;  
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[0][col] == 1) && (board[2][col] == 1) && (board[1][col] == 0)) {
        destination.first = 1;
        destination.second = col;  
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[1][col] == 1) && (board[2][col] == 1) && (board[0][col] == 0)) {
        destination.first = 0;
        destination.second = col; 
        move.first = source;
        move.second = destination; 
        return move; // done for blocking 
        } 
        // check for winning 
        else if ((board[row][0] == 2) && (board[row][1] == 2) && (board[row][2] == 0)) {
        destination.first = row;
        destination.second = 2; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[row][0] == 2) && (board[row][2] == 2) && (board[row][1] == 0)) {
        destination.first = row;
        destination.second = 1; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[row][1] == 2) && (board[row][2] == 2) && (board[row][0] == 0)) {
        destination.first = row;
        destination.second = 0;   
        move.first = source;
        move.second = destination; 
        return move; 
        } else if ((board[0][col] == 2) && (board[1][col] == 2) && (board[2][col] == 0)) {
        destination.first = 2;
        destination.second = col;  
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[0][col] == 2) && (board[2][col] == 2) && (board[1][col] == 0)) {
        destination.first = 1;
        destination.second = col;  
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[1][col] == 2) && (board[2][col] == 2) && (board[0][col] == 0)) {
        destination.first = 0;
        destination.second = col; 
        move.first = source;
        move.second = destination; 
        return move;
        } else { source.first = 1;
                source.second = 1;
    srand(time(0));
    destination.first = rand() % 3; 
    destination.second = rand() % 3; 
    move.first = source;
    move.second = destination; 
    return move; } 
    }
    }
    return move; 
  }

  if (gamePhase == 2) {
    for (unsigned int row = 0; row < board.size(); ++row) {
    for (unsigned int col = 0; col < board[row].size(); ++col) {
      int oldRow = row + 1 || row -1; 
      int oldCol = col + 1 || col -1; 
      if ((board[row][0] == 1) && (board[row][1] == 1) && (board[row][2] == 0)) {
        destination.first = row;
        destination.second = 2; 
        source.first = oldRow;
        source.second = 2; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[row][0] == 1) && (board[row][2] == 1) && (board[row][1] == 0)) {
        destination.first = row;
        destination.second = 1; 
        source.first = oldRow;
        source.second = 1; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[row][1] == 1) && (board[row][2] == 1) && (board[row][0] == 0)) {
        destination.first = row;
        destination.second = 0;   
        source.first = oldRow; 
        source.second = 0; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[0][col] == 1) && (board[1][col] == 1) && (board[2][col] == 0)) {
        destination.first = 2;
        destination.second = col;  
        source.first = 1; 
        source.second = oldCol; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[0][col] == 1) && (board[2][col] == 1) && (board[1][col] == 0)) {
        destination.first = 1;
        destination.second = col;  
        source.first = 1; 
        source.second = oldCol; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[1][col] == 1) && (board[2][col] == 1) && (board[0][col] == 0)) {
        destination.first = 0;
        destination.second = col; 
        source.first = 0; 
        source.second = oldCol; 
        move.first = source;
        move.second = destination; 
        return move; // done for blocking 

        // code for winning 
        if ((board[row][0] == 2) && (board[row][1] == 2) && (board[row][2] == 0)) {
        destination.first = row;
        destination.second = 2; 
        source.first = oldRow;
        source.second = 2; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[row][0] == 2) && (board[row][2] == 2) && (board[row][1] == 0)) {
        destination.first = row;
        destination.second = 1; 
        source.first = oldRow;
        source.second = 1; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[row][1] == 2) && (board[row][2] == 2) && (board[row][0] == 0)) {
        destination.first = row;
        destination.second = 0;   
        source.first = oldRow; 
        source.second = 0; 
        move.first = source;
        move.second = destination; 
        return move;

        } else if ((board[0][col] == 2) && (board[1][col] == 2) && (board[2][col] == 0)) {
        destination.first = 2;
        destination.second = col;  
        source.first = 1; 
        source.second = oldCol; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[0][col] == 2) && (board[2][col] == 2) && (board[1][col] == 0)) {
        destination.first = 1;
        destination.second = col;  
        source.first = 1; 
        source.second = oldCol; 
        move.first = source;
        move.second = destination; 
        return move;
        } else if ((board[1][col] == 2) && (board[2][col] == 2) && (board[0][col] == 0)) {
        destination.first = 0;
        destination.second = col; 
        source.first = 0; 
        source.second = oldCol; 
        move.first = source;
        move.second = destination; 
        return move;
      // code for other moves 
      } /*else { 
        srand(time(0));
        destination.first = rand() % 3; 
        destination.second = rand() % 3; 
        int sourceRow = destination.first + 1 || destination.first -1 || destination.first;
        int sourceCol = destination.second + 1 || destination.second -1 || destination.second;
        source.first = sourceRow;
        source.second = sourceCol; 
        move.first = source;
        move.second = destination; 
        } */ 
        
        
          else { 
            if (board[row][col] == 2){ 
          source.first = row;
          source.second = col; 
            } else if (board[row + 1][col] == 0) { 
          destination.first = row +1;
          destination.second = col; 
            } else if (board[row - 1][col] == 0) { 
          destination.first = row - 1;
          destination.second = col; 
            } else if (board[row][col + 1] == 0) { 
          destination.first = row;
          destination.second = col + 1;
            } else if (board[row][col - 1] == 0) { 
          destination.first = row;
          destination.second = col - 1;
            }
          move.first = source;
          move.second = destination; 
          return move; 
        }
      }
    }
    }
    }

ValidMove(gamePhase, 2,board, move);
move.first = source;
move.second = destination; 
 
return move; 
}
