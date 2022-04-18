#ifndef SUPERSICKAI_H
#define SUPERSICKAI_H


#include "Board.h"
#include <vector>
class SuperSickAI
{
public:
    SuperSickAI();
    ~SuperSickAI();
    std::vector<int> getBestMove(Board * b);

};

#endif // SUPERSICKAI_H
