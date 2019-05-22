
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

#include "LinkedList.h"
#include "QwirkleGame.h"

#define EXIT_SUCCESS 0
//test
void newGame();
void saveGame(QwirkleGame *g, std::string string2);
void loadGame();
void studentInfo();
void runGame(QwirkleGame *g);

std::string input;
std::string playerOne;
std::string playerTwo;
std::string place;
std::string place2;
std::string fileName;
std::string line;

std::ofstream outfile;
std::ifstream infile;


int playerTurn = 0;

int main(void)
{
  std::cout << std::endl;
  std::cout << "Welcome to Qwirkle!"
            << "\n"
            << "------------------------------------" << std::endl;
  while (input != "4")
  {
    std::cout
        << "Menu"
        << "\n"
        << "----"
        << "\n"
        << "1. New Game"
        << "\n"
        << "2. Load Game"
        << "\n"
        << "3. Show student information"
        << "\n"
        << "4. Quit" << std::endl;

    std::cin >> input;
    if (input == "1")
    {
      newGame();
    }
    else if (input == "2")
    {
      loadGame();
    }
    else if (input == "3")
    {
      studentInfo();
    }
    else if (input == "4")
    {
      std::cout << "See you next time!" << std::endl;
    }
    else
    {
      std::cout << "Warning: Invalid number." << std::endl;
    }
  }
  return EXIT_SUCCESS;
}

void newGame()
{
  std::cout << std::endl;
  std::cout << "Starting a New Game" << std::endl;
  std::cout << std::endl;

  bool capsn1 = false;
  bool capsn2 = false;

  //Code duplication, we need to create a method for it
  std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
  while (capsn1 == false)
  {
    bool temp = true;

    std::cin >> playerOne;
    std::cout << std::endl;
    for (size_t i = 0; i < playerOne.length(); i++)
    {
      if (!isupper(static_cast<unsigned char>(playerOne[i])))
      {
        temp = false;
      }
    }
    if (temp == false)
    {
      std::cout << "Invalid Input. Please enter your name in UPPERCASE" << std::endl;
    }
    capsn1 = temp;
  }

  std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
  //Code duplication, we need to create a method for it
  while (capsn2 == false)
  {
    bool temp = true;
    std::cin >> playerTwo;
    std::cout << std::endl;
    for (size_t i = 0; i < playerTwo.length(); i++)
    {
      if (!isupper(static_cast<unsigned char>(playerTwo[i])))
      {
        temp = false;
      }
    }
    if (temp == false)
    {
      std::cout << "Try Again, your name was not in uppercase" << std::endl;
    }
    capsn2 = temp;
    if (playerTwo == playerOne)
    {
      std::cout << "Name has been taken, please try again" << std::endl;
      capsn2 = false;
    }
  }
  std::cout << "Let's Play!" << std::endl;
  std::cout << std::endl;

  //Initializing the QwirkleGame, in here the bag is created and board is generated
  QwirkleGame *g = new QwirkleGame();
  //Filling the bag
  g->getBag()->fillBag();

  //Adding players -> However, we need to alter this as the amount of players is dynamic for milestone 3
  g->addPlayer(playerOne);
  g->addPlayer(playerTwo);

  //Shuffling the bag
  g->getBag()->shuffleBag();
  g->fillPlayerHands();

  //GameEngine commences

  runGame(g);

  /*
    **PSEUDOCODE**
    REPEAT until bag size is empty OR player hand is empty
    DISPLAY the current player's turn
    DISPLAY the scoreboard
    DISPLAY the Qwirkle board
    DISPLAY the current player's hand

    TAKE IN current player's input
      IF PLACE
        PLACE tile on board
        REMOVE tile from player hand
      IF REPLACE
        REMOVE tile from player hand and add it to back of the bag linked list
        TAKE first tile from bag
        PLACE in player hand

    END OF current player's turn

  */
}

