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
  //double coin = (double)rand() / RAND_MAX;

  //int floor = 1;
  //int ceiling = 50000;
  //int ops = floor + ( std::rand() % ( ceiling - floor + 1 ) );

  //rand()%(width*height) gets random cell
  //rand()%4 get random 0-3

  // NESW = 0,1,2,3
  // cell - width = N
  // cell + width = S
  // cell - 1 = W
  // cell + 1 = E


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

  int numconnected = width*(height-1);
  int connected[numconnected];
  for(int i = 0; i < numconnected; i++){
    connected[i]= -1;
  }

  int count = 0;
  int num = 15;
  while(count < num){
    // Randomly select a cell
    int cell = rand()%(width*height);
    std::cout << "Cell: " << cell << "\n";
    // Check if it's connected already
    if(connected[cell] == -1){
      // Randomly select a wall
      int wall = rand()%4;
      std::cout << "Wall: " << wall << "\n\n";
      // North
      if(wall == 0 && cell-width >= 0){
        connected[cell] = cell-width;
        horizontal[cell-width] = 1;
      }
      // East
      else if(wall == 1 && (cell+1)%width != 0 && cell+1 < width*height){
        connected[cell] = cell+1;
        vertical[cell - cell/width] = 1;
      }
      // South
      else if(wall == 2 && cell+width < width*height){
        connected[cell] = cell+width;
        horizontal[cell] = 1;
      }
      // West
      else if((cell-1)%width != 0 && cell-1 >= 0){
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
      int cell = j + i*5;
      
      if(horizontal[cell] == 1){
        std::cout << std::left << std::setw(colwidth) << "";
      }
      else{
        std::cout << std::left << std::setw(colwidth) << "_";
      }

      if(vertical[cell - cell/width ] == 1){
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

