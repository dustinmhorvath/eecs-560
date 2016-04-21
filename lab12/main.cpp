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
#include <vector>

void sort(int* array, std::vector<int> increments, int size){
  //print before
  for(int print = 0; print < size; print++){
    std::cout << array[print] << " ";
  }
  std::cout << "\n";

  for (std::vector<int>::size_type increment = 0; increment != increments.size(); increment++){
    int skip = increments[increment];
    for (int i = skip; i <size; i++){
      for (int j = i - skip; j >= 0 && array[j] > array[j+skip]; j -= skip){
        int temp = array[j];
        array[j] = array[j+skip];
        array[j+skip] = temp;
      }
    }
  }
  
  //print after
  for(int print = 0; print < size; print++){
    std::cout << array[print] << " ";
  }
      std::cout << "\n";
}



int main(int argc, char *argv[]){

  std::ifstream file("MLAB12.txt");
  std::string line;

  std::vector<int> increments[4];

  int linenum = 0;
  while(std::getline(file, line)){
    std::istringstream iss(line);
    int num;
    std::string word;

    while (getline(iss, word, ',')){
      num = stoi(word);
      increments[linenum].push_back(num);
    }
    linenum++;
  }

  for(int i = 0; i < 4; i++){
    for(std::vector<int>::size_type increment = 0; increment != increments[i].size(); increment++){
  //    std::cout << increments[i][increment] << " ";
    }
  //    std::cout << "\n";
  }



  for(int run = 1; run < 5; run++){
    int n = run*10;
    for(int i = 0; i < 5; i++){
      srand(i);
      // to get between -3n and 3n
      int* array = new int[n];
      for(int j = 0; j < n; j++){
        array[j] = rand()%(6*n) - (3*n);
      }
      clock_t t0 = clock();

            
      sort(array, increments[run - 1], n);
      t0 = clock() - t0;

      
    }
  }



  std::cout << "Exiting...\n";
  return 0;
}








