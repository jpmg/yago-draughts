/*********************\
|                     |
|    Game.cpp v0.1    |
|    2013-08-12       |
|                     |
\*********************/

#include "Game.h"

#define GET_ADDRESS(x, y) (x) * 5 + (y) / 2

using namespace std;

Game::Move::Move(short numColumn, short numRow)
    : x(numColumn), y(numRow) {}

Game::Game()
    : m_player1(true), m_player2(false)
{
    // The lines are 5 squares wide
    m_gameBoard = new STATE[50];
    for(short i = 0 ; i < 50 ; ++i)
    {
        if(i < 20)
            m_gameBoard[i] = WHITE;
        else if(i >= 30)
            m_gameBoard[i] = BLACK;
    }
}
Game::~Game()
{
    delete m_gameBoard;
}

void Game::computeGraphs(bool** boardGraphNoTaking, bool** boardGraphTaking, bool** boardGraphNoTakingKing, bool** boardGraphTakingKing) const
{
    // Initializations
    for(short i = 0 ; i < 50 ; ++i)
    {
        boardGraphNoTaking[i] = new bool[50];
        boardGraphTaking[i] = new bool[50];
        boardGraphNoTakingKing[i] = new bool[50];
        boardGraphTakingKing[i] = new bool[50];

        for(short j = 0 ; j < 50 ; ++j)
            boardGraphNoTaking[i][j] = boardGraphTaking[i][j] = boardGraphNoTakingKing[i][j] = boardGraphTakingKing[i][j] = false;

    }

    // Array used to compute the four possible directions
    short offsets[2];
    offsets[0] = -1;
    offsets[1] = 1;

    STATE enemy = (m_whitePlays) ? BLACK : WHITE;

    // Loop on all squares
    for(short x = 0 ; x < 10 ; x += 2)
        for(short y = 0 ; y < 10 ; ++y)
        {
            if(m_gameBoard[GET_ADDRESS(x, y)] & enemy) // Will compute successors for player's pawns or empty squares only
                continue;

            // Loop on the four possible directions
            for(short i = 0 ; i < 2 ; ++i)
                for(short j = 0 ; j < 2 ; ++j)
                {
                    short xNeighboor(x + offsets[i] * 2), yNeighboor(y + offsets[j]);
                    if(xNeighboor < 0 || xNeighboor >= 10 || yNeighboor < 0 || yNeighboor >= 10)
                        continue; // Invalid coordinates

                    if(m_gameBoard[GET_ADDRESS(xNeighboor, yNeighboor)] & enemy)
                    {
                        // Destination if we jump over the enemy
                        short xTarget(xNeighboor + offsets[i] * 2), yTarget(yNeighboor + offsets[j]);
                        if(xTarget >= 0 && xTarget < 10 && yTarget >= 0 && yTarget < 10 && m_gameBoard[GET_ADDRESS(xTarget, yTarget)] == VOID)
                            boardGraphTaking[GET_ADDRESS(x, y)][GET_ADDRESS(xTarget, yTarget)] = true;
                        // We could also add the edge in the other way, from target to origin, but we will have to compute it anyway when we look for target's neighboors.
                    }
                    else if(m_gameBoard[GET_ADDRESS(xNeighboor, yNeighboor)] == VOID)
                    {
                        boardGraphNoTaking[GET_ADDRESS(x, y)][GET_ADDRESS(xNeighboor, yNeighboor)] = true;

                        // Compute possible first moves for kings (flying without taking)
                        xNeighboor += 2 * offsets[i];
                        yNeighboor += offsets[j];
                        while(xNeighboor >= 0 && xNeighboor < 10 && yNeighboor >= 0 && yNeighboor < 10 && m_gameBoard[GET_ADDRESS(xNeighboor, yNeighboor)] == VOID)
                        {
                            boardGraphNoTakingKing[GET_ADDRESS(x, y)][GET_ADDRESS(xNeighboor, yNeighboor)] = true;
                            xNeighboor += 2 * offsets[i];
                            yNeighboor += offsets[j];
                        }
                        if(xNeighboor >= 0 && xNeighboor < 10 && yNeighboor >= 0 && yNeighboor < 10 && m_gameBoard[GET_ADDRESS(xNeighboor, yNeighboor)] & enemy)
                        {
                            // Same loop as before except the edges go into the King Taking graph (instead of King No Taking)
                            xNeighboor += 2 * offsets[i];
                            yNeighboor += offsets[j];
                            while(xNeighboor >= 0 && xNeighboor < 10 && yNeighboor >= 0 && yNeighboor < 10 && m_gameBoard[GET_ADDRESS(xNeighboor, yNeighboor)] == VOID)
                            {
                                boardGraphTakingKing[GET_ADDRESS(x, y)][GET_ADDRESS(xNeighboor, yNeighboor)] = true;
                                xNeighboor += 2 * offsets[i];
                                yNeighboor += offsets[j];
                            }
                            // Only this time an enemy stops the move
                        }
                    }
                }
        }
}

