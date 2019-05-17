
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
  this->bag = new Bag();
  bag->fillBag();

  for (int i = 0; i < 6; i++)
  {

    for (int j = 0; j < 6; j++)
    {

      board[i][j] = nullptr;
    }
  }
}
QwirkleGame::~QwirkleGame()
{
  delete bag;
}

bool QwirkleGame::placeTile(std::string placement, Player *player)
{
  bool check = false;
  std::string tile = placement.substr(1, 2);
  std::string x = placement.substr(6, 1);
  std::string y = placement.substr(7, 1);
  Tile *tileInHand = nullptr;
  
  if (std::atoi(y.c_str()) < 6 && letterToNumber(*x.c_str()) < 6)
  {

    for (int i = 0; i < player->getHand()->returnSize(); i++)
    {

      if (player->getHand()->findNode(i)->getTile()->getTileDets() == tile)
      {

        tileInHand = player->getHand()->findNode(i)->getTile();

        board[std::atoi(x.c_str())][std::atoi(y.c_str())] = tileInHand;
        player->getHand()->deleteNode(i);

        check = true;
        break;
      }
    }
  }
  else if (tileInHand == nullptr)
  {
    std::cout << "The tile you have entered does not exist" << std::endl;
  }
  else if (std::atoi(y.c_str()) > 6 && letterToNumber(*x.c_str()) > 6)
  {
    std::cout << "The tile you have entered is beyond the boundaries of the board" << std::endl;
  }

  return check;
}

void QwirkleGame::allocatePoints()
{
  //TO BE IMPLEMENTED, NEED TO GET POINTS FOR COMBO,
  // SUCH AS THE HORIZONTAL RUN AND VERTICAL RUN
}

bool QwirkleGame::replaceTile(std::string replacement, Player* player)
{
  /*  - replace a tile (in their hand) -> remove tile from player hand,
   *                               IF player has two tiles in same name,
   *                                then first tile should be replaced.
   */
  Tile *tileInHand = nullptr;
  bool check = false;
  std::string tile = replacement.substr(1,2);
  if (replacement.length() == 3)
  {
    for (int i = 0; i < player->getHand()->returnSize(); i++)
    {

      if (player->getHand()->findNode(i)->getTile()->getTileDets() == tile)
      {
        tileInHand = player->getHand()->findNode(i)->getTile();
        bag->getList()->addBack(tileInHand);
        Node* pickedTile = bag->getList()->findNode(1);
        player->getHand()->addAt(i,pickedTile);
        bag->getList()->deleteFront();
        player->getHand()->deleteNode(i);
        check = true;
      }
    }
  } else if (tileInHand == nullptr) {
    std::cout << "You have entered an invalid tile";
  } 

  return check;
}

Bag *QwirkleGame::getBag()
{
  return bag;
}

void QwirkleGame::addPlayer(std::string name)
{
  Player *p = new Player(name, 0);
  players.push_back(p);
}

std::vector<Player *> QwirkleGame::getPlayers()
{
  return players;
}

void QwirkleGame::fillPlayerHands()
{

  for (int i = 0; i < players.size(); i++)
  {

    players.at(i)->fillHand(bag);
  }
}
void QwirkleGame::printBoard()
{
  std::cout << "  0  1  2  3  4  5  " << std::endl;
  std::cout << " ------------------- " << std::endl;
  char a = 'A';
  for (int i = 0; i < 6; i++)
  {

    for (int j = 0; j < 6; j++)
    {
      if (j == 0)
      {
        std::cout << a;
        a++;
      }
      std::cout << "|";

      if (board[i][j] == nullptr)
      {
        std::cout << "  ";
      }
      else
      {
        std::cout << board[i][j]->getTileDets();
      }
      if (j == 5)
      {

        std::cout << "|";
      }
    }
    std::cout << std::endl;
  }
}
// board Coordinate converting A = 0, B = 1 ... z = 25
int QwirkleGame::letterToNumber(char a)
{

  if (!isupper(static_cast<unsigned char>(a) == false))
  {
    std::toupper(a);
  }
  std::cout << (int)a - 65;
  return (int)a - 65;
}

// str = const_cast<char*>((str2.substr(2,4)).c_str());  <- casting string to char
