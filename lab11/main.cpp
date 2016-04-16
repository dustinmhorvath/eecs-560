/*
 * Dustin Horvath
 *
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "StackOfBoxes.h"
// used for pretty output
#include <iomanip>


#define MAXSIDE 50

class Graph{
public:

int matrix[MAXSIDE][MAXSIDE] = {{0}};
int m_height;
int m_width;

  Graph(int sidelength){
    m_height = sidelength;
    m_width = sidelength;
  }

  bool destroyCycles(int node) {
    StackOfBoxes stack = StackOfBoxes();
    int temp_visited[m_width] = {false};

    stack.push(node);
    int parent;

    while (!stack.isEmpty()) {
      int temp_node = stack.pop();
      std::cout << temp_node << "\n";
      if (temp_visited[temp_node]) {
        matrix[parent][temp_node] = 0;
        return true;
      }
      temp_visited[temp_node] = true;

      for (int i = m_width-1; i >= 0; i--){
        if (matrix[temp_node][i] > 0 && !temp_visited[i] && temp_node != i) {
          stack.push(i);
          parent = temp_node;
        }
      }
    }
    return false;
  }

  
  void printMatrix(){
    int colwidth = 3;
    for(int i = 0; i < m_height; i++){
      for(int j = 0; j < m_width; j++){
        std::cout << std::right << std::setw(colwidth) << matrix[i][j];
      }
      std::cout << "\n";
    }
  }


};

int main(int argc, char *argv[]){
  std::string filename = "";
  if(argc < 2){
    std::cout << "Please provide filename as input.\n";
    exit(1);
  }
  else{
    filename = argv[1];
  }

  std::ifstream file(filename);
  std::string line;

  int width = 0;
  int height = 0;
  int value;

  while(std::getline(file, line)){
    height++;
  }

  // Reset file pointer after traversal
  file.clear();
  file.seekg(0);

  Graph graph = Graph(height);

  height = 0;
  while(std::getline(file, line)){
    int i  = 0;
    std::stringstream ss(line);
    while(ss >> value){
      graph.matrix[height][i] = value;
      i++;
    }
    width = i;
    height++;
  }

  graph.printMatrix();
  while(graph.destroyCycles(0));
  graph.printMatrix();

  /*
  //std::cout << width << " " << height << "\n";
  stack.push(0);
  bool visited[height] = {false};
  while(!stack.isEmpty()){
    int row = stack.pop();
    for(int i = width-1; i >= 0; i--){
      if(matrix[row][i] > 0 && !visited[i]){
        stack.push(i);
      }
      else if(stack.search(i)){
        visited[i] = true;
      }
      else{
        matrix[row][i] = 0;
      }
      
    }
    visited[row] = true;
  }
  */


  std::cout << "Exiting...\n";
  return 0;
}








