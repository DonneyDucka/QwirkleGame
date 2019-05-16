
#include "Player.h"

//TODO  Implement the player
Player::Player(LinkedList* playersHand, std::string name, int score)
{
  hand = nullptr;
  playerName = name;
  score = score;
}

void Player::getHand()
{
  return hand->printLine();
}

std::string Player::getName()
{
  return playerName;
}

int Player::getScore()
{
  return score;
}

void Player::setScore(int points)
{
  score = score + points;
}
