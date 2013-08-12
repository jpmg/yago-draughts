// TODO: Thread

//! A player of Draughts.
class Player
{
    public:
        //! Constructor.
        Player(bool isWhite);

        //! Asks for the player's next move
        /*!
            \param origin Coordinates of the man that is moved.
            \param destination Coordinates of the landing square.
        */
        void getNextMove(Coordinate& origin, Coordinate& destination);

    private:
        bool m_isWhite;
};
