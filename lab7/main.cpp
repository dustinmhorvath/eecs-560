
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

class MinHeap{
  public:

  int arr[101];
  int length;
  
  MinHeap(){
    arr[0] = -111;
    length = 0;
  }

  void buildHeap(int insert[], int n){
    // Copy the new values into the array
    for(int i = 0; i < n; i++){
      arr[i+1] = insert[i];
      length++;
    }

    // Does not use parameters anymore, all stored in member vars
    for(int i = floor(length/2); i > 0; i--){
      push_down(i);
    }
  }

  void push_down(int i){
    // moves an item down the heap until the correct spot for it is found
    // The item being moved down the heap starts in position i
    int val = arr[i];
    int position = i;
    bool cont = true;
    while( cont ){
      int k;
      if(arr[2*position] > arr[2*position + 1] && 2*position + 1 <= length){
        k = 2*position + 1;
      }
      else if(2*position <= length){
        k = 2*position;
      }
      else{
        arr[position] = val;
        cont = false;
      }

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

  // Verify function was tested by manually adding very high values to the
  // start of the heap and attempting to verify. Returned failure with bad
  // value.
  bool verify(){
    bool verified = true;
    std::cout << "Verifying...\n";
    for(int i = 1; i < length; i++){
      if( (arr[2*i + 1] < arr[i] && 2*i+1 <= length ) ||
        (arr[2*i] < arr[i] && 2*i <= length)  ){
        verified = false;
      }
    }
    if(verified){
      std::cout << "Array is sorted in MinHeap order.\n";
    }
    else{
      std::cout << "Array is not sorted in MinHeap order.\n";
    }
    return verified;
  }

  void print(){
    for(int i = 1; i <= length; i++){
      std::cout << arr[i] << " ";
    }
    std::cout << "\n";
  }

};

int main(){
  
  int numPoints = 25;
  int seed = 5;
  srand (seed);

  int generated[numPoints];

  MinHeap heap = MinHeap();

  std::cout << "Generating values.\n";
  for(int i = 0; i < numPoints; i++){
      generated[i] = 1 + rand() % (10000 - 1);
  }
  
  std::cout << "Building heap.\n";
  heap.buildHeap(generated, numPoints);   
  
  heap.print();
  
  heap.verify();
  
  
  
  std::cout << "Exiting...\n";
  return 0;
}
