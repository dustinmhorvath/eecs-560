
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

class MinHeap{
  public:

  int *arr;
  int *sorted;
  int arrLength;
  int sortedLength;
  int firstConstruct;
  int comparisons = 0;

  MinHeap(int size){
    firstConstruct = true;
    generate(size);    
  }

  ~MinHeap(){
    delete [] arr;
    delete [] sorted;
  }

  void generate(int size){
    if(!firstConstruct){
      delete [] arr;
      delete [] sorted;
    }
    // Allocate arrays for heap and sorted list.
    arr = new int[size+1];
    sorted = new int[size+1];

    // Store a magic number in index 0.
    arr[0] = -1111;
    // Set out lengths at zero for now.
    arrLength = 0;
    sortedLength = 0;  
    // Generates 'size' random values, then store them in our heap array. This
    // is a little inefficient atm because I pulled it from main for
    // abstraction, but I'm not in the mood to clean it up.
    int generated[size];
    std::cout << "Generating " << size << " random values.\n";
    int floor = -1000;
    int ceiling = 1000;
    int range = (ceiling - floor);
    
    for(int i = 0; i < size; i++){
      generated[i] = floor + ( std::rand() % ( ceiling - floor + 1 ) );
    }


    // Heapify
    buildHeap(generated, size);

    comparisons = 0;
  }
  
  void buildHeap(int insert[], int n){
    std::cout << "Building heap...\n";

    // Copy the new values into the array
    for(int i = 0; i < n; i++){
      arr[i+1] = insert[i];
      arrLength++;
    }

    // Does not use parameters anymore, all stored in member vars
    for(int i = floor(arrLength/2); i > 0; i--){
      push_down(i);
    }
  }
 

  void push_down(int i){
    // moves an item down the heap until the correct spot for it is found
    // The item being moved down the heap starts in position i
    int val = arr[i];
    int position = i;
    bool cont = true;
    comparisons++;
    while( cont ){
      comparisons++;
      int k;
      if(arr[2*position] > arr[2*position + 1] && 2*position + 1 <= arrLength){
        comparisons+=2;
        k = 2*position + 1;
      }
      else if(2*position <= arrLength){
        comparisons+=3;
        k = 2*position;
      }
      else{
        comparisons+=3;
        arr[position] = val;
        cont = false;
      }

      comparisons++;
      if(val > arr[k]){
        arr[position] = arr[k];
        position = k;
      }
      else{
        arr[position] = val;
        cont = false;
      }

    }
  }

  int push_down_modified(int i){
    // moves an item down the heap until the correct spot for it is found
    // The item being moved down the heap starts in position i
    int val = arr[i];
    int position = i;
    bool cont = true;
    comparisons++;
    while( cont ){
      comparisons++;
      int k;
      if(arr[2*position] > arr[2*position + 1] && 2*position + 1 <= arrLength){
        comparisons+=2;
        k = 2*position + 1;
      }
      else if(2*position <= arrLength){
        comparisons+=3;
        k = 2*position;
      }
      else{
        comparisons+=3;
        arr[position] = val;
        cont = false;
      }

      comparisons++;
      if(position != k){
        arr[position] = arr[k];
        position = k;
      }
      else{
        arr[position] = val;
        cont = false;
      }

    }
    return position;
  }


  void push_up(int i){
    //move an item up the heap until the correct spot for it is found
    //The item being moved up the heap starts in position i
    int val = arr[i];
    int position = i;
    comparisons+=2;
    while ( val < arr[position/2] && position > 1){
      comparisons+=2;
      //integer division for find parent
      arr[position] = arr[position/2];
      position = position/2;
    }
    arr[position] = val;
  }


  void deleteMin(){
    comparisons++;
    if(arrLength == 0){
      return;
    }

    // Grab copy of top, replace with last
    int temp = arr[1];
    arr[1] = arr[arrLength];
    arrLength--;

    // Store the front into a new sorted array.
    sortedLength++;
    sorted[sortedLength] = temp;

    push_down(1);
  }

  void deleteMin_modified(){
    comparisons++;
    if(arrLength == 0){
      return;
    }

    // Grab copy of top, replace with last
    int temp = arr[1];
    arr[1] = arr[arrLength];
    arrLength--;

    // Store the front into a new sorted array.
    sortedLength++;
    sorted[sortedLength] = temp;

    int tempIndex = push_down_modified(1);
    push_up(tempIndex);
  }

