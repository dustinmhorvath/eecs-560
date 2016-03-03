
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

double* getRandomArray(int size, int l_bound, int u_bound){
  double* arr = new double[size];
  arr[0] = -100000;
  for(int i = 1; i < size; i++){
    arr[i] = rand()%(u_bound-l_bound + 1) + l_bound;
  }
  return arr;
}

int main(){
  int numPoints = 0;
  int seed = 1;

  std::cout << "How many points in the graph? ";
  std::cin >> numPoints;
  std::cout << "Value to use for seed? ";
  std::cin >> seed;

  srand (seed);

  // % = rand()/rand_max  is between 0 and 1
  //
  int arraySize = 0;

  for(int i = numPoints; i > 0; i--){
    arraySize = arraySize + i;
  }

  int graph[arraySize];
  bool visited[arraySize];
  
  for(int i = 0; i < arraySize; i++){
    visited[i] = false;
    if((double)rand()/RAND_MAX < 0.6){
      graph[i] = 1 + rand() % (20 - 1);
    }
    else{
      graph[i] = 0;
    }
  }

  


  
  
  
  
  
  
  for(int i = 0; i < arraySize; i++){
    std::cout << graph[i] << "\n";
  }

  std::cout << "Exiting...\n";
  return 0;
}
