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

// Can change this here to run different sizes (e.g. 100000, 200000... vs
// 1000, 2000, 3000...
#define MULTIPLIER 10000

#define NUMTRIALS 8

void sort(int* array, std::vector<int> increments, int size){
  /*
  //print before
  for(int print = 0; print < size; print++){
  std::cout << array[print] << " ";
  }
  std::cout << "\n";
  */

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

  /*
  //print after
  for(int print = 0; print < size; print++){
  std::cout << array[print] << " ";
  }
  std::cout << "\n\n";
  */
}

bool verifyArray(int* array, int size){
  for(int i = 0; i < size-1; i++){
    if(array[i] > array[i+1]){
      return false;
    }
  }
  return true;;

}


int main(int argc, char *argv[]){

  std::ifstream file("RLAB12.txt");
  std::string line;

  std::vector<int> increments[4];

  // Prepare vector array of increment values from file
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

  // Check increment vectors for testing. Confirmed working.
  /*
     for(int i = 0; i < 4; i++){
     for(std::vector<int>::size_type increment = 0; increment != increments[i].size(); increment++){
     std::cout << increments[i][increment] << " ";
     }
     std::cout << "\n";
     }
     */

  int numtypes = 4;
  int times[numtypes][NUMTRIALS];

  for(int sizerun = 0; sizerun < numtypes; sizerun++){
    int numtosort = (sizerun+1)*MULTIPLIER;
    for(int trial = 0; trial < NUMTRIALS; trial++){
      srand(trial);
      // to get between -3n and 3n
      int* array = new int[numtosort];
      for(int j = 0; j < numtosort; j++){
        array[j] = rand()%(6*numtosort) - (3*numtosort);
      }
      
      // Get clock
      clock_t t0 = clock();
      // Sort
      sort(array, increments[sizerun], numtosort);
      // Store elapsed clock cycles
      times[sizerun][trial] = clock() - t0;
      
      // Verify each.
      if(verifyArray(array, numtosort)){
        std::cout << "Verified array " << trial+1 << " of size " << numtosort << " sorted successfully.\n";
      }
      else{
        std::cout << "Array was not sorted in order.\n";
      }


    }
  }

  int colwidth = 9;
  std::cout << "\n";
  std::cout << std::left << std::setw(colwidth) << "Size" << "  ";
  for(int i = 0; i < NUMTRIALS; i++){
    int t_int = i+1;
    std::string t_string = "T" + std::to_string(i+1) + " clks";
    std::cout << std::left << std::setw(colwidth) << t_string;
  }
  std::cout << std::left << std::setw(colwidth) << "Ttl clks";
  std::cout << std::left << std::setw(colwidth) << "Avg clks";
  std::cout << std::left << std::setw(colwidth) << "AvOps/clk";

  std::cout << "\n";
  for(int sizerun = 0; sizerun < numtypes; sizerun++){
    int numtosort = (sizerun+1)*MULTIPLIER;
    std::cout << std::setw(colwidth) << std::left << std::setw(colwidth) << numtosort << ": ";
    int total_time = 0;
    for(int trial = 0; trial < NUMTRIALS; trial++){
      std::cout << std::left << std::setw(colwidth) << times[sizerun][trial];
      total_time += times[sizerun][trial];
      

    }
    std::cout << std::left << std::setw(colwidth) << total_time;
    std::cout << std::left << std::setw(colwidth) << total_time / NUMTRIALS;
    std::cout << std::left << std::setw(colwidth) << (double)(numtosort * 4) / total_time;
    std::cout << "\n";
  }




  std::cout << "Exiting...\n";
  return 0;
}








