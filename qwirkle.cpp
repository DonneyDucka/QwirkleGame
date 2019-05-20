
#include <string>
#include <iostream>
#include <fstream>
#include <ostream>

#include "LinkedList.h"
#include "QwirkleGame.h"

#define EXIT_SUCCESS 0
//test
void newGame();
void saveGame(std::string string);
void loadGame();
void studentInfo();
std::string input;
std::string playerOne;
std::string playerTwo;
std::string place;
std::string place2;
std::string fileName;

int main(void)
{
  std::cout << std::endl;
  std::cout << "Welcome to Qwirkle!"
            << "\n"
            << "--------------------" << std::endl;
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
  }
  std::cout << "Let's Play!" << std::endl;
  std::cout << std::endl;

  //Initializing the QwirkleGame, in here the bag is created and board is generated
  QwirkleGame *g = new QwirkleGame();

  //Adding players -> However, we need to alter this as the amount of players is dynamic for milestone 3
  g->addPlayer(playerOne);
  g->addPlayer(playerTwo);

  //Shuffling the bag
  g->getBag()->shuffleBag();
  g->fillPlayerHands();
  
  //GameEngine commences

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
  while (g->getBag()->getSize() != 0)
  {
    for (Player *player : g->getPlayers())
    {

      //Displaying the current player's turn
      std::cout << player->getName() << ", it's your turn" << '\n' << std::endl;

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
      std::cout << "Your hand is.." << std::endl;
      player->printHand();

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
        g->placeTile(string2, player);
      }
      else if (string1 == "replace")
      { 
        g->replaceTile(string2, player);
      }
      else if (string1 == "save")
      {
        std::ofstream outfile;
        outfile.open(string2); 
        
        //Iterating through each of the players
        for(Player *p: g->getPlayers())
        {
          outfile << p->getName() << "\n";
          outfile << p->getScore() << "\n";
          
          for(int i = 0; i < p->getHand()->returnSize(); i++)
          {
            if(i != p->getHand()->returnSize() - 1)
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

        for( int i = 0; i < g->getBag()->getList()->returnSize(); i++)
        {
          if( i!= g->getBag()->getList()->returnSize() - 1)
          {
            outfile << g->getBag()->getList()->findNode(i)->getTile()->getTileDets() << ", ";
          }
          else
          {
            outfile << g->getBag()->getList()->findNode(i)->getTile()->getTileDets();
          }
        }

        outfile.close();

        std::cout << "\n";
        std::cout << "Game successfully saved \n";
        std::cout << "\n";

       }

        player->printHand();
      //Reprinting the board
      g->printBoard();
    }
    //DELETE later - no breaks are allowed
    break;
  }
}

//Method displays loading the game
void loadGame()
{
  std::cout << std::endl;
  std::cout << "Enter the filename from which to load a game" << std::endl;
  std::cin >> fileName;

  std::cout << std::endl;
  std::cout << "Qwirkle game successfully loaded" << std::endl;
  std::cout << fileName << std::endl;
  std::cout << std::endl;
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
