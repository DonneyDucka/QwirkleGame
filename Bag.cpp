
#include "Bag.h"

Bag::Bag()
{
  tileList = new LinkedList();
  std::cout << getSize(); //debug
} //END OF CONSTRUCTOR

void Bag::fillBag()
{
    Tile* t;
    Colour c;
    // Iterate through colours
    for (int i = 0; i < 3; i++)
    {
      for (int i = 1; i <= 6; i++)
      {

        c = 'R';
        t = new Tile(c, i);
        tileList->addNode(t);

        c = 'O';
        t = new Tile(c, i);
        tileList->addNode(t);

        c = 'Y';
        t = new Tile(c, i);
        tileList->addNode(t);

        c = 'G';
        t = new Tile(c, i);
        tileList->addNode(t);

        c = 'B';
        t = new Tile(c, i);
        tileList->addNode(t);

        c = 'P';
        t = new Tile(c, i);
        tileList->addNode(t);
      }
    }
    delete t;
}

Tile* Bag::pickFromBag()
{

    int i = rand() % tileList->returnSize();
    Tile* add = tileList->findNode(i);

    tileList->deleteNode(add);
    return add;

}

LinkedList* Bag::getList()
{
  return tileList;
}

int Bag::getSize()
{
  return tileList->returnSize();
}
