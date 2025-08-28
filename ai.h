#ifndef _AI_H_
#define _AI_H_

#include <string>

class board;

class ai
{
public:
  std::string get_ai_move();
private:
  int minimax(const board& board, int depth, bool is_ai);
};

#endif /* _AI_H_ */
