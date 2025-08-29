#include <limits>

#include "ai.h"
#include "board.h"
#include "constants.h"
#include "game.h"

#include <iostream>

ai::ai(ai_difficulty level) : difficulty(level) {}

position ai::get_move(const board& current_board)
{
  if (difficulty == ai_difficulty::Dumb) {
    auto moves = current_board.possible_moves();
    return moves[rand() % moves.size()];
  } else {
    return find_best_move(current_board); // minimax
  }
}

// todo: switch the player so that AI can start first
// reference: https://www.datacamp.com/tutorial/minimax-algorithm-for-ai-in-python
int ai::minimax(board& current_board, int depth, bool is_maximizing)
{
  char winner = current_board.check_winner();
  bool tie = current_board.is_tie();

  //std::cout << "Depth " << depth
  //        << ": Winner: " << winner
  //        << ", Tie: " << tie
  //        << ", Possible moves: " << current_board.possible_moves().size()
  //        << "\n";

  if (winner == PLAYER_O) return WIN_SCORE - depth;
  if (winner == PLAYER_X) return LOSE_SCORE + depth;
  if (tie) return TIE_SCORE;

  if (is_maximizing) {
    int best_score = std::numeric_limits<int>::min();

    for (const position& p : current_board.possible_moves()) {
      board temp_board = current_board;
      temp_board.make_move(p, PLAYER_O);

      int score = minimax(temp_board, depth + 1, false);
      best_score = std::max(score, best_score);
    }

    return best_score;
  } else {
    int best_score = std::numeric_limits<int>::max();

    for (const position& p : current_board.possible_moves()) {
      board temp_board = current_board;
      temp_board.make_move(p, PLAYER_X); // minimizing player

      int score = minimax(temp_board, depth + 1, true);
      best_score = std::min(score, best_score);
    }

    return best_score;
  }

  return 0;
}


position ai::find_best_move(const board& current_board)
{
  int best_score = std::numeric_limits<int>::min();
  position best_move = { -1, -1 };

  for (const position& p: current_board.possible_moves()) {
    board temp_board = current_board;
    temp_board.make_move(p, PLAYER_O); // ai is O

    int score = minimax(temp_board, 0, false);

    if (score > best_score) {
      best_score = score;
      best_move = p;
    }
  }

  return best_move;
}
