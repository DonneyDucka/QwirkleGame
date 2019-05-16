
#include "LinkedList.h"

LinkedList::LinkedList() :
    head(nullptr),
    current(nullptr),
    tail(nullptr),
    temp(nullptr)
{
}

LinkedList::~LinkedList()
{
}

void LinkedList::addNode(Tile* a)
{
    NodePtr node = new Node(a, nullptr);
    /* checks if the list is already empty
     * then go through the list, using next to
     * point to the next node
     * else, if empty, make the head the node
     */
    if (head != nullptr)
    {
       tail->setNext(node);
       tail = node;
    }
    else
    {
      head = node;
      tail = node;
    }
    std::cout << "node added" << std::endl;
    delete node;
}//end of addNode
/* find node for the random int to pull out */
Tile* LinkedList::findNode(int f)
{
  current = head;
  int count = 0;

    while (count < f && current != nullptr)
    {
      current = current->getNext();
      count++;
    }
    if (current == nullptr)
    {
    Tile* t = new Tile('P', 1);
    return t;
    }
    else
    {
    Tile* t = current->getTile();
    return t;
    }
}
/* delete selected tile pointer */
void LinkedList::deleteNode(Tile* d)
{
    NodePtr del = nullptr;

    temp = head;
    current = head;

    while (current != nullptr && current->getTile() != d)
    {
        temp = current;
        current = current->getNext();
    }
    if (current == NULL)
    {
      std::cout << "Debug Warning: " << d << " could not be found." << std::endl;
      delete del;
    }
    else if (current != nullptr && current->getTile() == d)
    {
      //TODO :: rewrite this shiet
        del = current;
        current = current->getNext();
        temp = current;
        if (del == head)
        {
            head = head->getNext();
            temp = nullptr;
        }
        delete del;
    }

}

int LinkedList::returnSize()
{
  int count = 0;

  if (head != nullptr)
  {
      current = head;
      count++;
      while (current->getNext() != nullptr)
      {
        current = current->getNext();
        count++;
      }
      count--;
  }

  return count;
}

/* prints everything in the linked list */
void LinkedList::printLine()
{
      current = head;

      while (current->getNext() != nullptr)
      {
          std::cout << current->getTile()->printTile() << std::endl;
          current = current->getNext();
      }
}
