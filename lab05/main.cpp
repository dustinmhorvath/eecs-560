/*
 * Dustin Horvath
 * 2729265
 * EECS 560 Lab 5
 * 2/27/16
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Queue.h"
//used for pow and sqrt
#include <math.h>

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
  int comparisons = 0;
  int buildcomparisons = 0;

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
    buildcomparisons++;
    if(!node){
      return -1;
    }
    else{
      return node -> m_height;
    }
  }

  int max(int lhs, int rhs){
    buildcomparisons++;
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
      buildcomparisons++;
      node = new Node(name, x, y);
    }
    // Compare 'value' to m_name inside node, then pick which subtree to put
    // it in.
    else if (name < node -> m_name){
      buildcomparisons += 2;
      node -> m_left = insert(name, x, y, node -> m_left);
      // Compare subtree heights. If more then 1 height difference, move
      // subtrees so that that's not the case.
      buildcomparisons++;
      if (height(node -> m_left) - height(node -> m_right) == 2){
        buildcomparisons++;
        if (name < node -> m_left -> m_name){
          node = rotateWithLeftChild(node);
        }
        else{
          node = doubleWithLeftChild(node);
        }
      }
    }
    else if (name > node -> m_name){
      buildcomparisons += 3;
      node -> m_right = insert(name, x, y, node -> m_right);
      buildcomparisons++;
      if (height(node -> m_right) - height(node -> m_left) == 2){
        buildcomparisons++;
        if (name > node -> m_right -> m_name){
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

  Node* remove(std::string name){
    return remove(m_root, name);
  }

  Node* remove(Node* root, std::string name){

    buildcomparisons++;
    if(root == nullptr){
      return root;
    }

    if(name < root -> m_name ){
      buildcomparisons++;
      root -> m_left = remove(root -> m_left, name);
    }
    else if(name > root -> m_name ){
      buildcomparisons += 2;
      root -> m_right = remove(root -> m_right, name);
    }

    else{
      buildcomparisons += 2;

      buildcomparisons += 2;
      if( (root -> m_left == nullptr) || (root -> m_right == nullptr) ){
        Node* temp;
        buildcomparisons++;
        if(root -> m_left != nullptr){
          temp = root -> m_left;
        }
        else{
          temp = root -> m_right;
        }

        buildcomparisons++;
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

    buildcomparisons++;
    if(root == nullptr){
      return root;
    }

    root -> m_height = max(height(root -> m_left), height(root -> m_right)) + 1;
    int balance = getBalance(root);

    buildcomparisons += 2;
    if(balance > 1 && getBalance(root -> m_left) >= 0){
      return rotateWithRightChild(root);
    }

    buildcomparisons += 2;
    if(balance > 1 && getBalance(root->m_left) < 0){
      root -> m_left =  rotateWithLeftChild(root -> m_left);
      return rotateWithRightChild(root);
    }

    buildcomparisons += 2;
    if(balance < -1 && getBalance(root->m_right) <= 0){
      return rotateWithLeftChild(root);
    }

    buildcomparisons += 2;
    if(balance < -1 && getBalance(root->m_right) > 0){
      root->m_right = rotateWithRightChild(root->m_right);
      return rotateWithLeftChild(root);
    }

    return root;
  }

  Node* minValueNode(Node* node){
    struct Node* current = node;

    /* loop down to find the leftmost leaf */
    buildcomparisons++;
    while (current->m_left != nullptr){
      buildcomparisons++;
      current = current->m_left;
    }

    return current;
  }

  int getBalance(Node* n){
    buildcomparisons++;
    if (n == nullptr){
      return 0;
    }
    return height(n->m_left) - height(n->m_right);
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
  
  Node* findByCoordHelper(Node* subtree, int x, int y){
    comparisons++;
      Node* found;
      comparisons++;
    if(subtree != nullptr){
      if(subtree -> m_x == x && subtree -> m_y == y){
      comparisons++;
        return subtree;
      }
      else if(findByCoordHelper(subtree -> m_left, x, y) != nullptr){
      comparisons += 2;
        return findByCoordHelper(subtree -> m_left, x, y);
      }
      else if(findByCoordHelper(subtree -> m_right, x, y) != nullptr){
      comparisons += 2;
        return findByCoordHelper(subtree -> m_right, x, y);
      }
    }
    else{
      return nullptr;
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
  void findByCoord(int x, int y){
    Node* found = findByCoordHelper(m_root, x, y);
    comparisons++;
    if(found != nullptr){
        std::cout << "Found " << found -> m_name << " at (" << x << "," << y << ") \n";
    }
    else{
      std::cout << "Found no location at (" << x << "," << y << ").\n";
    }
  }


  /*
   * Pre: BST constructed
   * Post: Prints all the values inside the tree in level-order, by level
   * Return: none
   */
  void printLevelOrder(){
    // Exit if tree is empty
    if (m_root == nullptr) { return;}
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
        /*        if(temp -> m_x != -111 && temp -> m_y != -111){
                  std::cout << temp -> m_x << " " << temp -> m_y << " ";
                  }*/
        // Pop the front of the queue
        q.dequeue();
        // Push on any children
        if (temp -> m_left){
          q.enqueue(temp -> m_left);
        }
        /*        else if((temp -> m_name).compare("*") != 0){
                  temp -> m_left = new Node("*", -111, -111);
                  q.enqueue(temp -> m_left);
                  }*/
        if (temp -> m_right){
          q.enqueue(temp -> m_right);
        }
        /*        else if((temp -> m_name).compare("*") != 0){
                  temp -> m_right = new Node("*", -111, -111);
                  q.enqueue(temp -> m_right);
                  }*/

        nodeCount--;
      }
      std::cout << std::endl;
      level++;
    }
  }

  void findWithinRadiusHelper(Node* subtree, int x_in, int y_in, int radius){
    comparisons++;
    if(subtree != nullptr){
      double del_x = subtree -> m_x - (double)x_in;
      double del_y = subtree -> m_y - (double)y_in;
      double hyp = sqrt(pow(del_x,2) + pow(del_y,2));
      comparisons++;
      if( hyp < radius ){
        std::cout << "Node " << subtree -> m_name << " at (" << subtree->m_x << "," << subtree->m_y << ") is within " << radius << " of (" << x_in << "," << y_in << ") and is " << hyp << " away.\n";
      }
      findWithinRadiusHelper(subtree -> m_left, x_in, y_in, radius);
      findWithinRadiusHelper(subtree -> m_right, x_in, y_in, radius);

    }
  }

  /*
   * Pre: BST constructed
   * Post: Calls preOrderHelper with m_root to print out values
   * Return: none
   */
  void findWithinRadius(int x, int y, int radius){
    findWithinRadiusHelper(m_root, x, y, radius);
    std::cout << std::endl;
  }



};