void Game::depthFirstSweep(Move& current, bool* captured, bool** boardGraphNoTaking, bool** boardGraphTaking, bool** boardGraphNoTakingKing, bool** boardGraphTakingKing) const
{
    short currentAddress(GET_ADDRESS(current.x, current.y));
    STATE enemy((m_whitePlays) ? BLACK : WHITE);

    bool validMove(false);

    // Recursively compute all possible moves
    for(short x = 0 ; x < 10 ; ++x)
        for(short y = 0 ; y < 10 ; ++y)
        {
            short targetAddress(GET_ADDRESS(x, y));
            Move successor(x, y);
            successor.longestPathLength = current.longestPathLength + 1;

            // Check if the destination is reachable by capturing a man
            if(boardGraphTaking[currentAddress][targetAddress] // The target is accessed by normal taking
                || (m_gameBoard[currentAddress] & KING && boardGraphTakingKing[currentAddress][targetAddress])) // The target is accessed by king taking
            {
                validMove = true;
                short directionX((x > current.x) ? 1 : -1), directionY((y > current.y) ? 1 : -1);
                short x2(current.x), y2(current.y);

                // As it is a taking, set the man located between the origin and the destination as captured
                for( ; !m_gameBoard[GET_ADDRESS(x2, y2)] & enemy ; x2 += directionX, y2 += directionY);

                if(captured[GET_ADDRESS(x2, y2)])
                    validMove = false; // The man was already captured, the move is invalid
                else
                {
                    captured[GET_ADDRESS(x2, y2)] = true;

                    // Recursive on capture
                    depthFirstSweep(successor, captured, boardGraphNoTaking, boardGraphTaking, boardGraphNoTakingKing, boardGraphTakingKing);
                }

            }
            // Otherwise, the destination may be reachable without capturing an enemy
            else if(current.longestPathLength == 0
                && (boardGraphNoTaking[currentAddress][targetAddress] // It's the first move for the man and the move is a valid No Taking
                     || (m_gameBoard[currentAddress] & KING && boardGraphNoTakingKing[currentAddress][targetAddress])) // Same but as a flying king
                )
                validMove = true;

                if(validMove)
                    current.successors.push_back(successor);
            }

    // Compute the longest move's length
    for(unsigned int i = 0 ; i < current.successors.size() ; ++i)
        if(current.successors[i].longestPathLength > current.longestPathLength)
            current.longestPathLength = current.successors[i].longestPathLength;

    // Erase the shorter moves
    for(unsigned int i = 0 ; i < current.successors.size() ; )
    {
        if(current.successors[i].longestPathLength < current.longestPathLength)
            current.successors.erase(current.successors.begin() + i);
        else
            ++i;
    }
}

