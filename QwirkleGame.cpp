
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

bool QwirkleGame::placeTile(std::string placement)
{
  bool check = false;
  std::string tile = placement.substr(1, 2);
  std::string x = placement.substr(7, 1);
  std::string y = placement.substr(8, 1);
  std::string y2;
  int twoDigit;

  std::string code = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  bool p = (code.find(x) != std::string::npos);
  Tile *tileInHand = nullptr;
  int y2n = letterToNumber(*x.c_str());
  int x2n = std::atoi(y.c_str());
  int i = 0;

  if (placement.length() > 9)
  {
    y2 = placement.substr(9, 1);
    twoDigit = (10 * x2n) + (std::atoi(y2.c_str()));
    std::cout << twoDigit;
    x2n = twoDigit;
  }

  if (p == false)
  {
    std::cout << "incorrect tile entered";
    return false;
  }
  else if (x2n < 26 && y2n < 26)
  {
    while (tileInHand == nullptr && i < 6)
    {

      if (currentP->getHand()->findNode(i)->getTile()->getTileDets() == tile)
      {
        tileInHand = currentP->getHand()->findNode(i)->getTile();
        if ((checkPlacement(y2n, x2n, tileInHand)) == true)
        {
          board[y2n][x2n] = tileInHand;
          bag->getList()->addBack(tileInHand);
          currentP->getHand()->deleteNode(i);
          Node *pickedTile = bag->pickFromBag();
          currentP->getHand()->addAt(i, pickedTile);
          allocatePoints(y2n, x2n, currentP);
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
    if (board[x][i] != nullptr && i <= y)
    {
      trackHor++;
    }
    else if (board[x][i] == nullptr)
    {
      trackHor = 0;
    }
  }
  for (int i = 26; i > y; i--)
  {

    if (board[x][i] != nullptr && i >= y)
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

    if (board[i][y] != nullptr && i <= x)
    {
      trackVer++;
    }
    else if (board[x][i] == nullptr)
    {
      trackVer = 0;
    }
  }
  for (int i = 26; i > x; i--)
  {

    if (board[i][y] != nullptr && i >= y)
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

bool QwirkleGame::replaceTile(std::string replacement)
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
    for (int k = 0; k < currentP->getHand()->returnSize(); k++)
    {
      if (currentP->getHand()->findNode(k)->getTile()->getTileDets() == tile)
      {
        tileInHand = currentP->getHand()->findNode(k)->getTile();
        bag->getList()->addBack(tileInHand);
        currentP->getHand()->deleteNode(k);
        Node *pickedTile = bag->pickFromBag();
        currentP->getHand()->addAt(k, pickedTile);
        return true;
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

bool QwirkleGame::checkPlacement(int y, int x, Tile *tile)
{
  bool check = false;
  int counter = 0;
  int trackR = 0;
  int trackL = 0;
  int trackU = 0;
  int trackD = 0;
  bool empty = false;

  for (int i = 0; i < 27; i++)
  {
    for (int l = 0; l < 27; l++)
    {

      if (board[i][l] == nullptr)
      {
        empty = true;
      }
      else
        empty = false;
    }
  }

  if (empty == true)
  {
    return true;
  }

  for (int j = 1; j < 8; j++)
  {

    if (board[y][x - j] == nullptr && trackL == 0)
    {
      trackL = j - 1;
    }

    if (board[y][x + j] == nullptr && trackR == 0)
    {
      trackR = j - 1;
    }

    if (board[y + j][x] == nullptr && trackU == 0)
    {
      trackU = j - 1;
    }

    if (board[y - j][x] == nullptr && trackD == 0)
    {
      trackD = j - 1;
    }
  }
  std::cout << trackD << trackU << trackR << trackL;
  if ((trackD + trackU) > 6 || (trackL + trackR) > 6)
  {
    return false;
  }

  // left            right            bottom           top
  Tile *surrounding[8] =
      {board[y][x - 1], board[y][x - 2], board[y][x + 1], board[y][x + 2], board[y + 1][x], board[y + 2][x], board[y - 1][x], board[y - 2][x]};
  int seperator = 0;
  int shapeOrColour = 0;
  while (counter < 4)
  {
    if (surrounding[counter] != nullptr)
    {
      Colour surColour = surrounding[counter]->getColour();
      Shape surShape = surrounding[counter]->getShape();

      if (surColour != tile->getColour() && surShape != tile->getShape())
      {
        return false;
      }
      else if (surrounding[counter + 1] != nullptr &&
               surColour == surrounding[counter + 1]->getColour() && surColour == tile->getColour())
      {
        if (seperator == 1 && (surrounding[counter + 2] == nullptr))
        {
          return true;
        }
        else if (seperator == 1 && (surrounding[counter + 2]->getColour() == surColour))
        {
          shapeOrColour = 1;
        }
      }
      else if (surrounding[counter + 1] != nullptr &&
               surShape == surrounding[counter + 1]->getShape() && surShape == tile->getShape())
      {
        if (seperator == 1 && (surrounding[counter + 2] == nullptr))
        {
          return true;
        }
        else if (seperator == 1 && (surrounding[counter + 2]->getShape() == surShape))
        {
          shapeOrColour = 2;
        }
      }
      else
      {
        if ( shapeOrColour == 2 &&
          (surrounding[counter + 2]->getShape() == surShape) && (surrounding[counter + 3]->getShape() == surShape ))
        {
          return true;
        }
        else if (shapeOrColour == 1 &&
          (surrounding[counter + 2]->getColour() == surShape) && (surrounding[counter + 3]->getColour() == surShape ))
        {
          return true;
        }
      }
    }
    else {

      if ( surrounding[counter + 2]->getShape() == tile->getShape() &&
          (surrounding[counter + 2]->getShape() == surrounding[counter + 3]->getShape()))
        {
          return true;
        }
        else if (surrounding[counter + 2]->getColour() == tile->getColour() &&
          (surrounding[counter + 2]->getColour() == surrounding[counter + 3]->getColour()))
        {
          return true;
        }
    }
    counter += 3;
  }
  return check;
}

bool QwirkleGame::gameFinished()
{

bool playerHandEmpty = false;

  for(int i = 0; i < players.size(); i++)
  {
    if(players[i]->getHand()->returnSize() == 0)
    {
      players[i]->setScore(6);
      playerHandEmpty = true;
    }
  }

  if(bag->getSize() == 0 && playerHandEmpty)
  {
    return true;
  }

  return false;
}



void QwirkleGame::setBoard(int x, int y, Tile *tile)
{

  board[y][x] = tile;
}

void QwirkleGame::setCurrentPlayer(Player *player)
{

  currentP = player;
}
Player *QwirkleGame::getCurrentPlayer()
{

  return currentP;
}