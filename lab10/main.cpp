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
#include <vector>

class DisjSets{

public:
  DisjSets(int width, int height){
    m_width = width;
    m_height = height;
    numconnected = m_width*(m_height);
    connected = new int[numconnected];
    for(int i = 0; i < numconnected; i++){
      connected[i]= -1;
    }

    numvert = (m_width-1)*m_height;
    vertical = new int[numvert];
    m_width*(m_height-1);
    for(int i = 0; i < numvert; i++){
      vertical[i]= 0;
    }

    numhor = m_width*(m_height-1);
    horizontal = new int[numhor];
    for(int i = 0; i < numhor; i++){
      horizontal[i]= 0;
    }

  }

  void unionSets(int root1, int root2){
    if(connected[root2] < connected[root1]){
      connected[root1] = root2;
    }
    else{
      if(connected[root1] == connected[root2]){
        --connected[root1];
      }
      connected[root2] = root1;
    }
  }

  void buildmaze(){
    
    for(int i = 0; i < numconnected-1; i++){
      int wall = rand()%4;
      int cell = i;
      // North
        if(wall == 0 && cell >= m_width){
          unionSets(cell, cell-m_width);
          horizontal[cell-m_width] = 1;
        }
        // East
        else if(wall == 1 && (cell+1)%m_width != 0){
          unionSets(cell, cell+1);
          vertical[cell - cell/m_width] = 1;
        }
        // South
        else if(wall == 2 && (cell+m_width) < m_width*m_height){
          unionSets(cell, cell+m_width);
          horizontal[cell] = 1;
        }
        // West
        else if(wall == 3 && cell%m_width != 0){
          unionSets(cell, cell-1);
          vertical[cell - cell/m_width - 1] = 1;
        }
        else{
          i--;
        }
        

      

    }
  }

  int find(int x) const {
    if(connected[x] < 0){
      return x;
    }
    else{
      return find(connected[x]);
    }
  }

  void printvalues(){
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

  }

  void print(){
    int colwidth = 1;
    for(int i = 0; i < m_width; i++){
      std::cout << std::left << std::setw(colwidth) << " _";
    }
    std::cout << "\n";
    for(int i = 0; i < m_height; i++){
      std::cout << std::left << std::setw(colwidth) << "|";
      for(int j = 0; j < m_width; j++){
        int cell = j + i*m_width;

        if(horizontal[cell] == 1 && cell+m_width <= m_height*m_width){
          std::cout << std::left << std::setw(colwidth) << "";
        }
        else{
          std::cout << std::left << std::setw(colwidth) << "_";
        }

        if(vertical[cell - cell/m_width ] == 1 && (cell+1)%m_width != 0){
          std::cout << std::left << std::setw(colwidth) << "";
        }
        else{
          std::cout << std::left << std::setw(colwidth) << "|";
        }

      }
      std::cout << "\n";
    }
  }


  private:
  int* connected;
  int* vertical;
  int* horizontal;
  int numvert;
  int numhor;
  int numconnected;
  int m_width;
  int m_height;

  };


  int main(){

    int seed = 0;
    srand (seed);

    clock_t t0;
    t0 = clock();

    int width = 5;
    int height = 5;


    DisjSets disset = DisjSets(width, height);
    disset.print();
    disset.buildmaze();
//    std::cout << "find 2: " << disset.find(2) << "\n";
//    disset.printvalues();
    disset.print();
    disset.printvalues();




    std::cout << "\n";




  }

