/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <math.h>

#define SIZE 2000

class MinMaxHeap{

public:
  int* arr;
  int m_length;

  MinMaxHeap(int size){
    generate(size);
    m_length = size;

    buildHeap();
  }


  ~MinMaxHeap() {
    delete arr;
  }

  void buildHeap() {
    int start = (m_length - 1) / 2;
    for (int i = start; i >= 0; i--) {
      trickleDown(i);
    }
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
    arr = new int[SIZE];

    // Set out lengths at zero for now.
    // Generates 'size' random values, then store them in our heap array.
    std::cout << "Generating " << size << " random values.\n";
    int floor = 1;
    int ceiling = 100;
    int range = (ceiling - floor);

    for(int i = 0; i < size; i++){
      int temp;
      // do-while block ensures that every value inserted is unique
      do{
        temp = floor + ( std::rand() % ( ceiling - floor + 1 ) );
      } while( checkArr(temp, 0, i)) ;
        
      arr[i] = temp;
    }
  }

  void bubbleUp(int i) {
    int parent = floor((i - 1) / 2);
    int index = (int) floor(log2(i + 1)) % 2;
    if (index == 0){ //i is on the min level
      if (arr[i] > arr[parent]) {
        swap(i, parent);
        bubbleUpMax(parent);
      } 
      else {
        bubbleUpMin(i);
      }
    } 
    else{ //i is on the max level
      if (arr[i] < arr[parent]) {
        swap(i, parent);
        bubbleUpMin(parent);
      }
      else {
        bubbleUpMax(i);
      }
    }
  }

  void bubbleUpMin(int i) {
    int parent = floor((i - 1) / 2);
    int grandparent = floor((parent - 1) / 2);
    if (grandparent != 0 || parent == 1){ // have a grand parent
      if (arr[i] < arr[grandparent]) {
        swap(i, grandparent);
        bubbleUpMin(grandparent);
      }
    }
  }

  void bubbleUpMax(int i) {
    int parent = floor((i - 1) / 2);
    int grandparent = floor((parent - 1) / 2);
    if (grandparent != 0){ // have a grand parent
      if (arr[i] > arr[grandparent]) {
        swap(i, grandparent);
        bubbleUpMax(grandparent);
      }
    }
  }

  void trickleDown(int i) {
    // expression confirmed producing correct values
    int index = (int) floor(log2(i + 1)) % 2;
    // i=0 for min level
    if (index == 0){
      int temp = trickleDownMin(i);
      for(int i = 0; i < m_length/2; i++){
        temp = trickleDownMin(temp);
      }
    }
    // i=1 for max level
    else{
      int temp = trickleDownMax(i);
      for(int i = 0; i < m_length/2; i++){
        temp = trickleDownMax(temp);
      }

    }
  }

  int trickleDownMin(int i) {
    if (arr[2 * i + 1] != 0 && 2*i+1 < m_length){ //if arr[i] has children
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
        if (arr[m] < arr[i]){
          swap(m, i);
        }
      }
      return m;
    }
    return i;
  }

  int trickleDownMax(int i) {
    if (arr[2 * i + 1] != 0 && 2*i+1 < m_length){ //if arr[i] has children
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
      return m;
    }
    return i;
  }

  void insert(int val) {
    if(arr == nullptr) {
      int* temp = new int[SIZE];
      arr = temp;
    }
    if (val > 0) {
      m_length++;
      arr[m_length - 1] = val;
      bubbleUp(m_length - 1);
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

  int deleteMax() {
    //compare which index has the biggest value
    if (arr[1] > arr[2]) {
      int temp = arr[1];
      arr[1] = arr[m_length - 1];
      arr[m_length - 1] = 0;
      m_length--;
      trickleDown(1);
      return temp;
    }
    else {
      int temp = arr[2];
      arr[2] = arr[m_length - 1];
      arr[m_length - 1] = 0;
      m_length--;
      trickleDown(2);
      return temp;
    }
  }

  void printArr(){
    for(int i = 0; i < m_length; i++){
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }

  void levelorder(){
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

  void swap(int x, int y) {
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
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

  int seed = 0;
  srand (seed);
  bool cont = true;
  int option = 0;
  int temp = 0;

  // Fyi, this constructor calls 'generate', which generates the random values
  // sets initial length global vars, and calls buildheap. If you want to test
  // some specific seed, change this value for your first set of data.
  MinMaxHeap heap = MinMaxHeap(50);

  while(cont){
    std::cout << "What do you want to do?\n";
    std::cout << "1. Insert a new item\n";
    std::cout << "2. Perform deleteMin\n";
    std::cout << "3. Perform deleteMax\n";
    std::cout << "4. Print levelOrder.\n";
    std::cout << "5. Print flat array.\n";
    std::cout << "6. Run Demo\n";
    std::cout << "7. Exit\n";
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
        heap.printArr();
        break;
      case 6:
        heap.insert(5);
        heap.insert(87);
        heap.deleteMax();
        heap.printArr();
        heap.deleteMin();
        heap.printArr();
        heap.insert(50);
        temp = heap.deleteMax();
        heap.printArr();
        heap.insert(temp);
        heap.insert(2);
        heap.insert(1);
        heap.insert(100);
        heap.insert(99);
        heap.deleteMin();
        heap.printArr();
        heap.deleteMax();
        heap.printArr();
        heap.deleteMin();
        heap.printArr();
        heap.deleteMax();
        heap.printArr();
        heap.deleteMax();
        heap.printArr();
        heap.deleteMax();
        heap.printArr();

        break;
      case 7:
        std::cout << "Exiting...\n";
        cont = false;
        break;
      default:
        std::cout << "Invalid input.\n";
        break;



    }



  }

}
