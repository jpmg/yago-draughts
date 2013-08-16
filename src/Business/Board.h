#ifndef BOARD_H
#define BOARD_H

#include "Score.h"

class Board
{
    public:
        Board();
        virtual ~Board();
        void updateScore(Score& score);
    protected:
    private:
};

#endif // BOARD_H
