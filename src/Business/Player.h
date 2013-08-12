// TODO: Thread

//! A player of Draughts.
class Player
{
    public:
        //! Constructor.
        explicit Player(bool isWhite);

        //! Asks for the player's next move
        /*!
            \param xOrigin Column number of the man that is moved.
            \param yOrigin Row number of the man that is moved.
            \param xDestination Column number of the landing square.
            \param yDestination Row number of the landing square.
        */
        void getNextMove(short& xOrigin, short& yOrigin, short& xDestination, short& yDestination) const;

    private:
        bool m_isWhite;
};
