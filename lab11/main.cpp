/*
 * Dustin Horvath
 *
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
// used for pretty output
#include <iomanip>
#include "StackOfBoxes.h"


#define MAXSIDE 50


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

  StackOfBoxes stack = StackOfBoxes();

  int matrix[MAXSIDE][MAXSIDE] = {0};
  int width = 0;
  int height = 0;
  int value;

  while(std::getline(file, line)){
    int i  = 0;
    std::stringstream ss(line);
    while(ss >> value){
      matrix[height][i] = value;
      i++;
    }
    width = i;
    height++;

  }


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


  int colwidth = 3;
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      std::cout << std::right << std::setw(colwidth) << matrix[i][j];
    }
    std::cout << "\n";
  }

  std::cout << "Exiting...\n";
  return 0;
}








