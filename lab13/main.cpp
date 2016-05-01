/*
 * Dustin Horvath
 * Pairing Heap
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

// Used for pretty output
#include <iomanip>
#include <vector>
#include <queue>
// End pretty libraries

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

    if(elem == nullptr){
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
  }

  void link(Node* &first, Node* &second){
    if(second == nullptr){
      return;
    }
    if(second -> getValue() < first -> getValue()){
      // second takes the place of first and pushes first down
      second -> setPrev(first -> getPrev());
      first -> setPrev(second);
      // first adopts seconds left child as sibling. Pushes second's left
      // child out to right
      first -> setSibling(second -> getLeft());
      // Point the new sibling back at first if it exists
      if(first -> getSibling() != nullptr){
        first -> getSibling() -> setPrev(first);
      }
      second -> setLeft(first);
      first = second;
    }
    else{
      // else do the opposite, where second gets pushed down and becomes
      // first's left child
      second -> setPrev(first);
      first -> setSibling(second -> getSibling());
      if(first -> getSibling() != nullptr){
        first -> getSibling() -> setPrev(first);
      }
      second -> setSibling(first -> getLeft());
      if(second -> getSibling() != nullptr){
        second -> getSibling() -> setPrev(second);
      }
      first -> setLeft(second);
    }

  }

  Node* merge(Node* sibling){
    
    if (sibling -> getSibling() == nullptr){
      return sibling;
    }
    
    Node* nodes[MAXNODES];
    
    // Count siblings
    int count = 0;
    for (; sibling != nullptr; count++){
      nodes[count] = sibling;
      sibling -> getPrev() -> setSibling(nullptr);
      sibling = sibling -> getSibling();
    }
    
    nodes[count] = nullptr;
    int i = 0;
    for (i = 0; i + 1 < count; i += 2){
      link(nodes[i], nodes[i + 1]);
    }
    int j = i - 2;
    if (j == count - 3)
      link (nodes[j], nodes[j + 2]);
    for (; j >= 2; j -= 2)
      link(nodes[j - 2], nodes[j] );
    return nodes[0];

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
      if(current -> getLeft()){
        q.push(current -> getLeft());
        nextchildren++;
      }
      std::cout << current -> getValue() << " ";
      // if it has a sibling, iterate to it
      if(current -> getSibling()){
        current = current -> getSibling();
      }
      // if it doesn't have siblings and there are more children in the row, 
      // get a another child from the row
      else if(curchildren > 0){
        std::cout << "    ";
        curchildren--;
        current = q.front();
        q.pop();
      }
      // if no more children in row (curchildren == 0), then move down a row
      // and make curchildren = nextchildren
      else{
        // also, this uses up one of the children
        curchildren = nextchildren;
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
/*
    while(current != nullptr){
      if(current -> getPrev() != nullptr){
        std::cout << current -> getPrev() -> getValue() << ": ";
      }
      
      do{
        std::cout << current -> getValue() << " ";
        if(current->getLeft()){
          array[index] = current->getLeft();
          index++;
        }
        current = current->getSibling();
      }while (current);
      std::cout << "\n";
      current = array[head];
      head++;
    }
*/
      
  }





};


int main(int argc, char *argv[]){

  PairingHeap heap = PairingHeap();

  std::random_device rd;
  std::mt19937 gen(rd());
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








