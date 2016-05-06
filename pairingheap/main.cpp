/*
 * Dustin Horvath
 * Pairing Heap
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>

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

    if( elem == nullptr ){
      return elem = temp;
    }
    else{
      compareAndLink( elem, temp );
    }
    size++;

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

  int deleteMin(){
    if (elem == nullptr){
      // Return a magic number for now
      return -111;
    }

    // Gets the root of the tree
    Node* prevroot = findmin();
    if (elem -> getLeft() == nullptr){
      elem = nullptr;
    }
    else{
      // New root is the result of combining its children
      elem = combine( prevroot -> getLeft());
    }

    int value = prevroot -> getValue();
    delete prevroot;
    size--;
    return value;
  }

  Node* combine(Node *first){
    if (first -> getSibling() == nullptr){
      return first;
    }
    // Make an array to hold all the siblings
    Node* list[100];
    int numSiblings;

    // Count siblings while putting them each in the array
    for (numSiblings = 0; first != nullptr; numSiblings++){
      list[numSiblings] = first;
      // For now they're not siblings anymore
      first -> getPrev() -> setSibling(nullptr);
      // Move across the linked list of siblings
      first = first -> getSibling();
    }


    list[numSiblings] = nullptr;
    int i = 0;
    // Do first pass
    for (i = 0; i + 1 < numSiblings; i += 2){
      compareAndLink(list[i], list[i + 1]);
    }
    int j = i - 2;
    if (j == numSiblings - 3){
      compareAndLink ( list[j], list[j+2] );
    }
    // Do second pass
    for (; j >= 2; j -= 2){
      compareAndLink( list[j-2], list[j] );
    }
    // return the item at the new head
    return list[0];
  }



  void levelorder(){
    std::queue<Node*> q;
    if(elem == nullptr){
      std::cout << "No heap to print.\n";
      return;
    }

    int level = 0;
    int nextchildren = 0;
    int curchildren = 0;
    Node* current = elem;
    std::cout << "Level " << level << ": ";
    while(current != nullptr){
      std::cout << current -> getValue();
      // if it has a child, push it on and increment the children in next row
      if(current -> getLeft() != nullptr){
        q.push(current -> getLeft());
        std::cout << "_V_ ";
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

  if(argc > 1){
    if(std::string(argv[1]) == "random"){  
      std::istringstream ss(argv[2]);
      int number;
      if (!(ss >> number)){
        std::cout << "Invalid number " << argv[2] << '\n';
      }
      //int number = argv[2];
      std::random_device rd;
      std::mt19937 gen(rd());
      //std::mt19937 gen(SEED);
      std::uniform_int_distribution<> dis(1, 200);
      int temp;

      for(int i = 0; i < number; i++){
        temp = dis(gen);
        heap.insert(temp);
      }

      heap.levelorder();
    }
    else{

      std::ifstream infile(argv[1]);
      std::string line;

      while (std::getline(infile, line)){
        std::istringstream iss(line);
        int n;

        while (iss >> n){
          std::cout << "Inserting " << n << " into the heap.\n";
          heap.insert(n);
        }

      }

      heap.levelorder();

    }
  }

  else{
    std::cout << "\nYou can provide this program a list of whitespace-delimited \n";
    std::cout << "values from which to build the pairingheap. Ex: './test insert.txt'\n";
    std::cout << "Alternatively, use './test random INT' to insert a random INT values\n";
    std::cout << "between 1 and 200.\n";
    bool cont = true;
    int option = 3;
    int value = 0;
    while(cont){
      std::cout << "\n1. Insert a new value\n";
      std::cout << "2. Deletemin\n";
      std::cout << "3. Print the current pairingheap\n";
      std::cout << "4. Exit\n";
      std::cout << "Select an option: ";
      std::cin >> option;
      std::cin.clear();

      switch(option){
      case 1:
        std::cout << "Please provide a value to insert: ";
        std::cin >> value;
        std::cin.clear();
        heap.insert(value);
        break;
      case 2:
        value = heap.deleteMin();
        if(value != -111){
          std::cout << "Deleted minimum value " << value << ".\n";
        }
        break;
      case 3:
        heap.levelorder();
        break;

      case 4:
        cont = false;
        break;

      default:
        std::cout << "Invalid input.\n";
        break;

      }

    }
  }

  std::cout << "\nExiting...\n\n";
  return 0;
}








