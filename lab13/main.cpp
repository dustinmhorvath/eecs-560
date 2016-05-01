/*
 * Dustin Horvath
 * Pairing Heap
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>

// Used for testing
#include <random>
// End testing

// Used for pretty output
//#include <iomanip>
//#include <vector>
#include <queue>
// End pretty libraries

#define SEED 10
#define MAXNODES 100

class Node{
private:
  int m_value;
  Node* m_left;
  Node* rs;
  Node* prev;

public:
  Node(int value){
    m_value = value;
    m_left = nullptr;
    rs = nullptr;
    prev = nullptr;
  }

  void setLeft(Node* node){
    m_left = node;
  }

  void setSibling(Node* node){
    rs = node;
  }

  void setPrev(Node* node){
    prev = node;
  }

  Node* getLeft(){
    return m_left;
  }

  Node* getSibling(){
    return rs;
  }

  Node* getPrev(){
    return prev;
  }

  int getValue(){
    return m_value;
  }


};


class PairingHeap{

  int size;
  Node* elem;

public:

  PairingHeap(){
    size = 0;
    elem = nullptr;
  }

  Node* findmin(){
    return elem;
  }

  Node* insert(int value){
    Node* temp = new Node(value);
    /*    if(elem == nullptr){
          elem = temp;
          size++;
          }
          else{
          if(elem -> getValue() > value){
          temp -> setLeft(elem);
          elem -> setPrev(temp);
          elem = temp;
          size++;
          }
          else{
          if(elem -> getLeft()){
          elem -> getLeft() -> setPrev(temp);
          temp -> setSibling(elem -> getLeft());
          }
          elem -> setLeft(temp);
          temp -> setPrev(elem);
          size++;
          }
          }
          */


    if( !elem ){
      elem = temp;
    }
    else
      compareAndLink( elem, temp );
    return temp;   

  }

  void compareAndLink(Node* &first, Node* &second){

    if(!second){
      return;
    }

    if( second -> getValue() < first -> getValue() ){
      second -> setPrev(first -> getPrev());
      first -> setPrev(second);
      first -> setSibling(second -> getLeft());
      if( first -> getSibling() != nullptr ){
        first -> getSibling() -> setPrev(first);
      }
      second -> setLeft(first);
      first = second;
    }
    else{
      second -> setPrev(first);
      first -> setSibling(second -> getSibling());
      if( first -> getSibling() != nullptr ){
        first -> getSibling() -> setPrev(first);
      }
      second -> setSibling(first -> getLeft());
      if( second -> getSibling() != nullptr ){
        second -> getSibling() -> setPrev(second);
      }
      first -> setLeft(second);
    }
  }



  void levelorder(){
    std::queue<Node*> q;

    int level = 0;
    int nextchildren = 0;
    int curchildren = 0;
    Node* current = elem;
    std::cout << "Level " << level << ": ";
    while(current != nullptr){
      // if it has a child, push it on and increment the children in next row
      std::cout << current -> getValue();
      if(current -> getLeft()){
        q.push(current -> getLeft());
        std::cout << "____";
        // increment the number of children in next row
        nextchildren++;
      }
      std::cout << " ";
      // if it has a sibling, iterate to it
      if(current -> getSibling()){
        current = current -> getSibling();
      }
      // if it doesn't have siblings and there are more children in the row, 
      // get another child from the row
      else if(curchildren > 0){
        std::cout << "    ";
        // this consumes a current row child
        curchildren--;
        current = q.front();
        q.pop();
      }
      // if no more children in row (curchildren == 0), then move down a row
      // and make curchildren = nextchildren
      else if(curchildren == 0){
        // also, this uses up one of the children
        curchildren = nextchildren - 1;
        // set next row of children to zero, since we've "moved down" a row
        nextchildren = 0;
        current = q.front();
        q.pop();
        // increment our current level
        level++;
        std::cout << "\n";
        if(current){
          std::cout << "Level " << level << ": ";
        }
      }

    }

  }





};


int main(int argc, char *argv[]){

  PairingHeap heap = PairingHeap();

  std::random_device rd;
  std::mt19937 gen(rd());
  //std::mt19937 gen(SEED);
  std::uniform_int_distribution<> dis(50, 200);
  int temp;

  for(int i = 0; i < 50; i++){
    temp = dis(gen);
    heap.insert(temp);
  }

  heap.levelorder();


  std::cout << "\n\nExiting...\n";
  return 0;
}








