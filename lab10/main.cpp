/*
 * Dustin Horvath
 *
 *
 */

#include <iostream>
// used for pretty output
#include <iomanip>

// for fun
#include <queue>

// These are used down in main(), and controlled here for convenience
#define WIDTH 75
#define HEIGHT 23
#define SEED 3


class Disjoint{

public:
  Disjoint(int width, int height){
    m_width = width;
    m_height = height;
    numconnected = m_width*(m_height);
    connected = new int[numconnected];
    for(int i = 0; i < numconnected; i++){
      connected[i]= -1;
    }

    numvisited = m_width*(m_height);
    visited = new bool[numvisited];
    for(int i = 0; i < numvisited; i++){
      visited[i]= false;
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
    // NOTE: THIS TERRIBLE VERSION FROM THE TEXTBOOK DOESN'T WORK
    //  JUST AN FYI
    /*if(connected[root2] < connected[root1]){
      connected[root1] = root2;
      }
      else{
      if(connected[root1] == connected[root2]){
      --connected[root1];
      }
      connected[root2] = root1;
      }*/

    // NO LUCK WITH THIS EITHER
    //connected[root2] = root1;

    connected[find(root1)] = find(root2);
  }

  void BFS(){
    std::queue<int> q = std::queue<int>();
    q.push(0);
    while(!q.empty()){
      int cell = q.front();
      q.pop();
      visited[cell] = true;
      if(cell == m_width*m_height-1){
        std::cout << "Traversed maze from cell 0 to cell " << cell << " using BFS.\n";
        return;
      }
      else{
        for(int i = 0; i < 4; i++){
          if(i == 0 && cell >= m_width && !visited[cell-m_width] && horizontal[cell-m_width] == 1){
            q.push(cell-m_width);
          }
          // EAST
          else if(i == 1 && (cell+1)%m_width != 0 && !visited[cell+1] && vertical[cell - cell/m_width] == 1){
            q.push(cell+1);
          }
          // SOUTH
          else if(i == 2 && (cell+m_width) < m_width*m_height && !visited[cell+m_width] && horizontal[cell] == 1){
            q.push(cell+m_width);
          }
          // WEST
          else if(i == 3 && cell%m_width != 0 && !visited[cell-1] && vertical[cell - cell/m_width - 1] == 1){
            q.push(cell-1);
          }
        }
      }
    }
    std::cout << "Could not find exit from entrance using BFS.\n";
  }

  void buildmaze(){

    int cell = 0;
    int wall = 0;
    // iterate across 'connected' array cells
    for(int i = 0; i < numconnected - 1; i++){
      // pick a wall at random
      wall = rand()%4;
      cell = i;

      // For each, check if on an edge, and check if other side of wall      
      // is already in the same set.
      // NORTH
      if(wall == 0 && cell >= m_width && find(cell) != find(cell-m_width)){
        unionSets(cell, cell-m_width);
        horizontal[cell-m_width] = 1;
      }
      // EAST
      else if(wall == 1 && (cell+1)%m_width != 0 && find(cell) != find(cell+1)){
        unionSets(cell, cell+1);
        vertical[cell - cell/m_width] = 1;
      }
      // SOUTH
      else if(wall == 2 && (cell+m_width) < m_width*m_height && find(cell) != find(cell+m_width)){
        unionSets(cell, cell+m_width);
        horizontal[cell] = 1;
      }
      // WEST
      else if(wall == 3 && cell%m_width != 0 && find(cell) != find(cell-1)){
        unionSets(cell, cell-1);
        vertical[cell - cell/m_width - 1] = 1;
      }
      // If all the attempts to union it with another cell failed, then roll
      // back the iterator and try again. This is generally for cells against
      // the edge.
      else{
        i--;
      }

    }
  }

  // From the textbook. It actually works, if you can believe it.
  int find(int x) const {
    if(connected[x] < 0){
      return x;
    }
    else{
      return find(connected[x]);
    }
  }

  // Prints all 3 arrays. For testing.
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

    //print top row
    std::cout << std::left << std::setw(colwidth) << "  ";
    for(int i = 1; i < m_width; i++){
      std::cout << std::left << std::setw(colwidth) << " _";
    }

    std::cout << "\n";
    for(int i = 0; i < m_height; i++){
      // If not first row, start with a wall
      if(i==0){
        std::cout << std::left << std::setw(colwidth) << "";
      }
      else{
        std::cout << std::left << std::setw(colwidth) << "|";
      }
      for(int j = 0; j < m_width; j++){
        int cell = j + i*m_width;

        if(horizontal[cell] == 1 && cell+m_width <= m_height*m_width){
          std::cout << std::left << std::setw(colwidth) << "";
        }
        else if(i!=m_height-1 || j!=m_width-1){
          std::cout << std::left << std::setw(colwidth) << "_";
        }

        if(vertical[cell - cell/m_width ] == 1 && (cell+1)%m_width != 0){
          std::cout << std::left << std::setw(colwidth) << "";
        }
        // If not last cell of maze, print a wall
        else if(i!=m_height-1 || j!=m_width-1){
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
  bool* visited;
  int numvert;
  int numvisited;
  int numhor;
  int numconnected;
  int m_width;
  int m_height;

};


int main(){

  int seed = SEED;
  srand (seed);

  clock_t t0, t1;

  int width = WIDTH;
  int height = HEIGHT;


  Disjoint disset = Disjoint(width, height);
  disset.print();
  std::cout << "\nBuilding maze....\n\n";
  t0 = clock();
  disset.buildmaze();
  t1 = clock();
  //    std::cout << "find 2: " << disset.find(2) << "\n";
  //    disset.printvalues();
  disset.print();
  std::cout << "\nMaze built in " << t1-t0 << " cycles.\n";
  //disset.printvalues();
  //std::cout << disset.find(1) << "\n";
  //std::cout << disset.find(11) << "\n";

  disset.BFS();

  std::cout << "\n";




}

