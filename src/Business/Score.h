#ifndef SCORE_H
#define SCORE_H


class Score
{
    public:
        Score();
        virtual ~Score();
    protected:
    private:
        int nbWhitePiece;
        int nbWhiteKing;
        int nbBlackPiece;
        int nbBlackKing;
};

#endif // SCORE_H
