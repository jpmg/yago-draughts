#include "Player.h"

Player::Player(bool isWhite)
    : m_isWhite(isWhite) {}

void Player::getNextMove(short& xOrigin, short& yOrigin, short& xDestination, short& yDestination) const
{
    // For a human player, wait/sleep until a move was made on the GUI
}