class LocationArray{
  std::string m_arr[300];
  int m_length;

public:
  int comparisons = 0;
  int buildcomparisons = 0;

  /* Stores locations in the following format:
   * [Name1, X1, Y1, Name2, X2, Y2, Name3......Name(Length-1), X(length-1), Y(length-1)]
   */
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
    buildcomparisons++;
    while(m_arr[i].compare(name) != 0 && i < m_length){
      comparisons++;
      i++;
    }
    buildcomparisons++;
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
    buildcomparisons += 3;
    while((m_arr[i-1].compare(xs) != 0 || m_arr[i].compare(ys) != 0) && i < m_length){
      buildcomparisons += 3;
      i++;
    }
    buildcomparisons++;
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

  void findByCoord(int x, int y){
    int i = 2;
    std::string xs = std::to_string(x);
    std::string ys = std::to_string(y);
    comparisons += 3;
    while((m_arr[i-1].compare(xs) != 0 || m_arr[i].compare(ys) != 0) && i < m_length){
      comparisons += 3;
      //i++;
      i += 3;
    }
    comparisons++;
    if(i == m_length){
      std::cout << "Found no city at " << x << " " << y << "\n";
    }
    else{
      std::cout << "Found " << m_arr[i-2] << " " << m_arr[i-1] << " " << m_arr[i] << "\n";
    }

  }

  void findWithinRadius(int x_in, int y_in, int radius){
    int i = 1;
    comparisons++;
    while(i < m_length){
      comparisons++;
      double del_x = atoi(m_arr[i].c_str()) - (double)x_in;
      double del_y = atoi(m_arr[i+1].c_str()) - (double)y_in;
      double hyp = sqrt(pow(del_x,2) + pow(del_y,2));
      comparisons++;
      if(hyp < radius){
        std::cout << "Node " << m_arr[i-1] << " at (" << m_arr[i] << "," << m_arr[i+1] << ") is within " << radius << " of (" << x_in << "," << y_in << ") and is " << hyp << " away.\n";
      }
      i += 3;
    }
  }


};

