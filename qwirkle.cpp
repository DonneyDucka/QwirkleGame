
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
    std::cout << "adding player one" << std::endl;
    g->addPlayer(playerOne);
    std::cout << "player one added" << std::endl;
    std::cout << "adding player two" << std::endl;
    g->addPlayer(playerTwo);
    std::cout << "player two added" << std::endl;
    std::cout << "attemping to print board" << std::endl;

    g->printBoard();
    std::cout << "printing board added" << std::endl;

        // std::cout << "attempting to add a bag" << std::endl;
        // Bag* b = new Bag();
        // std::cout << "bag added" << std::endl;
        //
        // b->fillBag();
        // std::cout << "filled bag" << std::endl;
        // b->getList()->printLine();
        std::cout << "print size" << std::endl;
        std::cout << g->getBag()->getSize() << std::endl;
        std::cout << "lalallalalalal" << std::endl;
        g->getBag()->getList()->printLine();

    std::cout << "now deleting game board" << std::endl;
    delete g;
    // delete b;
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
