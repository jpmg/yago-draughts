/*******************\
|                   |
|    Game.h v0.1    |
|    2013-08-12     |
|                   |
\*******************/

#include "Player.h"

//! A game of Draughts (International draughts).
class Game
{
    public:
        //! Represents the state of a square of the board.
        enum STATE
        {
            VOID = 0, WHITE = 1, BLACK = 2, KING = 4, CAPTURED = 8
        };

        //! Constructor.
        Game();
        //! Destructor.
        ~Game();

        //! Game routine.
        /*!
            Applies the next player's move.
            \return 'false' if the current player cannot move and loses the game.
        */
        bool nextTurn();

    private:
        // !Represents a move by its destination
        struct Move
        {
            short x; //!< Column number.
            short y; //!< Row number.
            short longestPathLength; //!< Longest possible moves from this position.
            std::vector<Move> successors; //!< List of possible following moves.

            //! Constructor.
            Move();
        };

        Player m_player1; //!< White player.
        Player m_player2; //!< Black player.
        STATE* m_gameBoard; //!< State of every square of the board.
        bool m_whitePlays; //!< True if the next player is White.

        //! Computes the squares that a man can reach from a given position, in different manners.
        /*!
            Represents the current state of the game as 4 graphs. Each graph uses the board's squares as vertices and add an edge between two vertices if a man can move from the first to the latter according to specific rules.
            \param boardGraphNoTaking The move is valid if it is the man's first move, as it doesn't capture any enemy.
            \param boardGraphTaking This indicate that the man reaches the destination by capturing an enemy.
            \param boardGraphNoTakingKing No taking move, except it requires the king's flying ability.
            \param boardGraphTakingKing Taking move, except it requires the king's flying ability.
        */
        void computeGraphs(bool** boardGraphNoTaking, bool** boardGraphTaking, bool** boardGraphNoTakingKing, bool** boardGraphTakingKing);
        
        //! Computes the set of valid moves for the current turn.
        /*!
            Sweep the four graphs that were previously created and created chained lists of valid moves. At the end, keeps only the longests.
            \param current Current moved being explored.
            \param captured List of the men that were already captured during this move.
            \param boardGraphNoTaking List of possible destinations without capturing an enemy.
            \param boardGraphTaking List of possible destinations by capturing an enemy.
            \param boardGraphNoTakingKing List of possible destinations without capturing an enemy but requiring the king's flying ability.
            \param boardGraphTakingKing List of possible destinations by capturing an enemy and requiring the king's flying ability.
            \sa computeGraphs
        */
        void depthFirstSweep(Move& current, bool* captured, bool** boardGraphNoTaking, bool** boardGraphTaking, bool** boardGraphNoTakingKing, bool** boardGraphTakingKing);
};
