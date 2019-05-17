
#ifndef ASSIGN2_QWIRKLEGAME_H
#define ASSIGN2_QWIRKLEGAME_H

#include "LinkedList.h"
#include "Player.h"
#include "Bag.h"
#include <string>
#include <vector>
#include "TileCodes.h"

typedef char BoardCoor;
class QwirkleGame
{

public:
  QwirkleGame();
  ~QwirkleGame();

  bool placeTile(std::string placement, Player* player);
  void allocatePoints();
  bool replaceTile(std::string replacement, Player* player);
  void addPlayer(std::string name);
  void fillPlayerHands();
  void printBoard();
  std::vector<Player *> getPlayers();

  Bag *getBag();

private:
  int letterToNumber(char a);
  Tile *board[6][6];
  std::vector<Player *> players;
  Bag *bag;
};

#endif // ASSIGN2_QWIRKLEGAME_H
