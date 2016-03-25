/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <math.h>

class MinMaxHeap{
public:
  int* arr;
  int m_length;

  MinMaxHeap() {
    arr = nullptr;
    m_length = 0;
  }

  MinMaxHeap(int size){
    generate(size);
    m_length = size;
    buildHeap();
  }

  MinMaxHeap(int* arr, int size) {
    arr = arr;
    m_length = size;
    buildHeap();
  }

  void buildHeap() {
    int index = (m_length - 1) / 2;
    for (int i = index; i >= 0; i--) {
      trickleDown(i);
    }
  }

  ~MinMaxHeap() {
    delete arr;
  }

  bool checkArr(int value, int start, int end){
    for(int i = start; i < end; i++){
      if(arr[i] == value){
        return true;
      }
    }
    return false;

  }

  void generate(int size){
    // Allocate arrays for heap and sorted list.
    arr = new int[size];

    // Set out lengths at zero for now.
    // Generates 'size' random values, then store them in our heap array. This
    // is a little inefficient atm because I pulled it from main for
    // abstraction, but I'm not in the mood to clean it up.
    std::cout << "Generating " << size << " random values.\n";
    int floor = 1;
    int ceiling = 100;
    int range = (ceiling - floor);

    for(int i = 0; i < size; i++){
      int temp;
      do{
        temp = floor + ( std::rand() % ( ceiling - floor + 1 ) );
      } while( checkArr(temp, 0, i)) ;
        

      arr[i] = temp;
      
    }

  }

  void BubbleUp(int i) {
    int index = (int) floor(log2(i + 1)) % 2;
    int parent = floor((i - 1) / 2);
    if (index == 0){ //i is on the min level
      if (arr[i] > arr[parent]) {
        swap(i, parent);
        BubbleUpMax(parent);
      } 
      else {
        BubbleUpMin(i);
      }
    } 
    else{ //i is on the max level
      if (arr[i] < arr[parent]) {
        swap(i, parent);
        BubbleUpMin(parent);
      }
      else {
        BubbleUpMax(i);
      }
    }
  }

  void BubbleUpMin(int i) {
    int parent = floor((i - 1) / 2);
    int grandparent = floor((parent - 1) / 2);
    if (grandparent != 0 || parent == 1){ // have a grand parent
      if (arr[i] < arr[grandparent]) {
        swap(i, grandparent);
        BubbleUpMin(grandparent);
      }
    }
  }

  void BubbleUpMax(int i) {
    int parent = floor((i - 1) / 2);
    int grandparent = floor((parent - 1) / 2);
    if (grandparent != 0){ // have a grand parent
      if (arr[i] > arr[grandparent]) {
        swap(i, grandparent);
        BubbleUpMax(grandparent);
      }
    }
  }

  void trickleDown(int i) {
    int index = (int) floor(log2(i + 1)) % 2;
    if (index == 0){ //i is on the min level
      trickleDownMin(i);
    }
    else{ //i is on the max level
      trickleDownMax(i);
    }
  }

  void trickleDownMin(int i) {
    if (arr[2 * i + 1] != 0){ //if arr[i] has children
      int firstchildrenPos = 2 * i + 1;
      int firstgrandchildrenPos = 2 * (2 * i + 1) + 1;

      int m = smallestIndex(i); //find the index of the smallest node
      int parent = floor((m - 1) / 2);
      if (m >= firstgrandchildrenPos){ //arr[m] is a grandchild
        if (arr[m] < arr[i]) {
          swap(m, i);
          if (arr[m] > arr[parent]) {
            swap(m, parent);
          }
          trickleDownMin(m);
        }
      } 
      else{ //arr[m] is a child
        if (arr[m] < arr[i])
          swap(m, i);
      }
    }
  }

  void trickleDownMax(int i) {
    if (arr[2 * i + 1] != 0){ //if arr[i] has children
      int firstchildrenPos = 2 * i + 1;
      int firstgrandchildrenPos = 2 * (2 * i + 1) + 1;

      int m = biggestIndex(i); //find the index of the smallest node
      int parent = floor((m - 1) / 2);
      if (m >= firstgrandchildrenPos){ //arr[m] is a grandchild
        if (arr[m] > arr[i]) {
          swap(m, i);
          if (arr[m] < arr[parent]) {
            swap(m, parent);
          }
          trickleDownMin(m);
        }
      }
      else{ //arr[m] is a child
        if (arr[m] > arr[i])
          swap(m, i);
      }
    }
  }

  void insert(int val) {
    if(arr == nullptr) {
      int* temp = new int[2000];
      arr = temp;
    }
    if (val > 0) {
      m_length++;
      arr[m_length - 1] = val;
      BubbleUp(m_length - 1);
    }
    else {
      std::cout << "invalid input" << "\n";
    }
  }

  void deleteMin() {
    if (m_length != 0) {
      arr[0] = arr[m_length - 1];
      arr[m_length - 1] = 0;
      m_length--;
      trickleDown(0);
    }
    else {
      std::cout << "Heap Empty" << "\n";
    }
  }

  void deleteMax() {
    //compare which index has the biggest value
    if (arr[1] > arr[2]) {
      arr[1] = arr[m_length - 1];
      arr[m_length - 1] = 0;
      m_length--;
      trickleDown(1);
    }
    else {
      arr[2] = arr[m_length - 1];
      arr[m_length - 1] = 0;
      m_length--;
      trickleDown(2);
    }
  }

