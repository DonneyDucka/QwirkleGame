
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
  //bag->fillBag();

  for (int i = 0; i < 26; i++)
  {

    for (int j = 0; j < 26; j++)
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
  std::string x = placement.substr(7, 1);
  std::string y = placement.substr(8, 1);
  std::string code = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  bool p = (code.find(x) != std::string::npos);
   Tile *tileInHand = nullptr;
  int x2n = letterToNumber(*x.c_str());
  int y2n = std::atoi(y.c_str());
  int i = 0;
  
  if (p == false ) {
    std::cout << "incorrect tile entered";
    return false;
  }
  else if (y2n < 26 && x2n < 26)
  {
    while (tileInHand == nullptr && i < 6)
    {

      if (player->getHand()->findNode(i)->getTile()->getTileDets() == tile)
      {
        if ((checkPlacement(x2n, y2n, tileInHand)) == true)
        {
          board[x2n][std::atoi(y.c_str())] = tileInHand;
         tileInHand = player->getHand()->findNode(i)->getTile();
         bag->getList()->addBack(tileInHand);
         player->getHand()->deleteNode(i);
         Node *pickedTile = bag->pickFromBag();
         player->getHand()->addAt(i, pickedTile);
          return true;
        }
        else
          std::cout << "Not a legal placement" << std::endl;
          return false;
      }
     i++;
    }
  }
 
  if (tileInHand == nullptr)
  {
    std::cout << "The tile you have entered does not exist" << std::endl;
  }
  else if (std::atoi(y.c_str()) > 26 && letterToNumber(*x.c_str()) > 26)
  {
    std::cout << "The tile you have entered is beyond the boundaries of the board" << std::endl;
  }

  return check;
}

void QwirkleGame::allocatePoints(int x, int y, Player *player)
{
  int trackVer = 0;
  int trackHor = 0;
  for (int i = 0; i < y; i++)
  {
    if (board[x][i] != nullptr && i < y)
    {
      trackHor++;
    }
    else if (board[x][i] == nullptr)
    {
      trackHor = 0;
    }
  }
  for (int i = 6; i > y; i--)
  {

    if (board[x][i] != nullptr && i > y)
    {
      trackHor++;
    }
    else if (board[x][i] == nullptr && trackHor < 1)
    {
      trackHor = 0;
    }
  }
  for (int i = 0; i < x; i++)
  {

    if (board[i][y] != nullptr && i < x)
    {
      trackVer++;
    }
    else if (board[x][i] == nullptr)
    {
      trackVer = 0;
    }
  }
  for (int i = 6; i > x; i--)
  {

    if (board[i][y] != nullptr && i > y)
    {
      trackVer++;
    }
    else if (board[i][y] == nullptr && trackVer < 1)
    {
      trackVer = 0;
    }
  }
  if (trackHor == 6 || trackVer == 6)
  {
    std::cout << "QWIRKLE" << std::endl;
  }
  int totalpoints = trackHor + trackVer;

  player->setScore(totalpoints);
}

bool QwirkleGame::replaceTile(std::string replacement, Player *player)
{
  /*  - replace a tile (in their hand) -> remove tile from player hand,
   *                               IF player has two tiles in same name,
   *                                then first tile should be replaced.
   */

  Tile *tileInHand = nullptr;
  bool check = false;
  std::string tile = replacement.substr(1, 2);

  if (replacement.length() == 3)
  {
    for (int k = 0; k < player->getHand()->returnSize(); k++)
    {
      if (player->getHand()->findNode(k)->getTile()->getTileDets() == tile)
      {
        tileInHand = player->getHand()->findNode(k)->getTile();
        bag->getList()->addBack(tileInHand);
        player->getHand()->deleteNode(k);
        Node *pickedTile = bag->pickFromBag();
        player->getHand()->addAt(k, pickedTile);
        check = true;
      }
    }
  }
  else if (tileInHand == nullptr)
  {
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
  std::cout << "  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25" << std::endl;
  std::cout << " ------------------------------------------------------------------------------- " << std::endl;

  boardToString = "  0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 \n ------------------------------------------------------------------------------- \n";

  char a = 'A';
  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 26; j++)
    {
      if (j == 0)
      {
        std::cout << a;
        boardToString += a;
        a++;
      }
      std::cout << "|";
      boardToString += "|";

      if (board[i][j] == nullptr)
      {
        std::cout << "  ";
        boardToString += "  ";
      }
      else
      {
        std::cout << board[i][j]->getTileDets();
        boardToString += board[i][j]->getTileDets();
      }
      if (j == 25)
      {
        std::cout << "|";
        boardToString += "|";
      }
    }
    std::cout << std::endl;
    boardToString += "\n";
  }
}
// board Coordinate converting A = 0, B = 1 ... z = 25
int QwirkleGame::letterToNumber(char word)
{
  int x = word;

  if (!isupper(static_cast<unsigned char>(word)) == true)
  {
    x = std::tolower(word);
  }
  return x - 65;
}

std::string QwirkleGame::getBoard()
{
  return boardToString;
}

bool QwirkleGame::checkPlacement(int x, int y, Tile *tile)
{
  bool check = true;
  int counter = 0;
  if (board[x][y] == nullptr)
  {
    return check;
  }
  else
  {
    // left            right            bottom           top
    Tile *surrounding[4] =
        {board[x][y - 1], board[x][y + 1], board[x + 1][y], board[x - 1][y]};

    while (counter < 4)
    {

      if (surrounding[counter] != nullptr)
      {

        if (surrounding[counter]->getColour() != tile->getColour() && surrounding[counter]->getShape() != tile->getShape())
        {
          check = false;
          return check;
        }
      }
      counter++;
    }
  }
  return check;
}

