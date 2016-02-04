
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Queue.h"

class Node {
public:
  int m_height;
  int m_value;
  Node* m_left;
  Node* m_right;

  Node(){
    m_left = nullptr;
    m_right = nullptr;
    m_value = 0;
    m_height = 0;
  }

  Node(int n){
    m_left = nullptr;
    m_right = nullptr;
    m_value = n;
    m_height = 0;
  }
};

class BinarySearchTree {
private:
  Node* m_root;
public:
  BinarySearchTree(){
    m_root = nullptr;
  }

  bool isEmpty(){
    return m_root == nullptr;
  }

  void insert(int m_value){
    m_root = insert(m_value, m_root);
  }

  int height(Node* node){
    if(!node){
      return -1;
    }
    else{
      return node -> m_height;
    }
  }

  int max(int lhs, int rhs){
    if(lhs > rhs){
      return lhs;
    }
    else {
      return rhs;
    }
  }

  /*
   * Pre: BST constructed
   * Post: Adds a new node containing "value" to the tree.
   * Return: Node pointer
   */
  Node* insert(int value, Node* node){
    // If tree is empty, return
    if (!node){
      node = new Node(value);
    }
    // Compare 'value' to m_value inside node, then pick which subtree to put
    // it in.
    else if (value < node -> m_value){
      node -> m_left = insert(value, node -> m_left);
      // Compare subtree heights. If more then 1 height difference, move
      // subtrees so that that's not the case
      if (height(node -> m_left) - height(node -> m_right) == 2){
        if (value < node -> m_left -> m_value){
          node = rotateWithLeftChild(node);
        }
        else{
          node = doubleWithLeftChild(node);
        }
      }
    }
    else if (value > node -> m_value){
      node -> m_right = insert(value, node -> m_right);
      if (height(node -> m_right) - height(node -> m_left) == 2){
        if (value > node -> m_right -> m_value){
          node = rotateWithRightChild(node);
        }
        else{
          node = doubleWithRightChild(node);
        }
      }
    }

    node -> m_height = max(height(node -> m_left), height(node -> m_right)) + 1;
    return node;
  }

  /*
   * Pre: BinarySearchTree constructed, has children
   * Post: Moves subtrees to balance tree
   * Return: node pointer
   * @note: called by `doubleWithRightChild`, `insert`
   */
  Node* rotateWithLeftChild(Node* node){
    Node* temp = node -> m_left;
    node -> m_left = temp -> m_right;
    temp -> m_right = node;
    node -> m_height = max(height(node -> m_left), height(node -> m_right)) + 1;
    temp -> m_height = max(height(temp -> m_left), node -> m_height) + 1;
    return temp;
  }

  /*
   * Pre: BinarySearchTree constructed, has children
   * Post: Moves subtrees to balance tree
   * Return: node pointer
   * @note: called by `doubleWithLeftChild`, `insert`
   */
  Node* rotateWithRightChild(Node* node){
    Node* temp = node -> m_right;
    node -> m_right = temp->m_left;
    temp -> m_left = node;
    node -> m_height = max(height(node -> m_left), height(node -> m_right)) + 1;
    temp -> m_height = max(height(temp -> m_right), node -> m_height) + 1;
    return temp;
  }

  /*
   * Pre: BST constructed, has children
   * Post: Rotates subtrees
   * Return: node pointer
   * @note: called by `insert`
   */
  Node* doubleWithLeftChild(Node* node){
    node -> m_left = rotateWithRightChild(node -> m_left);
    return rotateWithLeftChild(node);
  }

  /*
   * Pre: BST constructed, has children
   * Post: Rotates subtrees
   * Return: node pointer
   * @note: called by `insert`
   */
  Node* doubleWithRightChild(Node* node){
    node -> m_right = rotateWithLeftChild(node -> m_right);
    return rotateWithRightChild(node);
  }

  // I added this because I needed to print all the values in the tree. It was just by
  //  coincidence that it happened to be pre-order.
  void preOrderHelper(Node* subtree){
    if(subtree != nullptr){
      std::cout << subtree -> m_value << " ";
      preOrderHelper(subtree -> m_left);
      preOrderHelper(subtree -> m_right);
    }
  }

  /*
   * Pre: BST constructed
   * Post: Calls preOrderHelper with m_root to print out values
   * Return: none
   * @note: This function is to abstract the node argument from the caller.
   * Otherwise, they'd have to call it passing the root node every time they
   * print, because preOrderHelper is recursive.
   */
  void printPreOrder(){
    preOrderHelper(m_root);
    std::cout << std::endl;
  }

  /*
   * Pre: BST constructed
   * Post: Prints all the values inside the tree in level-order, by level
   * Return: none
   */
  void printLevelOrder(){
    // Exit if tree is empty
    if (m_root == NULL) { return;}
    // Declare a queue
    Queue<Node*> q;
    // Start with root
    q.enqueue(m_root);
    // Count the rows
    int level = 0;
    while (1){
      int nodeCount = q.size();
      // Exit when queue empty
      if (nodeCount == 0){
        break;
      }
      std::cout << "Level " << level << ": ";
      while (nodeCount > 0){
        // Store so we can get value
        Node* temp = q.peekFront();
        std::cout << temp -> m_value << " ";
        // Pop the front of the queue
        q.dequeue();
        // Push on any children
        if (temp -> m_left){
          q.enqueue(temp -> m_left);
        }
        if (temp -> m_right){
          q.enqueue(temp -> m_right);
        }
        nodeCount--;
      }
      std::cout << std::endl;
      level++;
    }
  }

};

int main(){
  BinarySearchTree tree;

  int size = 10;

  int arr[size];

  std::ifstream file("data2.txt");
  std::string line;

  while(std::getline(file, line)){
    std::stringstream  lineStream(line);
    int value;
    int index = 0;
    while(lineStream >> value){
      arr[index] = value;
      index++;
    }
  }

  for(int i = 0; i < size; i++){
    tree.insert(arr[i]);
  }

  std::cout << "Printing Pre-Order:" << std::endl;
  tree.printPreOrder();
  std::cout << "Printing Level-Order:" << std::endl;
  tree.printLevelOrder();

  std::cout << "Exiting...\n";



  return 0;
}
