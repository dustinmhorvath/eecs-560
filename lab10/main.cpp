/*
 * Dustin Horvath
 *
 *
 */

#include <iostream>
// used for floor
#include <math.h>
// used for pretty output
#include <iomanip>




int main(){

  int seed = 0;
  srand (seed);

  clock_t t0;
  t0 = clock();

  int width = 5;
  int height = 5;

  int numvert = (width-1)*height;
  int vertical[numvert];width*(height-1); //should initialize as zeroes
  for(int i = 0; i < numvert; i++){
    vertical[i]= 0;
  }

  int numhor = width*(height-1);
  int horizontal[numhor]; //should initialize as zeroes
  for(int i = 0; i < numhor; i++){
    horizontal[i]= 0;
  }

  int numconnected = width*(height);
  int connected[numconnected];
  for(int i = 0; i < numconnected; i++){
    connected[i]= -1;
  }

  int count = 0;
  int num = 50;
  //int cell = 0;
  //for(int node = 0; node < numconnected; node++){
  while(count < num){
    //cell = node;
    // Randomly select a cell
    int cell = rand()%(width*height);
    std::cout << "Cell: " << cell << "\n";
    // Check if it's connected already
    if(connected[cell] == -1){
      // Randomly select a wall
      int wall = rand()%4;
      std::cout << "Wall: " << wall << "\n\n";
      // North
      if(wall == 0 && cell >= width){
        connected[cell] = cell-width;
        horizontal[cell-width] = 1;
      }
      // East
      else if(wall == 1 && (cell+1)%width != 0){
        connected[cell] = cell+1;
        vertical[cell - cell/width] = 1;
      }
      // South
      else if(wall == 2 && (cell+width) < width*height){
        connected[cell] = cell+width;
        horizontal[cell] = 1;
      }
      // West
      else if(wall == 3 && cell%width != 0){
        connected[cell] = cell-1;
        vertical[cell - cell/width - 1] = 1;
      }

    }
    count++;
  }

  // TEST CHECK OUTPUT
  for(int i = 0; i < numvert; i++){
    std::cout << vertical[i] << " ";
  }
  std::cout << "\n";
  for(int i = 0; i < numhor; i++){
    std::cout << horizontal[i] << " ";
  }
  std::cout << "\n";
  for(int i = 0; i < numconnected; i++){
    std::cout << connected[i] << " ";
  }
  std::cout << "\n\n";
  // END TEST


  int colwidth = 1;
  for(int i = 0; i < width; i++){
    std::cout << std::left << std::setw(colwidth) << " _";
  }
  std::cout << "\n";
  for(int i = 0; i < height; i++){
    std::cout << std::left << std::setw(colwidth) << "|";
    for(int j = 0; j < width; j++){
      int cell = j + i*width;
      
      if(horizontal[cell] == 1 && cell+width <= height*width){
        std::cout << std::left << std::setw(colwidth) << "";
      }
      else{
        std::cout << std::left << std::setw(colwidth) << "_";
      }

      if(vertical[cell - cell/width ] == 1 && (cell+1)%width != 0){
        std::cout << std::left << std::setw(colwidth) << "";
      }
      else{
        std::cout << std::left << std::setw(colwidth) << "|";
      }
            
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  


}

