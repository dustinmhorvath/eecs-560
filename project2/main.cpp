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

class DicNode{
  public:

  DicNode(std::string a_name, std::string a_address, std::string a_phone, std::string a_charges){
    name = a_name;
    address = a_address;
    phonenumber = a_phone;
    charges = a_charges;

    m_next = nullptr;
  }

  void setNext(DicNode* a_next){
    m_next = a_next;
  }

  DicNode* getNext(){
    return m_next;
  }

  std::string getName(){
    return name;
  }
  std::string getPhoneNumber(){
    return phonenumber;
  }
  std::string getcharges(){
    return charges;
  }

private:
std::string name;
std::string address;
std::string phonenumber;
std::string charges;
DicNode* m_next;


};



class HashTable{
public:

  HashTable(std::string names[], std::string addresses[], std::string phones[],
      std::string charges[], int a_numentries){

    numentries = a_numentries;

    namelist = names;
    addresslist = addresses;
    phonelist = phones;
    chargeslist = charges;

    nameTableBuilt = false;
    phoneTableBuilt = false;
    areaCodeTableBuilt = false;

    buildtable();

  }

  void test(){
    std::cout << phoneHash(phonelist[0]) << "\n";
    std::cout << areacodeHash(phonelist[0]) << "\n";
    std::cout << nameHash(namelist[0]) << "\n";
  }


private:
  std::string* namelist;
  std::string* addresslist;
  std::string* phonelist;
  std::string* chargeslist;

  int numentries;

  DicNode* nameTable[47] = {nullptr};
  DicNode* phoneTable[53] = {nullptr};
  DicNode* areaCodeTable[113] = {nullptr};

  bool nameTableBuilt;
  bool phoneTableBuilt;
  bool areaCodeTableBuilt;

  void buildtable(){
    buildNameTable();
    buildPhoneTable();
    buildAreaCodeTable();
  }

  // Search nameTable for a_name and return a pointer to it if found, else
  // return a nullptr.
  DicNode* findByName(std::string a_name){
    if(!nameTableBuilt){
      return nullptr;
    }
    int namehash = nameHash(a_name);
    DicNode* current_node = nameTable[namehash];
    while(current_node != nullptr){
      if((current_node -> getName()).compare(a_name) == 0){
        return current_node;
      }
      current_node = current_node -> getNext();
    }
    return nullptr;
  }

  DicNode* findByAreaCode(std::string phonenumber){
    if(!areaCodeTableBuilt){
      return nullptr;
    }
    int areacodehash = areacodeHash(phonenumber);
    DicNode* current_node = areaCodeTable[areacodehash];
    while(current_node != nullptr){
      if((current_node -> getPhoneNumber()).compare(phonenumber) == 0){
        return current_node;
      }
      current_node = current_node -> getNext();
    }
    return nullptr;
  }

  DicNode* findByPhoneNumber(std::string phonenumber){
    if(!phoneTableBuilt){
      return nullptr;
    }
    int phonehash = phoneHash(phonenumber);
    DicNode* current_node = phoneTable[phonehash];
    while(current_node != nullptr){
      if((current_node -> getPhoneNumber()).compare(phonenumber) == 0){
        return current_node;
      }
      current_node = current_node -> getNext();
    }
    return nullptr;
  }

  void addToNameTable(std::string name, std::string address, std::string phone, std::string charges){
    int hash = nameHash(name);
    DicNode* current_node = nameTable[hash];

    if(findByAreaCode(phone) != nullptr){
      nameTable[hash] = findByAreaCode(phone);
    }
    else if(findByPhoneNumber(phone) != nullptr){
      nameTable[hash] = findByPhoneNumber(phone);
    }
    else if(current_node != nullptr){
      while(current_node -> getNext() != nullptr){
        current_node = current_node -> getNext();
      }
      current_node -> setNext(new DicNode(name, address, phone, charges));
    }
    else{
      nameTable[hash] = new DicNode(name, address, phone, charges);
    }
  }

  void addToPhoneTable(std::string name, std::string address, std::string phone, std::string charges){
    int hash = phoneHash(name);
    DicNode* current_node = phoneTable[hash];

    if(findByAreaCode(phone) != nullptr){
      phoneTable[hash] = findByAreaCode(phone);
    }
    else if(findByName(name) != nullptr){
      phoneTable[hash] = findByName(name);
    }
    else if(current_node != nullptr){
      while(current_node -> getNext() != nullptr){
        current_node = current_node -> getNext();
      }
      current_node -> setNext(new DicNode(name, address, phone, charges));
    }
    else{
      phoneTable[hash] = new DicNode(name, address, phone, charges);
    }
  }
 
  void addToAreaCodeTable(std::string name, std::string address, std::string phone, std::string charges){

  }

  void buildNameTable(){
    
    // For every name
    for(int i = 0; i < numentries; i++){
      addToNameTable(namelist[i], addresslist[i], phonelist[i], chargeslist[i]);
    }
    nameTableBuilt = true;
  }

  void buildPhoneTable(){
    // For every phone number
    for(int i = 0; i < numentries; i++){
      addToPhoneTable(namelist[i], addresslist[i], phonelist[i], chargeslist[i]);
    }
    phoneTableBuilt = true;

  }

  void buildAreaCodeTable(){
    // For every phone number
    for(int i = 0; i < numentries; i++){
      addToAreaCodeTable(namelist[i], addresslist[i], phonelist[i], chargeslist[i]);
    }
    areaCodeTableBuilt = true;

  }

  int phoneHash(std::string phonenumber){
    std::string lastfour = phonenumber.substr(6);
    return std::stoi(lastfour)%53;
  }

  int nameHash(std::string name){
    int a = (int)name.at(1);
    int b = 0;
    if(name.length() > 6){
      b = (int)name.at(6);
    }
    int c = 0;
    if(name.length() > 12){
      c = (int)name.at(12);
    }
    int value = a + b + c;

    return value%47;
  }

  int areacodeHash(std::string phonenumber){
    std::string areastring = phonenumber.substr(0,3);
    int areacode = std::stoi(areastring);
    return (areacode*(areacode + 3)) % 113 ;
  }


};

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



int main(){


  std::string phonebookfile = "phonebook.txt";
  std::string datafile = "proj2data.txt";

  std::ifstream file(phonebookfile);
  std::string line;

  int numentries = 0;
  while(std::getline(file, line)){
    numentries++;
  }

  // Reset file pointer after traversal
  file.clear() ;
  file.seekg(0) ;

  // Initialize arrays with magic number
  std::string namelist[numentries] = {""};
  std::string addresslist[numentries] = {""};
  std::string phonelist[numentries] = {""};
  std::string chargeslist[numentries] = {""};

  int row = 0;
  while(std::getline(file, line)){
    std::string name = line.substr(0,20);
    name = trim_copy(name);
    std::string address = line.substr(21,28);
    address = trim_copy(address);
    std::string phone = line.substr(49,13);
    phone = trim_copy(phone);
    std::string charges = line.substr(62,7);
    charges = trim_copy(charges);

    namelist[row] = name;
    addresslist[row] = address;
    phonelist[row] = phone;
    chargeslist[row] = charges;

    row++;
  }

  HashTable table = HashTable(namelist, addresslist, phonelist, chargeslist, numentries);
  table.test();

  std::cout << "Exiting...\n";
  return 0;
}