void saveGame(QwirkleGame *g, std::string string2)
{
  outfile.open(string2 + ".txt");

  //Iterating through each of the players
  for (Player *p : g->getPlayers())
  {
    outfile << p->getName() << "\n";
    outfile << p->getScore() << "\n";

    for (int i = 0; i < p->getHand()->returnSize(); i++)
    {
      if (i != p->getHand()->returnSize() - 1)
      {
        outfile << p->getHand()->findNode(i)->getTile()->getTileDets() << ", ";
      }
      else
      {
        outfile << p->getHand()->findNode(i)->getTile()->getTileDets();
      }
    }
    //Current player details has been written out to the file
    outfile << "\n";
  }

  outfile << g->getBoard();

  for (int i = 0; i < g->getBag()->getList()->returnSize(); i++)
  {
    if (i != g->getBag()->getList()->returnSize() - 1)
    {
      outfile << g->getBag()->getList()->findNode(i)->getTile()->getTileDets() << ", ";
    }
    else
    {
      outfile << g->getBag()->getList()->findNode(i)->getTile()->getTileDets();
    }
  }
  outfile << "\n";
  outfile << g->getCurrentPlayer()->getName();


  outfile.close();

  std::cout << "\n";
  std::cout << "Game successfully saved \n";
  std::cout << "\n";
}

//Method displays loading the game
void loadGame()
{

  int x_count = 0;
  int y_count = 0;
  int loopCount = 0;

  std::cout << "Enter the filename from which to load a game" << std::endl;
  std::cin >> fileName;

  infile.open(" " + fileName + ".txt");

  if (infile)
  {
    std::cout << "File has been loaded" << std::endl;

    QwirkleGame *p = new QwirkleGame();

    int noOfPlayers = 0;
    int counter = 0;

    for (std::string line; getline(infile, line);)
    {
      if (counter == 0 || counter == 3)
      {
        p->addPlayer(line);
        noOfPlayers++;
      }
      if (counter == 1 || counter == 4)
      {
        int score = std::stoi(line);
        p->getPlayers().at(noOfPlayers - 1)->setScore(score);
      }
      //These lines occupy tile contents, whether it is the player's hands or the tiles in the bag
      if (counter == 2 || counter == 5 || counter == 34)
      {
        std::stringstream stream(line);
        std::string tile;

        //These lines occupy players' hands
        if (counter == 2 || counter == 5)
        {
          while (stream >> tile)
          {
            std::cout << tile.at(0) << tile.at(1) << std::endl;
            
            Tile *t = new Tile(tile.at(0), (int)tile.at(1) - 48);

            p->getPlayers().at(noOfPlayers - 1)->getHand()->addNode(t);
            
          }
        }
        //the 33rd line occupy the tiles in the bag
        if (counter == 34)
        {
          while (stream >> tile)
          {
            //I take away 48 because of ascii conversions
            Tile *t = new Tile(tile.at(0), (int)tile.at(1) - 48);
            p->getBag()->getList()->addNode(t);
          }
        }
      }
      //These lines work with the tiles that are on the board
      if (counter >= 8 && counter <= 33)
      {

        std::stringstream stream(line);
        std::string tileOnBoard;

        while (std::getline(stream, tileOnBoard, '|'))
        {
          if (loopCount == 0)
          {
            x_count--;
            loopCount++;
          }

          if (tileOnBoard[0] != ' ' && tileOnBoard[1] != ' ' && x_count != -1)
          {
            Tile *t = new Tile(tileOnBoard[0], (int)tileOnBoard[1] - 48);
            p->setBoard(x_count, y_count, t);
          }

          x_count++;

          if (x_count == 26)
          {
            x_count = 0;
            y_count++;
            loopCount = 0;
          }
        }
      }

      if (counter == 35)
      {
        for (int i = 0; i < p->getPlayers().size(); i++)
        {
          if (p->getPlayers()[i]->getName() == line)
          {
            playerTurn = i;
            p->setCurrentPlayer(p->getPlayers()[i]);
          }
        }
      }

      counter++;
    }

    //p->printBoard();

    infile.close();

    std::cout << std::endl;
    std::cout << "Qwirkle game successfully loaded" << std::endl;
    std::cout << std::endl;

    runGame(p);
  }
  else
  {
    std::cout << "File could not be loaded." << std::endl;
  }
}

