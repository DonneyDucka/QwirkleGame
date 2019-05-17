
#include "LinkedList.h"

LinkedList::LinkedList() :
    head(nullptr),
    current(nullptr),
    tail(nullptr)
 
{
  numOfNodes = 0;
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
       numOfNodes++;
    }
    else if (head == nullptr)
    {
      head = node;
      tail = node;
      numOfNodes++;
    } else if (head == tail)
    {
      tail->setNext(node);
      tail = node;
      head->setNext(tail);
      numOfNodes++;
    } 
}//end of addNode
/* find node for the random int to pull out */
Node* LinkedList::findNode(int f)
{
 Node* temp = head;
  for(int count = 1; count <= f; ++count) {

   temp = temp->getNext();

  }
  return temp;
}

void LinkedList::addAt(int i, Node* node) {
 

 if ( i > 0 && head != nullptr) { 
 int prev  = i - 1;
 findNode(prev)->setNext(node);
 node->setNext(findNode(i));
 
 numOfNodes++;
 } else if (i == 0 && head != nullptr){
   
   node->setNext(head);
   head = node;
   numOfNodes++;
 } else if (head == nullptr) {
   node->setNext(nullptr);
   head = node;
   tail = node;
    numOfNodes++;
 } else if( i == numOfNodes) {
    node->setNext(nullptr);
    tail->setNext(node);
    tail = node;
    numOfNodes++;
 }

}

void LinkedList::addBack(Tile* data){
  
    Node* newNode = new Node(data, nullptr);
       
       tail->setNext(newNode);
       tail = newNode;
       numOfNodes++;

}
/* delete selected tile pointer */
void LinkedList::deleteNode(int i)
{
   current = head;

    int count = 0;
    
    if (i == 0) {
     head =  head->getNext();
    }

    while(count != i){

     if ((count + 1) == i ) {
       
       findNode(count)->setNext(findNode(i+1));
     }
     count++;
    }

 numOfNodes--;
}

void LinkedList::deleteBack(){

tail = findNode(numOfNodes - 1);
tail->setNext(nullptr);

}

void LinkedList::deleteFront(){
  
   head = head->getNext();
}

int LinkedList::returnSize()
{
 return numOfNodes;
}

/* prints everything in the linked list */
void LinkedList::printLine()
{ 
      current = head;

      while(current->getNext() != nullptr)
      {
          current->getTile()->printTile();
         if(current->getNext()->getNext() != nullptr) 
          {
          std::cout <<", " ;
          }
          current = current->getNext();
      }

      std::cout << std::endl;
}
