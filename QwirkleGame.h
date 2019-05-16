
#ifndef ASSIGN2_QWIRKLEGAME_H
#define ASSIGN2_QWIRKLEGAME_H

#include "LinkedList.h"
#include "Player.h"
#include "Bag.h"
#include <string>
#include <vector>

class QwirkleGame {

public:

QwirkleGame();
~QwirkleGame();

bool placeTile(std::string placement);
void allocatePoints();
bool replaceTile(std::string replacement);

void addPlayer(std::string name);
void printBoard();

Bag* getBag();

private:

  char** board;
  std::vector<Player*> players;
  Bag* bag;


};





#endif // ASSIGN2_QWIRKLEGAME_H
