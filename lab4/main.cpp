
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Queue.h"

class Node {
public:
  int m_height;
  std::string m_name;
  int m_x;
  int m_y;
  Node* m_left;
  Node* m_right;

  Node(){
    m_left = nullptr;
    m_right = nullptr;
    m_name = "";
    m_x = 0;
    m_y = 0;
    m_height = 0;
  }

  Node(std::string name, int x_in, int y_in){
    m_left = nullptr;
    m_right = nullptr;
    m_name = name;
    m_x = x_in;
    m_y = y_in;
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

  void insert(std::string m_name, int x, int y){
    m_root = insert(m_name, x, y, m_root);
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
  Node* insert(std::string name, int x, int y, Node* node){
    // If tree is empty, return
    if (!node){
      node = new Node(name, x, y);
    }
    // Compare 'value' to m_name inside node, then pick which subtree to put
    // it in.
    else if (name < node -> m_name){
      node -> m_left = insert(name, x, y, node -> m_left);
      // Compare subtree heights. If more then 1 height difference, move
      // subtrees so that that's not the case.
      if (height(node -> m_left) - height(node -> m_right) == 2){
        if (name < node -> m_left -> m_name){
          node = switchWithLeft(node);
        }
        else{
          node = switchWithLeftChild(node);
        }
      }
    }
    else if (name > node -> m_name){
      node -> m_right = insert(name, x, y, node -> m_right);
      if (height(node -> m_right) - height(node -> m_left) == 2){
        if (name > node -> m_right -> m_name){
          node = switchWithRight(node);
        }
        else{
          node = switchWithRightChild(node);
        }
      }
    }

    node -> m_height = max(height(node -> m_left), height(node -> m_right)) + 1;
    return node;
  }

  Node* remove(std::string name){
    return remove(m_root, name);
  }

  Node* remove(Node* root, std::string name){

    if(root == nullptr){
      return root;
    }
    if(name < root -> m_name ){
      root -> m_left = remove(root -> m_left, name);
    }
    else if(name > root -> m_name ){
      root -> m_right = remove(root -> m_right, name);
    }

    else{
      if( (root -> m_left == nullptr) || (root -> m_right == nullptr) ){
        Node* temp;
        if(root -> m_left != nullptr){
          temp = root -> m_left;
        }
        else{
          temp = root -> m_right;
        }

        if(temp == nullptr){
          temp = root;
          root = nullptr;
        }
        else
          *root = *temp;
      }
      else{
        Node* temp = minValueNode(root -> m_right);

        root -> m_name = temp -> m_name;

        root -> m_right = remove(root -> m_right, temp -> m_name);
      }
    }

    if(root == NULL){
      return root;
    }

    root -> m_height = max(height(root -> m_left), height(root -> m_right)) + 1;
    int balance = getBalance(root);

    if(balance > 1 && getBalance(root -> m_left) >= 0)
      return switchWithRight(root);

    if(balance > 1 && getBalance(root->m_left) < 0)
    {
      root -> m_left =  switchWithLeft(root -> m_left);
      return switchWithRight(root);
    }

    if(balance < -1 && getBalance(root->m_right) <= 0)
      return switchWithLeft(root);

    if(balance < -1 && getBalance(root->m_right) > 0)
    {
      root->m_right = switchWithRight(root->m_right);
      return switchWithLeft(root);
    }

    return root;
  }

  Node* minValueNode(Node* node){
    struct Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->m_left != NULL)
      current = current->m_left;

    return current;
  }

  int getBalance(Node* n){
    if (n == nullptr){
      return 0;
    }
    return height(n->m_left) - height(n->m_right);
  }

  /*
   * Pre: BinarySearchTree constructed, has children
   * Post: Moves subtrees to balance tree
   * Return: node pointer
   * @note: called by `switchWithRightChild`, `insert`
   */
  Node* switchWithLeft(Node* node){
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
   * @note: called by `switchWithLeftChild`, `insert`
   */
  Node* switchWithRight(Node* node){
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
  Node* switchWithLeftChild(Node* node){
    node -> m_left = switchWithRight(node -> m_left);
    return switchWithLeft(node);
  }

  /*
   * Pre: BST constructed, has children
   * Post: Rotates subtrees
   * Return: node pointer
   * @note: called by `insert`
   */
  Node* switchWithRightChild(Node* node){
    node -> m_right = switchWithLeft(node -> m_right);
    return switchWithRight(node);
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
        std::cout << temp -> m_name << " " << temp -> m_x << " " << temp -> m_y << " ";
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



class LocationArray{
  std::string m_arr[300];
  int m_length;

public:

  LocationArray(){
    m_length = 0;
  }

  void insert(std::string* pack){
    m_arr[m_length] = pack[0];
    m_arr[m_length + 1] = pack[1];
    m_arr[m_length + 2] = pack[2];
    m_length += 3;
  }

  void print(){
    int i = 0;
    while(i < m_length){
      std::cout << m_arr[i] << " " << m_arr[i+1] << " " << m_arr[i+2] << "\n";
      i += 3;
    }
  }

  void remove(std::string name){
    int i = 0;
    while(m_arr[i].compare(name) != 0 && i < m_length){
      i++;
    }
    if(i == m_length){
      std::cout << "City not in list.\n";
    }
    else{
      m_arr[i] = m_arr[m_length - 3];
      m_arr[i+1] = m_arr[m_length - 2];
      m_arr[i+2] = m_arr[m_length - 1];
      m_length -= 3;
    }
  }

  void remove(int x, int y){
    int i = 1;
    std::string xs = std::to_string(x);
    std::string ys = std::to_string(y);
    while((m_arr[i-1].compare(xs) != 0 || m_arr[i].compare(ys) != 0) && i < m_length){
      i++;
    }
    if(i == m_length){
      std::cout << "Found no city at " << x << " " << y << "\n";
    }
    else{
      std::cout << "Removing " << m_arr[i-2] << " " << m_arr[i-1] << " " << m_arr[i] << "\n";
      m_arr[i-2] = m_arr[m_length - 3];
      m_arr[i-1] = m_arr[m_length - 2];
      m_arr[i] = m_arr[m_length - 1];
      m_length -= 3;
    }

  }

};


int main(){

  BinarySearchTree tree = BinarySearchTree();

  LocationArray la = LocationArray();

  std::ifstream file("data.txt");
  std::string line;

  while(std::getline(file, line)){
    std::string temp_arr[3];
    int i = 0;
    std::istringstream iss(line);
    while(iss.good()){
      iss >> temp_arr[i];
      i++;
    }
    tree.insert(temp_arr[0], atoi(temp_arr[1].c_str()), atoi(temp_arr[2].c_str()));
    la.insert(temp_arr);
  }


  std::cout << "Printing array: \n";
  la.print();
  //  la.remove("Otherplace");
  std::cout << std::endl;

  std::cout << "Printing AVL level order:\n";
  tree.printLevelOrder();
  
  tree.remove("Place1");
  std::cout << "Printing AVL level order:\n";
  tree.printLevelOrder();

  std::cout << "Exiting...\n";
  return 0;
}