  void heapSort(){
    sortedLength = 0;
    int tempArr[arrLength + 1];
    int tempSize = arrLength;
    
    for(int i = 0; i <= arrLength; i++){
      tempArr[i] = arr[i];
    }

    std::cout << "Running heapsort...\n";
    comparisons++;
    while(arrLength > 0){
      comparisons++;
      deleteMin();
    }

    for(int i = 0; i <= tempSize; i++){
      arr[i] = tempArr[i];
    }
    arrLength = tempSize;
  }

  void heapSort_modified(){
    sortedLength = 0;
    int tempArr[arrLength + 1];
    int tempSize = arrLength;
    
    for(int i = 0; i <= arrLength; i++){
      tempArr[i] = arr[i];
    }

    
    std::cout << "Running modified heapsort...\n";
    comparisons++;
    while(arrLength > 0){
      comparisons++;
      deleteMin_modified();
    }
    
    for(int i = 0; i <= tempSize; i++){
      arr[i] = tempArr[i];
    }

    arrLength = tempSize;
  }

  // Verify function was tested by manually adding very high values to the
  // start of the heap and attempting to verify. Returned failure with bad
  // value.
  bool verifyHeap(){
    if(arrLength == 0){
      std::cout << "No heap to print\n.";
      return false;
    }
    bool verified = true;
    std::cout << "Verifying heap...";
    // Needs equals here? 
    // Nah, last one will be implied correct after checking all the others.
    for(int i = 1; i < arrLength; i++){
      if( (arr[2*i + 1] < arr[i] && 2*i+1 <= arrLength ) ||
        (arr[2*i] < arr[i] && 2*i <= arrLength)  ){
        verified = false;
      }
    }
    if(verified){
      std::cout << "SUCCESS: Heap is built in MinHeap order.\n";
    }
    else{
      std::cout << "FAIL: Heap was not built in MinHeap order.\n";
    }
    return verified;
  }

  bool verifySorted(){
    bool verified = true;
    std::cout << "Verifying sorted list...";
    if(sortedLength == 0){
      std::cout << "No sorted array to print.\n";
      return false;
    }
    for(int i = 1; i < sortedLength; i++){
      if(sorted[i] > sorted[i+1]){
        verified = false;
      }
    }
    if(verified){
      std::cout << "SUCCESS: Sorted array verified in order.\n";
    }
    else{
      std::cout << "FAIL: Sorted array is not in order.\n";
    }
    return verified;
  }

  void printHeap(){
    if(arrLength > 0){
      for(int i = 1; i <= arrLength; i++){
        std::cout << arr[i] << " ";
      }
    }
    else{
      std::cout << "No array to print.";
    }
    std::cout << "\n";
  }
  
  void printSorted(){
    if(sortedLength > 0){
      for(int i = 1; i <= sortedLength; i++){
        std::cout << sorted[i] << " ";
      }
    }
    else{
      std::cout << "No array to print.";
    }
    std::cout << "\n";
  }


};

int main(){
  
  int seed = 5;
  srand (seed);

  // Fyi, this constructor calls 'generate', which generates the random values
  // sets initial length global vars, and calls buildheap. If you want to test
  // some specific seed, change this value for your first set of data.
  MinHeap heap = MinHeap(25);
 
  heap.printHeap();
  heap.verifyHeap();
  
  heap.heapSort_modified();
  heap.printSorted();
  heap.verifySorted();

  heap.heapSort();
  heap.printSorted();
  heap.verifySorted();

  
  int normals = 0;
  int modifieds = 0;
  int runs = 10;
  std::cout << "\n";
  for(int i = 0; i < runs; i++){
    heap.generate(2000);
    heap.verifyHeap();
    heap.heapSort();
    heap.verifySorted();
    int heapComparisons = heap.comparisons;
    heap.comparisons = 0;
    heap.heapSort_modified();
    heap.verifySorted();
    int modifiedComparisons = heap.comparisons;
    std::cout << "Heapsort used " << heapComparisons << " comparisons.\n";
    std::cout << "Modified heapsort used " << modifiedComparisons << " comparisons.\n";
    normals += heapComparisons;
    modifieds += modifiedComparisons;
    std::cout << "\n";
  }
  
  std::cout << "Heapsort averaged " << normals/runs << " comparisons.\n";
  std::cout << "Modified heapsort averaged " << modifieds/runs << " comparisons.\n";



  std::cout << "Exiting...\n";
  return 0;
}