  void levelorder() {
    if (m_length != 0) {
      std::cout << "Level order: " << "\n";
      int height = 0;
      int size = m_length;
      while (size > pow(2, height)) {
        size - pow(2, height);
        height++;
      }
      int index = 0;
      for (int i = 0; i <= height; i++) {
        for (int j = 0; j < pow(2, i); j++) {
          if (arr[index] != 0) {

            std::cout << arr[index] << " ";
            index++;
          }
          else {
            break;
          }
        }
        std::cout << "\n";
      }
    }
    else {
      std::cout << "Heap empty " << "\n";
    }
  }

  void swap(int pos1, int pos2) {
    int temp = arr[pos1];
    arr[pos1] = arr[pos2];
    arr[pos2] = temp;
  }

  int smallestIndex(int i) {
    int smallestindex = 0;
    int lastchildrenPos = 2 * i + 2;
    int lastgrandchildrenPos = 2 * (2 * i + 2) + 2;

    if ((m_length - 1 <= lastchildrenPos) || m_length - 1 <= lastgrandchildrenPos - 4){ //if arr[i] has no grandchildren
      if (m_length - 1 < lastchildrenPos){ //has only one child
        smallestindex = m_length - 1;
      }
      else{ //has two children
        if (arr[lastchildrenPos - 1] > arr[lastchildrenPos]) {
          smallestindex = lastchildrenPos;
        }
        else {
          smallestindex = lastchildrenPos - 1;
        }
      }
      return smallestindex;
    }
    if ((m_length - 1 <= lastgrandchildrenPos) && (m_length - 1 > lastgrandchildrenPos - 4)){ //if arr[i] has grandchildren
      //find the smallest node among all the children and grandchildren
      if (arr[lastchildrenPos - 1] > arr[lastchildrenPos]) {
        smallestindex = lastchildrenPos;
      }
      else {
        smallestindex = lastchildrenPos - 1;
      }
      for (int i = lastgrandchildrenPos - 3; i <= m_length - 1; i++) {
        if (arr[i] < arr[smallestindex]) {
          smallestindex = i;
        }
      }
      return smallestindex;
    }
    if (m_length - 1 > lastgrandchildrenPos) {
      //find the smallest node among all the children and grandchildren
      if (arr[lastchildrenPos - 1] > arr[lastchildrenPos]) {
        smallestindex = lastchildrenPos;
      }
      else {
        smallestindex = lastchildrenPos - 1;
      }
      for (int i = lastgrandchildrenPos - 3; i <= lastgrandchildrenPos; i++) {
        if (arr[i] < arr[smallestindex]) {
          smallestindex = i;
        }
      }
      return smallestindex;
    }
  }

  int biggestIndex(int i) {
    int biggestIndex = 0;
    int lastchildrenPos = 2 * i + 2;
    int lastgrandchildrenPos = 2 * (2 * i + 2) + 2;

    if ((m_length - 1 <= lastchildrenPos) || m_length - 1 <= lastgrandchildrenPos - 4){ //if arr[i] has no grandchildren
      if (m_length - 1 < lastchildrenPos){ //has only one child
        biggestIndex = m_length - 1;
      }
      else{ //has two children
        if (arr[lastchildrenPos - 1] < arr[lastchildrenPos]) {
          biggestIndex = lastchildrenPos;
        }
        else {
          biggestIndex = lastchildrenPos - 1;
        }
      }
      return biggestIndex;
    }
    if ((m_length - 1 <= lastgrandchildrenPos) && (m_length - 1 > lastgrandchildrenPos - 4)){ //if arr[i] has grandchildren
      //find the biggest node among all the children and grandchildren
      if (arr[lastchildrenPos - 1] < arr[lastchildrenPos]) {
        biggestIndex = lastchildrenPos;
      }
      else {
        biggestIndex = lastchildrenPos - 1;
      }
      for (int i = lastgrandchildrenPos - 3; i <= m_length - 1; i++) {
        if (arr[i] > arr[biggestIndex]) {
          biggestIndex = i;
        }
      }
      return biggestIndex;
    }
    if (m_length - 1 > lastgrandchildrenPos) {
      //find the biggest node among all the children and grandchildren
      if (arr[lastchildrenPos - 1] < arr[lastchildrenPos]) {
        biggestIndex = lastchildrenPos;
      }
      else {
        biggestIndex = lastchildrenPos - 1;
      }
      for (int i = lastgrandchildrenPos - 3; i <= lastgrandchildrenPos; i++) {
        if (arr[i] > arr[biggestIndex]) {
          biggestIndex = i;
        }
      }
      return biggestIndex;
    }
  }

};


int main(){

  int seed = 5;
  srand (seed);
  bool cont = true;
  int option = 0;

  // Fyi, this constructor calls 'generate', which generates the random values
  // sets initial length global vars, and calls buildheap. If you want to test
  // some specific seed, change this value for your first set of data.
  MinMaxHeap heap = MinMaxHeap(25);




  while(cont){
    std::cout << "What do you want to do?\n";
    std::cout << "1. Insert a new item\n";
    std::cout << "2. Perform deleteMin\n";
    std::cout << "3. Perform deleteMax\n";
    std::cout << "4. Print the current MinMaxHeap\n";
    std::cout << "5. Exit\n";
    std::cout << "Select an option: ";
    std::cin >> option;

    switch(option){
      case 1:
        std::cout << "What value to insert? ";
        std::cin >> option;
        heap.insert(option);
        break;
      case 2:
        heap.deleteMin();
        std::cout << "Deletemin completed.\n";
        break;
      case 3:
        heap.deleteMax();
        std::cout << "Deletemax completed.\n";
        break;
      case 4:
        heap.levelorder();
        break;
      case 5:
        std::cout << "Exiting...\n";
        cont = false;
        break;
      default:
        std::cout << "Invalid input.\n";
      break;



    }



  }


  return 0;
}