class LocRadius{
public:
  int m_x;
  int m_y;
  int m_radius;
  LocRadius(int x, int y, int radius){
    m_x = x;
    m_y = y;
    m_radius = radius;
  }

  LocRadius(){}
};

int main(){

  BinarySearchTree tree = BinarySearchTree();

  LocationArray la = LocationArray();

  std::ifstream queryfile("lab5_testR.txt");
  std::string line;

  Queue<LocRadius> arrayQueue;
  Queue<LocRadius> treeQueue;

  while(std::getline(queryfile, line)){
    int temp_arr[3];
    int i = 0;
    std::istringstream iss(line);
    while(iss.good()){
      iss >> temp_arr[i];
      i++;
    }
    arrayQueue.enqueue(LocRadius(temp_arr[0], temp_arr[1], temp_arr[2]));
    treeQueue.enqueue(LocRadius(temp_arr[0], temp_arr[1], temp_arr[2]));
  }


  std::ifstream locationlist("data5R.txt");

  while(std::getline(locationlist, line)){
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



  int ex_x = 23;
  int ex_y = 43;
  std::string toremove = "Derptown";

  std::cout << "Printing array: \n\n";
  la.print();

  std::cout << "\nFinding all locations in array within radii...\n";
  while(!arrayQueue.isEmpty()){
    LocRadius tempLoc = arrayQueue.peekFront();
    std::cout << "Searching near (" << tempLoc.m_x << "," << tempLoc.m_y << ")...\n";
    la.findByCoord(tempLoc.m_x, tempLoc.m_y);
    la.findWithinRadius(tempLoc.m_x, tempLoc.m_y, tempLoc.m_radius);
    arrayQueue.dequeue();
    std::cout << "\n";
  }


  std::cout << "\n\nPrinting AVL level order:\n\n";
  tree.printLevelOrder();

  std::cout << "\nFinding all locations in tree within radii...\n";
  while(!treeQueue.isEmpty()){
    LocRadius tempLoc = treeQueue.peekFront();
    std::cout << "Searching near (" << tempLoc.m_x << "," << tempLoc.m_y << ")...\n";
    tree.findByCoord(tempLoc.m_x, tempLoc.m_y);
    tree.findWithinRadius(tempLoc.m_x, tempLoc.m_y, tempLoc.m_radius);
    treeQueue.dequeue();
  }

  std::cout << "Array implementation used " << la.comparisons << " search comparisons and " << la.buildcomparisons << " build comparisons.\n";
  std::cout << "Tree implementation used " << tree.comparisons << " search comparisons and " << tree.buildcomparisons << " build comparisons.\n";

  tree.comparisons = 0;
  tree.buildcomparisons = 0;
  la.comparisons = 0;
  la.buildcomparisons = 0;

  int length = 5;
  std::string removelist[length] = {
    "FortHays", "Hooterville",
    "Russellville" , "HighCityHeights",
    "BridgerRange" };
  
  std::cout << "\nTREE OPERATIONS\n";

  for(int i = 0; i < length; i++){
    std::cout << "Removing " << removelist[i] << " from the list..\n";
    tree.remove(removelist[i]);
    std::cout << "Tree implementation used " << tree.comparisons + tree.buildcomparisons << " comparisons.\n";
  }

  std::cout << "\nARRAY OPERATIONS\n";

  for(int i = 0; i < length; i++){
    std::cout << "Removing " << removelist[i] << " from the list..\n";
    la.remove(removelist[i]);
    std::cout << "Array implementation used " << la.comparisons + la.buildcomparisons << " comparisons.\n";
  }

  std::cout << "\n";


  //tree.remove("FortHays");
  //tree.remove("Hooterville");
  //tree.remove("Russellville");

  tree.comparisons = 0;
  tree.buildcomparisons = 0;
  la.comparisons = 0;
  la.buildcomparisons = 0;

  std::cout << "Finding (16,22) and (25,32) by coordinates.\n";
  tree.findByCoord(16,22);
  tree.findByCoord(25,32);
  la.findByCoord(16,22);
  la.findByCoord(25,32);
  std::cout << "Array implementation used " << la.comparisons + la.buildcomparisons << " comparisons.\n";
  std::cout << "Tree implementation used " << tree.comparisons + tree.buildcomparisons << " comparisons.\n";

  std::cout << "Exiting...\n";
  return 0;
}
