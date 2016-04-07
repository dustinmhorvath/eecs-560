
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <math.h>

double* getRandomArray(int size, int l_bound, int u_bound){
  double* arr = new double[size];
  arr[0] = -100000;
  for(int i = 1; i < size; i++){
    arr[i] = rand()%(u_bound-l_bound + 1) + l_bound;
  }
  return arr;
}

int getVisitedFromGraph(int index, int size){

  double temp = ((double)sqrt(size*size - 2*size - 8*index + 1) +size-1)/2;
  //int visited = floor(temp/(size-1));
  return floor(temp/size);
}

int sumArray(bool array[], int length){
  int sum;
  for(int i = 0; i < length; i++){
    if(array[i]){
      sum++;
    }
  }
  return sum;
}

int main(){
  int numPoints = 0;
  int seed = 1;

  std::cout << "How many points in the graph? ";
  std::cin >> numPoints;
  std::cout << "Value to use for seed? ";
  std::cin >> seed;

  srand (seed);

  int arraySize = 0;

  for(int i = numPoints - 1; i > 0; i--){
    arraySize = arraySize + i;
  }

  int graph[arraySize];
  bool visited[numPoints];
  
  std::cout << "\nConnected graph contains: \n";
  for(int i = 0; i < arraySize; i++){
    // 0.6 is what this should be, might be changed for testing
    if((double)rand()/RAND_MAX < 0.6){
      graph[i] = 1 + rand() % (20 - 1);
    }
    else{
      graph[i] = 0;
    }
    std::cout << graph[i] << " ";
  }
  std::cout << "\n";

  


  int numVis = 0;
  std::stack<int> q;
  q.push(0);
  while(!q.empty()){
    int index = q.top();
    visited[index] = true;
    numVis++;
    q.pop();

    // Maps from visited[] indeces to the graph[] indices
    int lower = (index * numPoints) - (index*(index+1)/2);
    int upper = (index + 1)*numPoints - 1 - (index)*(index+1)/2 - (index+1);

    int j = 0;
    for(int i = lower; i <= upper; i++){
      if(graph[i] > 0){
        if(!visited[index+j+1]){
          q.push((j+1+index));
          std::cout << "index = " << index << " is connected to " << j+1+index << "\n";


        }
      }
      j++;
    }

    for(int m = 0; m < numPoints; m++){
      int newlower = (m * numPoints) - (m*(m+1)/2);
      int newupper = (m + 1)*numPoints - 1 - (m)*(m+1)/2 - (m+1);

      int n = 0;
      bool hasVisited = false;
      for(int i = newlower; i <= newupper; i++){
        if(graph[i] > 0){
          if(visited[m+n+1]){
            hasVisited = true;


          }
        }
        n++;
      } 
      if(hasVisited && !visited[m]){
        q.push(m);
      }


    }


  }

  std::cout << "Visited contains: \n";
  for(int i = 0; i < numPoints; i++){
    if(visited[i]){
      std::cout << "1 ";
    }
    else
      std::cout << "0 ";
  }
  std::cout << std::endl;
  
 
  
  std::cout << "Exiting...\n";
  return 0;
}
