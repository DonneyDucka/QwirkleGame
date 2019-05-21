
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
  void allocatePoints(int x, int y, Player* player);
  bool replaceTile(std::string replacement, Player* player);
  void addPlayer(std::string name);
  void fillPlayerHands();
  void printBoard();
  bool checkPlacement(int x, int y, Tile* pos);
  std::string getBoard();
  std::vector<Player *> getPlayers();
  Bag *getBag();

private:
  int letterToNumber(char a);
  Tile *board[26][26];
  std::string boardToString;
  std::vector<Player *> players;
  Bag *bag;
};

#endif // ASSIGN2_QWIRKLEGAME_H
