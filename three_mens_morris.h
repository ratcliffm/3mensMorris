#ifndef THREE_MENS_MORRIS_H

#include <string>
#include <utility>  // For pair
#include <vector>

/**
 * \brief The main board type. 3x3 vector.
 *
 * This is a vector of integer vectors.
 * Each vector is guaranteed to be length 3.
 */
typedef std::vector<std::vector<int>> Board;

/**
 * \brief A pair of indices into our board.
 *
 * Used to represent a space on our 3x3 board.
 * The first element of the pair is the row.
 * The second element of the pair is the column.
 * For example, the pair 0,0 is the top left corner.
 */
typedef std::pair<int, int> BoardIndex;

/**
 * \brief A move from one place to another on the board.
 *
 * A pair of board indices (spaces).
 * This represents a move from one location to another.
 * The first element of the pair is the source.
 * The second element of the pair is the destination.
 * During phase 1 of the game, only the destination matters.
 */
typedef std::pair<BoardIndex, BoardIndex> Move;

void PrintBoard(Board board);
BoardIndex ParseSpace(const std::string &space);
int PlayerAtSpace(const Board board, const BoardIndex space);
void SetPlayerAtSpace(Board &board, const int player, const BoardIndex space);
bool ValidMove(int phase, int player, const Board board, Move move);
Move ParseMove(int phase, const std::string move);
int GameOver(const Board board);

#endif