void runGame(QwirkleGame *g)
{

  while (!g->gameFinished())
  {
      //This if loop will only be called at new game, not load game as load game sets the player's turn
      if(g->getCurrentPlayer() == nullptr)
      {
        //Sets to be the first player in the loop
        Player *player = g->getPlayers()[0];
        g->setCurrentPlayer(player);
      }

        //Displaying the current player's turn
        std::cout << g->getCurrentPlayer()->getName() << ", it's your turn \nNeed some help? If so, type 'help'!" << '\n'
                  << std::endl;

        //Displaying the scoreboard
        for (Player *playerlist : g->getPlayers())
        {
          std::cout << playerlist->getName() << "'s score: " << playerlist->getScore() << std::endl;
        }

        //Newline for neatness
        std::cout << std::endl;

        //Printing the board for viewing
        g->printBoard();
        std::cout << std::endl;

        //Printing the current players hand
        std::cout << std::endl; //2 newlines for neatness
        std::cout << "Your hand is.." << std::endl;
        g->getCurrentPlayer()->printHand();
        std::cout << std::endl;

        bool moveMade = false;

        while (moveMade == false)
        {
          //Reading in player input
          std::string string1, string2;
          std::getline(std::cin >> string1, string2);
          for (int i = 0; i < string1.length(); i++)
          {
            std::tolower(string1[i]);
          }

          //If statement to be embeded here for PLACING, REPLACING or SAVING GAME
          if (string1 == "place")
          {
            moveMade = g->placeTile(string2);
            if (!moveMade)
            {
              std::cout << "Invalid move. Please enter a valid move." << std::endl;
            }
          }
          else if (string1 == "replace")
          {
            moveMade = g->replaceTile(string2);
            if (!moveMade)
            {
              std::cout << "Invalid move. Please enter a valid move." << std::endl;
            }
          }
          else if (string1 == "save")
          {
            saveGame(g, string2);
            std::cout << "It is still your turn, " + g->getCurrentPlayer()->getName() << "\n" << std::endl;
            std::cout << "Your hand is.." << std::endl;
            g->getCurrentPlayer()->printHand();
            std::cout << std::endl;
          }
          else if( string1 == "help")
          {
            std::cout << std::endl;
            std::cout << "                                                       HELP!" << std::endl;
            std::cout << "----------------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << "place   <tile> at <coordinate> - will place your chosen tile on the board, counts as a move" << std::endl;
            std::cout << "replace <tile>                 - your tile will be placed in the bag and you will draw a new tile, counts as a move" << std::endl;
            std::cout << "save <file name>               - your tile will be placed in the bag and you will draw a new tile, DOES NOT count as a move" << std::endl;
            std::cout << "----------------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << std::endl;
            std::cout << "It is still your turn, " + g->getCurrentPlayer()->getName() << "\nPlease make a move!" << std::endl;
          }
          else
          {
            std::cout << "Invalid command. Please enter a valid command." << std::endl;
          }
        }
        //Reprinting the board
        std::cout << std::endl;
        g->printBoard();
        std::cout << std::endl;

        //Alternating between the players and ensuring that the vector does not go out of bounds
        if(playerTurn == g->getPlayers().size()-1)
        {
          playerTurn = 0;
          g->setCurrentPlayer(g->getPlayers()[playerTurn]);
        }
        else
        {
          playerTurn++;
          g->setCurrentPlayer(g->getPlayers()[playerTurn]);
        }
    }


    //The while loop ends when the game has finished
    std::cout << "Game over!" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    int temp = 0;
    std::string winner;

    //Iterates to find who has the highest score 
    for(Player *p: g->getPlayers())
    {
      if(p->getScore() == temp)
      {
        winner = "Draw";
      }
      else if(p->getScore() > temp)
      {
        temp = p->getScore();
        winner = "Player " + p->getName() + " wins.";
      }

      std::cout << "Score for " << p->getName() << ": " << p->getScore() << std::endl; 
    }

    std::cout << winner << std::endl; 
}

//Method displays student info
void studentInfo()
{
  std::cout << std::endl;
  std::cout << "------------------------------------" << std::endl;
  std::cout << "Name: Don Phuu"
            << "\n"
            << "Student ID: s3716808"
            << "\n"
            << "Email: s3716808@student.rmit.edu.au"
            << "\n"
            << std::endl;
  std::cout << "Name: David Vo"
            << "\n"
            << "Student ID: s3723069"
            << "\n"
            << "Email: s3723069@student.rmit.edu.au"
            << "\n"
            << std::endl;
  std::cout << "Name: Peter Pham"
            << "\n"
            << "Student ID: s3717828"
            << "\n"
            << "Email: s3717828@student.rmit.edu.au"
            << "\n"
            << std::endl;
  std::cout << "Name: Jamal Ibaida"
            << "\n"
            << "Student ID: s3723430"
            << "\n"
            << "Email: s3723430@student.rmit.edu.au" << std::endl;
  std::cout << "------------------------------------" << std::endl;
  std::cout << std::endl;
}