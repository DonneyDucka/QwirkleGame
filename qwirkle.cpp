
#include <string>
#include <iostream>
#include "LinkedList.h"
#include "QwirkleGame.h"

#define EXIT_SUCCESS    0
//test
void newGame();
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
    // LinkedList* list = new LinkedList();
    // delete list;
    std::cout << std::endl;
    std::cout << "Welcome to Qwirkle!"  << "\n"
              << "--------------------" << std::endl;

  while (input != "4")
  {
    std::cout
     << "Menu" << "\n"
     << "----" << "\n"
     << "1. New Game" << "\n"
     << "2. Load Game" << "\n"
     << "3. Show student information" << "\n"
     << "4. Quit" << std::endl;

    std::cin >> input;
    if (input == "1") {
      newGame();
    }
    else if (input == "2") {
      loadGame();
    }
    else if (input == "3") {
      studentInfo();
    }
    else if (input == "4") {
      std::cout << "See you next time!" << std::endl;
    }
    else {
      std::cout << "Warning: Invalid number." << std::endl;
    }
  }
     return EXIT_SUCCESS;
  } //end of main

  void newGame()
  {
    std::cout << std::endl;
    std::cout << "Starting a New Game" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
    std::cin >> playerOne;
    std::cout << std::endl;

    std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
    std::cin >> playerTwo;
    std::cout << std::endl;

    std::cout << "Let's Play!" << std::endl;
    std::cout << std::endl;

    QwirkleGame* g = new QwirkleGame();
    
    //ADDING PLAYERS
    g->addPlayer(playerOne);
    g->addPlayer(playerTwo);
     
     //Shuffling the bag
    g->getBag()->shuffleBag();
    g->fillPlayerHands();

    while( g->getBag()->getSize()!=0) 
    {
      for (Player* player : g->getPlayers()) 
       {

        std::cout << player->getName() << ", it's your turn" << '\n' <<std::endl;

         //Displaying the scoreboard 
        for(Player* playerlist: g-> getPlayers()) {

          std::cout << playerlist->getName()<<"'s score: " << playerlist->getScore() << std::endl;
        }

        g->printBoard();

        std::cout << std::endl;

        std::cout << "Your hand is.." << std::endl;
        
        player->printHand();
       }
       break;
    }
  }

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

  void studentInfo()
  {
    std::cout << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Name: Don Phuu" << "\n" << "Student ID: s3716808" << "\n" << "Email: s3716808@student.rmit.edu.au" << "\n" << std::endl;
    std::cout << "Name: David Vo" << "\n" << "Student ID: s3723069" << "\n" << "Email: s3723069@student.rmit.edu.au" << "\n" << std::endl;
    std::cout << "Name: Peter Pham" << "\n" << "Student ID: s3717828" << "\n" << "Email: s3717828@student.rmit.edu.au" << "\n" << std::endl;
    std::cout << "Name: Jamal Ibaida" << "\n" << "Student ID: s3723430" << "\n" << "Email: s3723430@student.rmit.edu.au" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << std::endl;
  }
