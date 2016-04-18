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

  static bool compareDicNodes(DicNode* item1, DicNode* item2){
    if( (item1 -> getName()).compare(         item2 -> getName()          ) == 0 &&
        (item1 -> getPhoneNumber()).compare(  item2 -> getPhoneNumber()   ) == 0 &&
        (item1 -> getAddress()).compare(      item2 -> getAddress()       ) == 0 &&
        (item1 -> getCharges()).compare(      item2 -> getCharges()       ) == 0){
      return true;
    }
    else{
      return false;
    }
  }


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
    printNameTableNodes();
    printPhoneTableNodes();
    printAreaCodeTableNodes();
  }

  void printNameTableNodes(){
    int counter = 0;
    for(int i = 0; i < 47; i++){
      DicNode* tempptr = nameTable[i];
      if(tempptr != nullptr){
        std::cout << nameHash(tempptr -> getName()) << "\n";
      }
      while(tempptr != nullptr){
        std::cout << tempptr -> getName() << "\n";
        tempptr = tempptr -> getNextByName();
        counter++;
      }
      std::cout << "\n";
    }
    std::cout << "Found " << counter << " nodes.\n\n";

  }

  void printPhoneTableNodes(){
    int counter = 0;
    for(int i = 0; i < 53; i++){
      DicNode* tempptr = phoneTable[i];
      if(tempptr != nullptr){
        std::cout << phoneHash(tempptr -> getPhoneNumber()) << "\n";
      }
      while(tempptr != nullptr){
        std::cout << tempptr -> getPhoneNumber() << "\n";
        tempptr = tempptr -> getNextByPhone();
        counter++;
      }
      std::cout << "\n";
    }
    std::cout << "Found " << counter << " nodes.\n\n";

  }

  void printAreaCodeTableNodes(){
    int counter = 0;
    for(int i = 0; i < 113; i++){
      DicNode* tempptr = areaCodeTable[i];
      if(tempptr != nullptr){
        std::cout << areacodeHash(tempptr -> getPhoneNumber()) << "\n";
      }
      while(tempptr != nullptr){
        std::cout << tempptr -> getPhoneNumber() << "\n";
        tempptr = tempptr -> getNextByArea();
        counter++;
      }
      std::cout << "\n";
    }
    std::cout << "Found " << counter << " nodes.\n\n";

  }

  bool d_addByName(DicNode* create){
    addToNameTable(create);
    addToPhoneTable(create);
    addToAreaCodeTable(create);
    return true;
  }

  bool d_addByPhone(DicNode* create){
    addToPhoneTable(create);
    addToNameTable(create);
    addToAreaCodeTable(create);
    return true;
  }

  // Finds a node by name, routes pointers around it from its parents to its
  // children, then returns the node in question.
  // REQUIRES CALLER DESTROY NODE THEY RECEIVE
  DicNode* d_removeByName(std::string name){
    // Get node by name
    DicNode* node = getFirstByName(name);
    // Score us some hash yo
    if(node == nullptr){
      return nullptr;
    }
    int namehash = nameHash(node -> getName());
    int phonehash = phoneHash(node -> getPhoneNumber());
    int areahash = areacodeHash(node -> getPhoneNumber());
    
    // For each, check if has no parent
    if(compareDicNodes(nameTable[namehash], node)){
      nameTable[namehash] = node -> getNextByName();
    }
    // If has a parent, route appropriate pointers over it from parent to
    // child.
    else{
      DicNode* nameparent = getParentByName(node);
      DicNode* namechild = node -> getNextByName(); 
      nameparent -> setNextName(namechild);
    }
    if(compareDicNodes(phoneTable[phonehash], node)){
      phoneTable[phonehash] = node -> getNextByPhone();
    }
    else{
      DicNode* phoneparent = getParentByPhone(node);
      DicNode* phonechild = node -> getNextByPhone();
      phoneparent -> setNextPhone(phonechild);
    }
    if(compareDicNodes(areaCodeTable[areahash], node)){
      areaCodeTable[areahash] = node -> getNextByArea();
    }
    else{
      DicNode* areacodeparent = getParentByArea(node);
      DicNode* areacodechild = node -> getNextByArea();
      areacodeparent -> setNextArea(areacodechild);
    }
    
    // Return the node, which will need destroyed by caller
    return node;
  }

  void d_printByAreaCode(std::string area){
    int areacodehash = areacodeHash(area);
    DicNode* currentnode = areaCodeTable[areacodehash];
    while(currentnode != nullptr){
      if((currentnode -> getPhoneNumber()).substr(0,3).compare(area) == 0){
        std::cout << currentnode -> getName() << "  " << currentnode -> getPhoneNumber() << "\n";
      }
      currentnode = currentnode -> getNextByArea();
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
    buildPhoneTable();
    buildAreaCodeTable();
  }

  // Returns the first node with 'name'
  DicNode* getFirstByName(std::string name){
    if(!nameTableBuilt){
      return nullptr;
    }
    int namehash = nameHash(name);
    std::cout << namehash << "\n";
    DicNode* current_node = nameTable[namehash];

    while(current_node != nullptr){
      if((current_node -> getName()).compare(name) == 0){
        return current_node;
      }
      current_node = current_node -> getNextByName();
    }
    return nullptr;
  }

  // Returns the parent of 'item' if it has a parent in the nametable
  DicNode* getParentByName(DicNode* item){
    int namehash = nameHash(item -> getName());
    DicNode* current_node = nameTable[namehash];
    if(current_node == nullptr){
      return nullptr;
    }
    // These are broken to avoid segfaults
    else if(current_node -> getNextByName() == nullptr){
      return nullptr;
    }

    while(current_node -> getNextByName() != nullptr){
      if(compareDicNodes(current_node -> getNextByName(), item)){
        return current_node;
      }
      current_node = current_node -> getNextByName();
    }
    return nullptr;
  }
  // Returns the parent of 'item' if it has a parent in the phonetable
  DicNode* getParentByPhone(DicNode* item){
    int phonehash = phoneHash(item -> getPhoneNumber());
    DicNode* current_node = phoneTable[phonehash];
    if(current_node == nullptr){
      return nullptr;
    }
    // These are broken to avoid segfaults
    else if(current_node -> getNextByPhone() == nullptr){
      return nullptr;
    }

    while(current_node -> getNextByPhone() != nullptr){
      if(compareDicNodes(current_node -> getNextByPhone(), item)){
        return current_node;
      }
      current_node = current_node -> getNextByPhone();
    }
    return nullptr;
  }
  // Returns the parent of 'item' if it has a parent in the areaCodeTable
  DicNode* getParentByArea(DicNode* item){
    int areahash = areacodeHash(item -> getPhoneNumber());
    DicNode* current_node = areaCodeTable[areahash];
    if(current_node == nullptr){
      return nullptr;
    }
    // These are broken to avoid segfaults
    else if(current_node -> getNextByArea() == nullptr){
      return nullptr;
    }

    while(current_node -> getNextByArea() != nullptr){
      if(compareDicNodes(current_node -> getNextByArea(), item)){
        return current_node;
      }
      current_node = current_node -> getNextByArea();
    }
    return nullptr;
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

  DicNode* findByArea(DicNode* item){
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
    if(findByArea(item) != nullptr){
      found_node = findByArea(item);
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
    // Get the top hash table node
    int hash = phoneHash(item -> getPhoneNumber());
    DicNode* hash_node = phoneTable[hash];

    // Check if already exists elsewhere and remember location
    DicNode* found_node = nullptr;
    if(findByArea(item) != nullptr){
      found_node = findByArea(item);
    }
    else if(findByName(item) != nullptr){
      found_node = findByName(item);
    }

    // If nullptr at this hash value, make a new node
    if(hash_node == nullptr){
      phoneTable[hash] = item;
    }
    // If there is a node, find where next nullptr is
    else{
      // Keep looking for nullptr while next node exists
      while(hash_node -> getNextByPhone() != nullptr){
        hash_node = hash_node -> getNextByPhone();
      }
      // Now we know that NEXT node is null, so we can set next to a new one
      // If search for existing node was successful
      if(found_node != nullptr){
        hash_node -> setNextPhone(found_node);
      }
      // If not, add new node to linked list
      else{
        hash_node -> setNextPhone(item);
      }
    }

  }

  void addToAreaCodeTable(DicNode* item){
    // Get the top hash table node
    int hash = areacodeHash(item -> getPhoneNumber());
    DicNode* hash_node = areaCodeTable[hash];

    // Check if already exists elsewhere and remember location
    DicNode* found_node = nullptr;
    if(findByPhoneNumber(item) != nullptr){
      found_node = findByPhoneNumber(item);
    }
    else if(findByName(item) != nullptr){
      found_node = findByName(item);
    }

    // If nullptr at this hash value, make a new node
    if(hash_node == nullptr){
      areaCodeTable[hash] = item;
    }
    // If there is a node, find where next nullptr is
    else{
      // Keep looking for nullptr while next node exists
      while(hash_node -> getNextByArea() != nullptr){
        hash_node = hash_node -> getNextByArea();
      }
      // Now we know that NEXT node is null, so we can set next to a new one
      // If search for existing node was successful
      if(found_node != nullptr){
        hash_node -> setNextArea(found_node);
      }
      // If not, add new node to linked list
      else{
        hash_node -> setNextArea(item);
      }
    }

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
  //table.test();

  std::string name;
  std::string address;
  std::string phone;
  std::string charges;
  bool cont = true;
  int option = 0;
  std::string tempstring;
  DicNode* tempnode;
  while(cont){
    std::cout << "1. Insert new by name.\n";
    std::cout << "2. Insert new by phone number.\n";
    std::cout << "3. Remove a customer by name.\n";
    std::cout << "4. Insert a customer by phone.\n";
    std::cout << "5. Add a payment by name or phone.\n";
    std::cout << "6. Add a charge by name or phone.\n";
    std::cout << "7. Print a bill by name.\n";
    std::cout << "8. Print a bill by phone.\n";
    std::cout << "9. Print all customers for a namehash.\n";
    std::cout << "10. Print monthly billing schedule.\n";
    std::cout << "11. Print all customers in area code.\n";
    std::cout << "12. Exit.\n";
    std::cout << "Select an option: ";
    std::cin >> option;
    // This cin bullshit is absolutely absurd. This has been a problem for
    // YEARS and should have been fixed **YEARS** ago. Compiler devs should be
    // ashamed. And it STILL doesn't work right.
    std::cin.clear();
    std::cin.ignore(10, '\n');

    switch(option){
    case 1:
      std::cout << "Provide name: ";
      std::getline(std::cin, name);
      std::cin.clear();
      std::cout << "Provide address: ";
      std::getline(std::cin, address);
      std::cin.clear();
      std::cout << "Provide phone number: ";
      std::cin >> phone;
      std::cin.clear();
      std::cin.ignore(10, '\n');
      std::cout << "Provide charges: ";
      std::cin >> charges;
      std::cin.clear();
      std::cin.ignore(10, '\n');
      tempnode = new DicNode(name, address, phone, charges);
      table.d_addByName(tempnode);
      break;
    case 2:
      std::cout << "Provide name: ";
      std::getline(std::cin, name);
      std::cin.clear();
      std::cin.ignore(10, '\n');
      std::cout << "Provide address: ";
      std::getline(std::cin, address);
      std::cin.clear();
      std::cin.ignore(10, '\n');
      std::cout << "Provide phone number: ";
      std::cin >> phone;
      std::cin.clear();
      std::cin.ignore(10, '\n');
      std::cout << "Provide charges: ";
      std::cin >> charges;
      std::cin.clear();
      std::cin.ignore(10, '\n');
      tempnode = new DicNode(name, address, phone, charges);
      table.d_addByPhone(tempnode);
      break;
    case 3:
      std::cout << "Customer to remove: ";
      std::getline(std::cin, tempstring);
      std::cin.clear();
      tempstring = trim_copy(tempstring);
      tempnode = table.d_removeByName(tempstring);
      if(tempnode == nullptr){
        std::cout << "Could not find customer with name " << tempstring << ".\n";
      }
      else{
        std::cout << "Charges for " << tempnode -> getName() << " are " << tempnode -> getCharges() << ".\n";
      }
      break;
    case 4:
      //        table.d_removeByPhone();
      break;

    case 11:
      std::cout << "Area code to print: ";
      std::cin >> tempstring;
      std::cin.clear();
      std::cin.ignore();
      table.d_printByAreaCode(tempstring);
      break;
    case 12:
      cont = false;
      break;
    default:
      std::cout << "Invalid input.\n";
      option = 0;
      break;
    }


  }

  std::cout << "Exiting...\n";
  return 0;
}











