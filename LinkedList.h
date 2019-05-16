
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <iostream>
#include "Node.h"
#include "Tile.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   //only adds node at the end
   void addNode(Tile* a);
   //find the Node
   Tile* findNode(int f);
   //only deletes node of where it is
   void deleteNode(Tile* d);

   int returnSize();

   void printLine();



private:
   NodePtr head;
   NodePtr current;
   NodePtr tail;
   NodePtr temp;
};

#endif // ASSIGN2_LINKEDLIST_H
