/*
 * Dustin Horvath
 * Shellsort with statically-read list of gap values
 * Has abstract design of trial-runs, but static size (bleh) for each run.
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>

// Used for pretty output
#include <iomanip>
#include <vector>
// End pretty libraries


// ~~~~~~~~CONTROLS~~~~~~~~~
// Can change this here to run different sizes (e.g. 100000, 200000... vs
// 1000, 2000, 3000...
#define MULTIPLIER 100000
// This changes number of trials
#define NUMTRIALS 10



// Use a vector here because it lets me get the list of increments in an
// object easily.
void sort(int* array, std::vector<int> increments, int size){

  // Iterate over the read-in increment list for each shellsort size
  for (std::vector<int>::size_type increment = 0; increment != increments.size(); increment++){
    // Grab this here so I can make the code a bit tidier
    int skip = increments[increment];
    // Shellsort list normal
    for (int i = skip; i < size; i++){
      for (int j = i - skip; j >= 0 && array[j] > array[j+skip]; j -= skip){
        int temp = array[j];
        array[j] = array[skip + j];
        array[skip + j] = temp;
      }
    }
  }

 
}

// Zips over an array and makes sure it's sorted
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
        std::cout << "Verified trial " << std::setw(2) << trial+1 << " of size " << numtosort << " sorted successfully.\n";
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
  std::cout << std::left << std::setw(colwidth) << "Num/clk";

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
    std::cout << std::left << std::setw(colwidth) << (double)numtosort / (total_time / NUMTRIALS);
    std::cout << "\n";
  }




  std::cout << "\n\nExiting...\n";
  return 0;
}