bool Game::nextTurn()
{
    // The follow arrays represent the game board as a graph, where each vertex is a square and each edge links two squares that can be accessed in one move

    // Squares that are reachable without jumping over an enemy
    bool** boardGraphNoTaking = new bool*[50];
    // Squares that are reachable by jumping over an enemy
    bool** boardGraphTaking = new bool*[50];
    // Squares that are reachable without jumping over an enemy but require to fly
    bool** boardGraphNoTakingKing = new bool*[50];
    // Squares that are reachable by flying over an enemy
    bool** boardGraphTakingKing = new bool*[50];

    computeGraphs(boardGraphNoTaking, boardGraphTaking, boardGraphNoTakingKing, boardGraphTakingKing);

    vector<Move> validMoves;
    // Used to ensure that a man is not taken more than once
    bool* captured = new bool[50];

    // Now sweep the board for the longest possible moves
    for(short x = 0 ; x < 10 ; ++x)
        for(short y = 0 ; y < 10 ; ++y)
        {
            // Reinitialize captured
            for(short i = 0 ; i < 50 ; ++i)
                captured[i] = false;

            // The square does not contain one of the player's men
            if(!(m_whitePlays && m_gameBoard[GET_ADDRESS(x, y)] & WHITE) || !(!m_whitePlays && m_gameBoard[GET_ADDRESS(x, y)] & BLACK))
                continue;

            Move n(x, y);
            depthFirstSweep(n, captured, boardGraphNoTaking, boardGraphTaking, boardGraphNoTakingKing, boardGraphTakingKing);
            validMoves.push_back(n);
        }

    delete captured;
    delete boardGraphNoTaking;
    delete boardGraphTaking;
    delete boardGraphNoTakingKing;
    delete boardGraphTakingKing;

    short lengthsSum(0);
    for(unsigned int i = 0 ; i < validMoves.size() ; ++i)
        lengthsSum += validMoves[i].longestPathLength;
    if(!lengthsSum)
        return false;

    while(validMoves.size() > 0)
    {
        short xOrigin, yOrigin, xDestination, yDestination;
        // Ask the move to apply
        bool invalidMove(true);
        unsigned int validMoveIdx(0), successorIdx(0);
        while(invalidMove)
        {
            if(m_whitePlays)
                m_player1.getNextMove(xOrigin, yOrigin, xDestination, yDestination);
            else
                m_player2.getNextMove(xOrigin, yOrigin, xDestination, yDestination);

            // Check that the move's coordinates are valid
            if(xOrigin < 0 || yOrigin < 0 || xDestination < 0 || yDestination < 0 || xOrigin > 10 || yOrigin > 10 || xDestination > 10 || yDestination > 10)
                continue;

            // Check that the move's origin does exist
            for(validMoveIdx = 0 ; validMoveIdx < validMoves.size() && (validMoves[validMoveIdx].x != xOrigin || validMoves[validMoveIdx].y != yOrigin) ; ++validMoveIdx);
            if(validMoveIdx >= validMoves.size())
                continue;

            for( ; successorIdx < validMoves[validMoveIdx].successors.size() && (validMoves[validMoveIdx].successors[successorIdx].x != xDestination || validMoves[validMoveIdx].successors[successorIdx].y != yDestination) ; ++successorIdx);
            if(successorIdx >= validMoves[validMoveIdx].successors.size())
                continue;
        }

        // Apply the move's effects
        m_gameBoard[GET_ADDRESS(xOrigin, yOrigin)] = VOID;
        for( ; xOrigin != xDestination && yOrigin != yDestination ; ++xOrigin, ++yOrigin)
            if(m_gameBoard[GET_ADDRESS(xOrigin, yOrigin)] != VOID)
                m_gameBoard[GET_ADDRESS(xOrigin, yOrigin)] = static_cast<STATE>(m_gameBoard[GET_ADDRESS(xOrigin, yOrigin)] | CAPTURED);

        validMoves = validMoves[validMoveIdx].successors;
        validMoves.erase(validMoves.begin(), validMoves.begin() + successorIdx);
        if(validMoves.size() > 1)
            validMoves.erase(validMoves.begin() + 1, validMoves.end());
    }

    // Remove captured men
    for(short i = 0 ; i < 50 ; ++i)
        if(m_gameBoard[i] & CAPTURED)
            m_gameBoard[i] = VOID;
}

const Game::STATE* Game::getGameBoard() const { return m_gameBoard; }
