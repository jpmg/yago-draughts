#ifndef MOVE_H
#define MOVE_H


class Move
{
    public:
        Move(short numCol, short numRow)
        virtual ~Move();
    protected:
    private:
        short x;
        short y;
};

#endif // MOVE_H
