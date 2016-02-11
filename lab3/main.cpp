
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Timer.cpp"

double* insert_sort(double* arr, int size){
  int j;
  double temp;
  for(int i = 2; i < size; i++){
    j = i;
    temp = arr[i];
    while(temp < arr[j-1]){
      arr[j] = arr[j-1];
      j = j - 1;
    }
    arr[j] = temp;
  }
  return arr;
}

double* getRandomArray(int size, int l_bound, int u_bound){
  double* arr = new double[size];
  arr[0] = -100000;
  for(int i = 1; i < size; i++){
    arr[i] = rand()%(u_bound-l_bound + 1) + l_bound;
  }
  return arr;
}

int main(){

  Timer timer = Timer();
  srand (time(NULL));


  int size = 10;
  double* arr = new double[size];
  int iterations = 10;

  std::cout << "Running " << iterations << " iterations of insertion sort...\n";
  for(int i = 0; i < iterations; i++){
    arr = getRandomArray(size, -40000, 40000);
    
    timer.start();
    insert_sort(arr, size);
    timer.printTime(timer.stop());
    
    for(int i = 0; i < size; i++){
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Exiting...\n";



  return 0;
}
