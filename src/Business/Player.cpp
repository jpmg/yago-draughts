#include "Player.h"

Player::Player(bool isWhite)
    : m_isWhite(isWhite) {}

void Player::getNextMove(Coordinate& origin, Coordinate& destination) const
{
    // For a human player, wait/sleep until a move was made on the GUI
}
