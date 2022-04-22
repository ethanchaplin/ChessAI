#ifndef SUPERSICKAI_H
#define SUPERSICKAI_H


#include "Board.h"
#include <vector>
#include <map>
class SuperSickAI
{
public:
    SuperSickAI();
    ~SuperSickAI();
    static std::vector<int> getBestMove(Board * b, Piece::Color color, int depth);
    static int negamax(Board *b, int color, int depth);

};

#endif // SUPERSICKAI_H
