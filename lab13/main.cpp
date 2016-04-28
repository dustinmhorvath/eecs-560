/*
 * Dustin Horvath
 * Pairing Heap
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>

// Used for pretty output
#include <iomanip>
#include <vector>
#include <queue>
// End pretty libraries

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

Node* elem;

public:

  PairingHeap(){
    elem = nullptr;
  }

  Node* findmin(){
    return elem;
  }

  Node* insert(int value){
    Node* tempnode = new Node(value);
    if(elem == nullptr){
      elem = tempnode;
    }
    else{
      link(elem, tempnode);
    }
    return tempnode;
  }

  void link(Node* &first, Node* &second){
    if(second == nullptr){
      return;
    }
    if(second -> getValue() < first -> getValue()){
      second -> setPrev(first -> getPrev());
      first -> setPrev(second);
      first -> setSibling(second -> getLeft());
      if(first -> getSibling() != nullptr){
        first -> getSibling() -> setPrev(first);
      }
      second -> setLeft(first);
      first = second;
    }
    else{
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
    static std::vector<Node*> treeArray(5);
    // Count siblings
    int count = 0;
    for (; sibling != nullptr; count++){
      if (count == treeArray.size()){
        treeArray.resize(count * 2);
      }
      treeArray[count] = sibling;
      sibling -> getPrev() -> setSibling(nullptr);
      sibling = sibling -> getSibling();
    }
    if (count == treeArray.size()){
      treeArray.resize(count + 1);
    }
    treeArray[count] = nullptr;
    int i = 0;
    for (i = 0; i + 1 < count; i += 2){
      link(treeArray[i], treeArray[i + 1]);
    }
    int j = i - 2;
    if (j == count - 3)
      link (treeArray[j], treeArray[j + 2]);
    for (; j >= 2; j -= 2)
      link(treeArray[j - 2], treeArray[j] );
    return treeArray[0];

  }

  void levelorder(){
    if (elem != nullptr) {
      std::cout << "Printing level order..." << "\n";
      int height = 0;
      Node* temp;
      std::queue<Node*> siblings;
      std::queue<Node*> children;
      siblings.push(elem);
      while (!siblings.empty() || !children.empty()) {
        if(!siblings.empty()){
          temp = siblings.front();
          siblings.pop();
          std::cout << temp -> getValue() << " ";
          if(temp -> getSibling() != nullptr){
            siblings.push(temp -> getSibling());
          }
          if(temp -> getLeft() != nullptr){
            children.push(temp -> getLeft());
          }
        }
        else if(!children.empty()){
          std::cout << "\n";
          temp = children.front();
          children.pop();
          std::cout << temp -> getValue() << " ";
          if(temp -> getSibling() != nullptr){
            siblings.push(temp -> getSibling());
          }
          if(temp -> getLeft() != nullptr){
            children.push(temp -> getLeft());
          }

        }


      }
      
    }
    else {
      std::cout << "No elements in heap\n";
    }
  }





};


int main(int argc, char *argv[]){

  PairingHeap heap = PairingHeap();
  heap.insert(5);
  heap.insert(10);
  heap.insert(18);
  heap.insert(26);
  heap.insert(1);
  heap.insert(90);
  heap.insert(75);
  heap.insert(2);
  heap.insert(5);
  heap.insert(12);
  heap.levelorder();


  std::cout << "\n\nExiting...\n";
  return 0;
}








