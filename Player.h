
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include "Tile.h"
#include <string>

class Player {
public:

   Player(LinkedList* playersHand, std::string name, int score);

   void getHand();
   void fillHand();
   std::string getName();
   int getScore();
   void setScore(int points);
   void resetTurn();

private:
   LinkedList* hand;
   std::string playerName;
   int score;
};

#endif // ASSIGN2_NODE_H
