
#ifndef ASSIGN2_BAG_H
#define ASSIGN2_BAG_H

#include <cstdlib>
#include "LinkedList.h"
#include "Tile.h"

class Bag {
public:

Bag();

void fillBag();

Tile* pickFromBag();
LinkedList* getList();
int getSize();
private:
  //must be stored as an ordered linked list
LinkedList* tileList;

};

#endif // ASSIGN2_BAG_H
