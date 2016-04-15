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

    m_next_name = nullptr;
    m_next_phone = nullptr;
    m_next_area = nullptr;
  }

  void setNextName(DicNode* a_next){
    m_next_name = a_next;
  }
  void setNextArea(DicNode* a_next){
    m_next_area = a_next;
  }
  void setNextPhone(DicNode* a_next){
    m_next_phone = a_next;
  }



  DicNode* getNextByName(){
    return m_next_name;
  }
  DicNode* getNextByArea(){
    return m_next_area;
  }
  DicNode* getNextByPhone(){
    return m_next_phone;
  }


  std::string getName(){
    return name;
  }
  std::string getPhoneNumber(){
    return phonenumber;
  }
  std::string getAddress(){
    return address;
  }
  std::string getCharges(){
    return charges;
  }

private:
std::string name;
std::string address;
std::string phonenumber;
std::string charges;
DicNode* m_next_name;
DicNode* m_next_area;
DicNode* m_next_phone;


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
    for(int i = 0; i < 47; i++){
      DicNode* tempptr = nameTable[i];
      if(tempptr != nullptr){
        std::cout << nameHash(tempptr -> getName()) << "\n";
      }
      while(tempptr != nullptr){
        std::cout << tempptr -> getName() << "\n";
        tempptr = tempptr -> getNextByName();
      }
      std::cout << "\n";
    }
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
    //buildPhoneTable();
    //buildAreaCodeTable();
  }

  // Search nameTable for a_name and return a pointer to it if found, else
  // return a nullptr.
  DicNode* findByName(DicNode* item){
    if(!nameTableBuilt){
      return nullptr;
    }
    int namehash = nameHash(item -> getName());
    DicNode* current_node = nameTable[namehash];
    while(current_node != nullptr){
      if((current_node -> getName()).compare(item -> getName()) == 0 &&
        (current_node -> getPhoneNumber()).compare(item -> getPhoneNumber()) == 0 &&
        (current_node -> getAddress()).compare(item -> getAddress()) == 0 &&
        (current_node -> getCharges()).compare(item -> getCharges()) == 0){
        return current_node;
      }
      current_node = current_node -> getNextByName();
    }
    return nullptr;
  }

  DicNode* findByAreaCode(DicNode* item){
    if(!areaCodeTableBuilt){
      return nullptr;
    }
    int areacodehash = areacodeHash(item -> getPhoneNumber());
    DicNode* current_node = areaCodeTable[areacodehash];
    while(current_node != nullptr){
      if((current_node -> getName()).compare(item -> getName()) == 0 &&
        (current_node -> getPhoneNumber()).compare(item -> getPhoneNumber()) == 0 &&
        (current_node -> getAddress()).compare(item -> getAddress()) == 0 &&
        (current_node -> getCharges()).compare(item -> getCharges()) == 0){
        return current_node;
      }
      current_node = current_node -> getNextByArea();
    }
    return nullptr;
  }

  DicNode* findByPhoneNumber(DicNode* item){
    if(!phoneTableBuilt){
      return nullptr;
    }
    int phonehash = phoneHash(item -> getPhoneNumber());
    DicNode* current_node = phoneTable[phonehash];
    while(current_node != nullptr){
      if((current_node -> getName()).compare(item -> getName()) == 0 &&
        (current_node -> getPhoneNumber()).compare(item -> getPhoneNumber()) == 0 &&
        (current_node -> getAddress()).compare(item -> getAddress()) == 0 &&
        (current_node -> getCharges()).compare(item -> getCharges()) == 0){
        return current_node;
      }
      current_node = current_node -> getNextByPhone();
    }
    return nullptr;
  }

  void addToNameTable(DicNode* item){
    // Get the top hash table node
    int hash = nameHash(item -> getName());
    DicNode* hash_node = nameTable[hash];
   
    // Check if already exists elsewhere and remember location
    DicNode* found_node = nullptr;
    if(findByAreaCode(item) != nullptr){
      found_node = findByAreaCode(item);
    }
    else if(findByPhoneNumber(item) != nullptr){
      found_node = findByPhoneNumber(item);
    }
    
    // If nullptr at this hash value, make a new node
    if(hash_node == nullptr){
      nameTable[hash] = item;
    }
    // If there is a node, find where next nullptr is
    else{
      // Keep looking for nullptr while next node exists
      while(hash_node -> getNextByName() != nullptr){
        hash_node = hash_node -> getNextByName();
      }
      // Now we know that NEXT node is null, so we can set next to a new one
      // If search for existing node was successful
      if(found_node != nullptr){
        hash_node -> setNextName(found_node);
      }
      // If not, add new node to linked list
      else{
        hash_node -> setNextName(item);
      }
    }
  }

  void addToPhoneTable(DicNode* item){
  
  }
 
  void addToAreaCodeTable(DicNode* item){
  
  }

  void buildNameTable(){
    
    // For every name
    for(int i = 0; i < numentries; i++){
      addToNameTable(new DicNode(namelist[i], addresslist[i], phonelist[i], chargeslist[i]));
    }
    nameTableBuilt = true;
  }

  void buildPhoneTable(){
    // For every phone number
    for(int i = 0; i < numentries; i++){
      addToPhoneTable(new DicNode(namelist[i], addresslist[i], phonelist[i], chargeslist[i]));
    }
    phoneTableBuilt = true;

  }

  void buildAreaCodeTable(){
    // For every phone number
    for(int i = 0; i < numentries; i++){
      addToAreaCodeTable(new DicNode(namelist[i], addresslist[i], phonelist[i], chargeslist[i]));
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











