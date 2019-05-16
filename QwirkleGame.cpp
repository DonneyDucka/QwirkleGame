
#include "QwirkleGame.h"
#include <iostream>

#define MAX_ROWS 25
#define MAX_COLS 25

/* This class is for the board, where moves are made and pieces set into the board
 *
 * We need to create an algorithm so that the columns and rows expand(?) to
 * a maximum of 26. (0 -> 25)
 *
 * METHODS INCLUDE:
 *   - place tile (on the board) -> put tile on board, remove from hand
 *
 *   - replace a tile (in their hand) -> remove tile from player hand,
 *                               IF player has two tiles in same name,
 *                                then first tile should be replaced.
 *
 *    NEED TO GET ALGORITHM TO MAKE THE PLACED TILE ON BOARD LOOK
 *    IN ALL DIRECTIONS AND SEE IF IT CAN GET POINTS
 */

QwirkleGame::QwirkleGame()
{
  bag = new Bag();
  bag->fillBag();
  
board = {};
};

QwirkleGame::~QwirkleGame()
{
  delete bag;
}

bool QwirkleGame::placeTile(std::string placement)
{
/*
 * We need to create an algorithm so that the columns and rows expand(?) to
 * a maximum of 26. (0 -> 25)
 * placing tile on board, remove from player's hand
 *
 */


  return true;
}

void QwirkleGame::allocatePoints()
{
  //TO BE IMPLEMENTED, NEED TO GET POINTS FOR COMBO,
  // SUCH AS THE HORIZONTAL RUN AND VERTICAL RUN

}

bool QwirkleGame::replaceTile(std::string replacement)
{
  /*  - replace a tile (in their hand) -> remove tile from player hand,
   *                               IF player has two tiles in same name,
   *                                then first tile should be replaced.
   */


  return true;
}

Bag* QwirkleGame::getBag()
{
  return bag;
}

void QwirkleGame::addPlayer(std::string name)
{
  LinkedList* newHand = new LinkedList();
  Player* p = new Player(newHand, name, 0);
  players.push_back(p);
}

void QwirkleGame::printBoard()
{
  std::cout << board << std::endl;
  // for (int i = 0; i < 6; i++)
  // {
  //   for (int j = 0; j < 6; j++)
  //   {
  //       std::cout << board[i][j];
  //   }
  //   std::cout << std::endl;
  // }
}

// str = const_cast<char*>((str2.substr(2,4)).c_str());  <- casting string to char
