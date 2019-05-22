
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
  int trackR = 0;
  int trackL = 0;
  int trackU = 0;
  int trackD = 0;
  bool empty = true;

  for (int i = 0; i < 27; i++)
  {
    for (int l = 0; l < 27; l++)
    {

      if (board[i][l] != nullptr)
      {
        empty = false;
      }
    }
  }
  if (empty)
  {
    return true;
  }

  for (int j = 1; j < 8; j++)
  {

    if (board[y][x - j] == nullptr && trackL == 0)
    {
      trackL = j - 1;
     
    } 
    else if (board[y][x - j] != nullptr && (board[y][x-j]->getTileDets() == tile->getTileDets())) {
      return false;
    }

    if (board[y][x + j] == nullptr && trackR == 0)
    {
      trackR = j - 1;
    }
    else if (board[y][x + j] != nullptr && (board[y][x+j]->getTileDets() == tile->getTileDets())) {
      return false;
    }

    if (board[y + j][x] == nullptr && trackU == 0)
    {
      trackU = j - 1;
    }
    else if (board[y+j][x] != nullptr && (board[y+j][x]->getTileDets() == tile->getTileDets())) {
      return false;
    }

    if (board[y - j][x] == nullptr && trackD == 0)
    {
      trackD = j - 1;
    }
    else if (board[y - j][x] != nullptr && (board[y-j][x]->getTileDets() == tile->getTileDets())) {
      return false;
    }
  }
  if ((trackD + trackU) > 6 || (trackL + trackR) > 6)
  {
    return false;
  
  } else check = true;
   

  // left            right            bottom           top
  Tile *surrounding[8] =
      {board[y][x - 1], board[y][x - 2], board[y][x + 1], board[y][x + 2], board[y + 1][x], board[y + 2][x], board[y - 1][x], board[y - 2][x]};

  int shapeOrColour = 0;
 
     int counter = 0;  
     bool valid = false;
     bool horEm = false;
     bool verEm = false;
  while (counter < 5)
  { 
    if (surrounding[counter] != nullptr)
    {  valid = false;
      Colour surColour = surrounding[counter]->getColour();
      Shape surShape = surrounding[counter]->getShape();
       shapeOrColour = 0;
      if (surColour != tile->getColour() && surShape != tile->getShape())
      {
        return false;
      }
      else if (surrounding[counter + 1] != nullptr &&
               surColour == surrounding[counter + 1]->getColour() && surColour == tile->getColour())
      {  
        std::cout << "Place ONE" << counter<< std::endl;
        if (surrounding[counter + 2] == nullptr)
        { std::cout << "run 1" << counter<< std::endl;
          valid = true;
        }
        else if (surrounding[counter + 2]->getColour() == surColour)
        { std::cout << "run 2" << counter<< std::endl;
          shapeOrColour = 1;
        }
      }
      else if (surrounding[counter + 1] != nullptr &&
               surShape == surrounding[counter + 1]->getShape() && surShape == tile->getShape())
      { std::cout << "Place TWO" << counter<< std::endl;    
        
        if (surrounding[counter + 2] == nullptr)
        { std::cout << "run 3" << counter<< std::endl;
          valid = true;
        }
        else if (surrounding[counter + 2]->getShape() == surShape )
        { std::cout << "run FKDASF" << counter<< std::endl;
          shapeOrColour = 2;
        }
      }
      else if (surrounding[counter+2] != nullptr)
      { std::cout << "Place THREE" << counter<< std::endl;
        if ( shapeOrColour == 2 &&
          (surrounding[counter + 2]->getShape() == surShape) && (surrounding[counter + 3]->getShape() == surShape ))
        { std::cout << "run 71234" << counter<< std::endl;
          valid =  true;
        }
        else if (shapeOrColour == 1 &&
          (surrounding[counter + 2]->getColour() == surShape) && (surrounding[counter + 3]->getColour() == surShape ))
        { std::cout << "run 6" << counter<< std::endl;
          valid = true;
        }
      } else if (surrounding[counter + 2] == nullptr && counter == 0 ) {
        std::cout << "run  4" << counter<< std::endl;
        horEm = true;
      } else if (surrounding[counter + 2] != nullptr && counter == 4) {
        std::cout << "run  15353236" << counter<< std::endl;
        verEm = true;
        valid = true;
      }

    } 
    else if (surrounding[counter+2] != nullptr && surrounding[counter+3] != nullptr) {
      if ( surrounding[counter + 2]->getShape() == tile->getShape() &&
          (surrounding[counter + 2]->getShape() == surrounding[counter + 3]->getShape()))
        { std::cout << "run 7" << counter<< std::endl;
          valid = true;
        }
        else if (surrounding[counter + 2]->getColour() == tile->getColour() &&
          (surrounding[counter + 2]->getColour() == surrounding[counter + 3]->getColour()))
        { std::cout << "run 8" << counter<< std::endl;
          valid=  true;
        }
    } else if (surrounding[counter+2] != nullptr && surrounding[counter+3] == nullptr) {
     
      if ( surrounding[counter + 2]->getShape() == tile->getShape())
        { std::cout << "run 9" << counter<< std::endl;
          valid = true;
        }
        else if (surrounding[counter + 2]->getColour() == tile->getColour())
        { std::cout << "run 10" << counter<< std::endl;
          valid = true;
        }
    
    }  
    counter += 4;
  }
  
  if (board[y][x] != nullptr) {
    return false;
  }
  if(horEm == true && verEm == false) {
    std::cout << "run  4131" << counter<< std::endl;
    return true;
  }

  return valid;
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
int QwirkleGame::trendCheck(int y, int x, Tile* tile){
 
 int hor1,hor2 = 0;
 int ver1,ver2 = 0;
 int finV,finH =0;
 Tile *temp1,*temp2,*temp3,*temp4 = nullptr;

  for (int j = 1; j < 3; j++)
  {
    if(j == 1) {
     temp1 = board[y][x - j];
     temp2 = board[y][x + j];
     temp3 = board[y-j][x];
     temp4 = board[y+j][x];
    } 

    
    if (board[y][x - j] != nullptr && temp1 != nullptr )  
    {
      if (board[y][x - j]->getColour() == temp1->getColour()){
        hor1 = 1;
      } else if (board[y][x - j]->getShape() == temp1->getShape()){
        hor1 = 2;
      }
    }  
    if (board[y][x + j] != nullptr  && temp2 != nullptr) {
      
       if (board[y][x + j]->getColour() == temp2->getColour()){
        hor2 = 1;
      } else if (board[y][x + j]->getShape() == temp2->getShape()){
        hor2 = 2;
      }
    }
    if (board[y + j][x] != nullptr  && temp3 != nullptr)
    {
       if (board[y+j][j]->getColour() == temp3->getColour()){
        ver1 = 1;
      } else if (board[y+j][x]->getShape() == temp3->getShape()){
        ver1 = 2;
      }
    }
    if (board[y-j][x] != nullptr  && temp4 != nullptr) {
       if (board[y-j][x]->getColour() == temp4->getColour()){
        ver2 = 1;
       } else if (board[y-j][x]->getShape() == temp4->getShape()){
        ver2 = 2;
      }
    }
  }

if (hor1 == 1 && hor1 == hor2) {
 finH = 1;
} else if ((hor1 == 1 && hor2 == 0) || (hor1 == 0 && hor2 == 1 )){
finH = 1;
} else if ((hor1 == 2 && hor2 == 0) || (hor1 == 0 && hor2 == 2 )){
finH = 2;
} else if (hor1 == 2 && hor1 == hor2) {
finH = 2;
} finH = 0;

if (ver1 == 1 && ver1 == hor2) {
 finV = 1;
} else if ((ver1 == 1 && ver2 == 0) || (ver1 == 0 && ver2 == 1 )){
finV = 1;
} else if ((hor1 == 2 && hor2 == 0) || (hor1 == 0 && hor2 == 2 )){
finV = 2;
} else if (hor1 == 2 && hor1 == hor2) {
finV = 2;
} else finV = 0;

return finV + finH;


}