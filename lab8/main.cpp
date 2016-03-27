/*
 * Dustin Horvath
 * MinMaxHeap
 * Does what a MinMaxHeap does. Has a little menu for adding and deleting
 * values.
 *
 *
 *******************************************************************************
 * NOTE: RUN THE DEMO to perform all the actions required for this assignment. *
 *******************************************************************************
 *
 *
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

  void swap(int x, int y) {
    int temp = arr[y];
    arr[y] = arr[x];
    arr[x] = temp;
  }

  void trickleUp(int i) {
    int parentIndex = floor((i - 1) / 2);
    int index = (int) floor(log2(i + 1)) % 2;
    // index=0 on min level
    if (index == 0){ 
      if (arr[i] > arr[parentIndex]) {
        swap(i, parentIndex);
        trickleUpMax(parentIndex);
      } 
      else {
        trickleUpMin(i);
      }
    } 
    // index=1 on max level
    else{ 
      if (arr[i] < arr[parentIndex]) {
        swap(i, parentIndex);
        trickleUpMin(parentIndex);
      }
      else {
        trickleUpMax(i);
      }
    }
  }

  void trickleUpMax(int i) {
    int parentIndex = floor((i - 1) / 2);
    int grandparent = floor((parentIndex - 1) / 2);
    if (grandparent != 0){ // have a grand parent
      if (arr[i] > arr[grandparent]) {
        swap(i, grandparent);
        trickleUpMax(grandparent);
      }
    }
  }

  void trickleUpMin(int i) {
    int parentIndex = floor((i - 1) / 2);
    int grandparent = floor((parentIndex - 1) / 2);
    if (grandparent != 0 || parentIndex == 1){ // have a grand parent
      if (arr[i] < arr[grandparent]) {
        swap(i, grandparent);
        trickleUpMin(grandparent);
      }
    }
  }

  void trickleDown(int i) {
    // expression confirmed producing correct values
    int index = (int) floor(log2(i + 1)) % 2;
    // i=0 for min level
    if (index == 0){
      int temp = trickleDownToMinLevel(i);
      temp = trickleDownToMinLevel(temp);
    }
    // i=1 for max level
    else{
      int temp = trickleDownToMaxLevel(i);
      temp = trickleDownToMaxLevel(temp);

    }
  }

  int trickleDownToMinLevel(int i) {
    // arr[i] is not leaf
    if (arr[2 * i + 1] != 0 && 2*i+1 < m_length){
      int firstchildrenPos = 2 * i + 1;
      int firstgrandchildrenPos = 2 * (2 * i + 1) + 1;

      // gets the smallest node
      int m = getSmallestIndex(i);
      int parentIndex = floor((m - 1) / 2);


      // if m is a grandchild
      if (m >= firstgrandchildrenPos){
        if (arr[m] < arr[i]) {
          swap(m, i);
          if (arr[m] > arr[parentIndex]) {
            swap(m, parentIndex);
          }
          trickleDownToMinLevel(m);
        }
      } 



      // else m is a child
      else{
        if (arr[m] < arr[i]){
          swap(m, i);
        }
      }
      // return last index evaluated
      return m;
    }
    return i;
  }

  int trickleDownToMaxLevel(int i) {
    // i is not leaf
    if (arr[2 * i + 1] != 0 && 2*i+1 < m_length){
      int firstchildrenPos = 2 * i + 1;
      int firstgrandchildrenPos = 2 * (2 * i + 1) + 1;

      // gets smallest node
      int m = getLargestIndex(i);
      int parentIndex = floor((m - 1) / 2);


      // m is a grandchild
      if (m >= firstgrandchildrenPos){
        if (arr[m] > arr[i]) {
          swap(m, i);
          if (arr[m] < arr[parentIndex]) {
            swap(m, parentIndex);
          }
          trickleDownToMinLevel(m);
        }
      }


      // else m is a child
      else{
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
      trickleUp(m_length - 1);
    }
    else {
      std::cout << "Cannot insert bad value" << "\n";
    }
  }

  int deleteMin() {
    int temp;
    if (m_length != 0) {
      // swap last value into root
      temp = arr[0];
      arr[0] = arr[m_length - 1];
      // shorten arr
      arr[m_length - 1] = 0;
      m_length--;
      // push the new root down to proper position
      trickleDown(0);
      std::cout << "Deleted min " << temp << ".\n";
      return temp;
    }
    else {
      std::cout << "Heap is empty" << "\n";
      return 0;
    }
  }

  int deleteMax() {
    if(m_length > 0){
      //compare which root child has the biggest value
      if (arr[1] > arr[2]) {
        int temp = arr[1];
        // swap from end
        arr[1] = arr[m_length - 1];
        // shorten
        arr[m_length - 1] = 0;
        m_length--;
        // push down to proper location
        trickleDown(1);
        std::cout << "Deleted max " << temp << ".\n";
        return temp;
      }
      else {
        int temp = arr[2];
        arr[2] = arr[m_length - 1];
        arr[m_length - 1] = 0;
        m_length--;
        trickleDown(2);
        std::cout << "Deleted max " << temp << ".\n";
        return temp;
      }
    }
    else {
      std::cout << "Heap is empty" << "\n";
      return 0;
    }
  }

  void printArr(){
    for(int i = 0; i < m_length; i++){
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }

  void levelorder(){
    if (m_length > 0) {
      std::cout << "Printing level order..." << "\n";
      int size = m_length;
      int height = 0;
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
        }

        std::cout << "\n";
      }
    }
    else {
      std::cout << "No elements in heap\n";
    }
  }


  int getSmallestIndex(int i) {
    int lastChild = 2*i+2;
    int lastGrandchild = 2*(2*i+2)+2;

    int index = 0;
    // index has no grandchildren
    if ((m_length - 1 <= lastChild) || m_length - 1 <= lastGrandchild - 4){
      // only one child
      if (m_length - 1 < lastChild){
        index = m_length - 1;
      }
      // has children in both positions
      else{
        if (arr[lastChild - 1] > arr[lastChild]) {
          index = lastChild;
        }
        else {
          index = lastChild - 1;
        }
      }
      return index;
    }
    // index has values in grandchildren
    if ( (m_length - 1 <= lastGrandchild) && (m_length - 1 > lastGrandchild - 4) ){
      //find the smallest node among all the children and grandchildren
      if (arr[lastChild - 1] > arr[lastChild]) {
        index = lastChild;
      }
      else {
        index = lastChild - 1;
      }
      for (int i = lastGrandchild - 3; i <= m_length - 1; i++) {
        if (arr[i] < arr[index]) {
          index = i;
        }
      }
      return index;
    }
    if (m_length - 1 > lastGrandchild) {
      //find the smallest node among all the children and grandchildren
      if (arr[lastChild - 1] > arr[lastChild]) {
        index = lastChild;
      }
      else {
        index = lastChild - 1;
      }
      for (int i = lastGrandchild - 3; i <= lastGrandchild; i++) {
        if (arr[i] < arr[index]) {
          index = i;
        }
      }
      return index;
    }
  }

  int getLargestIndex(int i) {
    int lastChild = 2*i+2;
    int lastGrandchild = 2*(2*i+2)+2;

    int index = 0;
    if ((m_length - 1 <= lastChild) || m_length - 1 <= lastGrandchild - 4){
      // only one child
      if (m_length - 1 < lastChild){
        index = m_length - 1;
      }
      // two children
      else{
        if (arr[lastChild - 1] < arr[lastChild]) {
          index = lastChild;
        }
        else {
          index = lastChild - 1;
        }
      }
      return index;
    }
    // index has grandchildren
    if ((m_length - 1 <= lastGrandchild) && (m_length - 1 > lastGrandchild - 4)){
      //find the biggest node among all the children and grandchildren
      if (arr[lastChild - 1] < arr[lastChild]) {
        index = lastChild;
      }
      else {
        index = lastChild - 1;
      }
      for (int i = lastGrandchild - 3; i <= m_length - 1; i++) {
        if (arr[i] > arr[index]) {
          index = i;
        }
      }
      return index;
    }
    if (m_length - 1 > lastGrandchild) {
      //find the biggest node among all the children and grandchildren
      if (arr[lastChild - 1] < arr[lastChild]) {
        index = lastChild;
      }
      else {
        index = lastChild - 1;
      }
      for (int i = lastGrandchild - 3; i <= lastGrandchild; i++) {
        if (arr[i] > arr[index]) {
          index = i;
        }
      }
      return index;
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
      heap.levelorder();
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
      std::cout << "\n";
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
