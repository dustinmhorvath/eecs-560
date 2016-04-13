/*
 * Dustin Horvath
 * 2729265
 * EECS 560
 * Fraction operation program
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define MAXENTRIES 500

class HashTable{
  HashTable(int size){
    

  }




}

inline std::string trim_right_copy(
    const std::string& s,
    const std::string& delimiters = " \f\n\r\t\v" )
{
  return s.substr( 0, s.find_last_not_of( delimiters ) + 1 );
}

inline std::string trim_left_copy(
    const std::string& s,
    const std::string& delimiters = " \f\n\r\t\v" )
{
  return s.substr( s.find_first_not_of( delimiters ) );
}

inline std::string trim_copy(
    const std::string& s,
    const std::string& delimiters = " \f\n\r\t\v" )
{
  return trim_left_copy( trim_right_copy( s, delimiters ), delimiters );
}

int phoneHash(std::string phonenumber){
  std::string lastfour = phonenumber.substr(6);
  return std::stoi(lastfour)%53;
}

int nameHash(std::string name){
  int a = (int)name.at(1);
  int b = (int)name.at(6);
  int c = (int)name.at(12);
  int value = a + b + c;

  return value%47;
}

int areacodeHash(std::string phonenumber){
  std::string areastring = phonenumber.substr(0,3);
  int areacode = std::stoi(areastring);
  return areacode;
}


int main(){

  // Initialize arrays with magic number
  std::string namelist[MAXENTRIES] = {-1};
  std::string addresslist[MAXENTRIES] = {-1};
  std::string phonelist[MAXENTRIES] = {-1};
  std::string chargeslist[MAXENTRIES] = {-1};


  std::string phonebookfile = "phonebook.txt";
  std::string datafile = "proj2data.txt";

  std::ifstream file(phonebookfile);
  std::string line;

  int numentries = 0;
  while(std::getline(file, line)){
    std::string name = line.substr(0,20);
    name = trim_copy(name);
    std::string address = line.substr(21,28);
    address = trim_copy(address);
    std::string phone = line.substr(49,13);
    phone = trim_copy(phone);
    std::string charges = line.substr(62,7);
    charges = trim_copy(charges);

    namelist[numentries] = name;
    addresslist[numentries] = address;
    phonelist[numentries] = phone;
    chargeslist[numentries] = charges;

    numentries++;
  }

  //std::cout << phoneHash(phonelist[0]) << "\n";
  //std::cout << nameHash(namelist[0]) << "\n";
  //std::cout << areacodeHash(phonelist[0]) << "\n";

  


  std::cout << "Exiting...\n";
  return 0;
}











