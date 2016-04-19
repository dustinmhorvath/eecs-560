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

#define NAMESIZE 48
#define PHONESIZE 54
#define AREASIZE 114

bool isDigits(const std::string &str){
  return str.find_first_not_of("0123456789") == std::string::npos;
}


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

  void payCharges(std::string value){
    /*double nodebalance;
      std::istringstream ( charges ) >> nodebalance;
      double payment;
      std::istringstream ( value ) >> payment;*/

    double nodebalance = std::atof(charges.c_str());
    double payment = std::atof(value.c_str());

    std::ostringstream sstream;
    sstream << (nodebalance - payment);

    charges = sstream.str();


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
    for(int i = 0; i < NAMESIZE; i++){
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
    for(int i = 0; i < PHONESIZE; i++){
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
    for(int i = 0; i < AREASIZE; i++){
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
    if(node == nullptr){
      return nullptr;
    }
    // Score us some hash yo
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

  void d_printByNameHash(int namehash){
    DicNode* currentnode = nameTable[namehash];
    while(currentnode != nullptr){
      std::cout << currentnode -> getName() << "  " << currentnode -> getAddress() << "\n";  
      currentnode = currentnode -> getNextByArea();
    }
  }

  void d_printByDay(int day){
    int hash1 = 2*(day - 1);
    int hash2 = 2*(day - 1) + 1;
    DicNode* currentnode = nameTable[hash1];
    while(currentnode != nullptr){
      std::cout << currentnode -> getName() << "   " << currentnode -> getAddress() << "   " << currentnode -> getCharges() << "\n";  
      currentnode = currentnode -> getNextByArea();
    }
    currentnode = nameTable[hash2];
    while(currentnode != nullptr){
      std::cout << currentnode -> getName() << "   " << currentnode -> getAddress() << "   " << currentnode -> getCharges() << "\n";  
      currentnode = currentnode -> getNextByArea();
    }
  }

  // Finds a node by phone, routes pointers around it from its parents to its
  // children, then returns the node in question.
  // REQUIRES CALLER DESTROY NODE THEY RECEIVE
  DicNode* d_removeByPhone(std::string phone){
    // Get node by phone
    DicNode* node = getFirstByPhone(phone);
    if(node == nullptr){
      return nullptr;
    }
    // Score us some hash yo
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

  DicNode* getNodeAmbiguous(std::string input){
    if(isDigits(input)){
      return getFirstByPhone(input);
    }
    else{
      return getFirstByName(input);
    }
  }

  void payBalanceAmbiguous(std::string charge, std::string input){
    DicNode* tempnode = nullptr;
    if(isDigits(input)){
      tempnode =  getFirstByPhone(input);
    }
    else{
      tempnode =  getFirstByName(input);
    }
    tempnode -> payCharges(charge); 
  }

private:
  std::string* namelist;
  std::string* addresslist;
  std::string* phonelist;
  std::string* chargeslist;

  int numentries;

  DicNode* nameTable[NAMESIZE] = {nullptr};
  DicNode* phoneTable[PHONESIZE] = {nullptr};
  DicNode* areaCodeTable[AREASIZE] = {nullptr};

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
    DicNode* current_node = nameTable[namehash];

    while(current_node != nullptr){
      if((current_node -> getName()).compare(name) == 0){
        return current_node;
      }
      current_node = current_node -> getNextByName();
    }
    return nullptr;
  }

  // Returns the first node with 'phone'
  DicNode* getFirstByPhone(std::string phone){
    int phonehash = phoneHash(phone);
    DicNode* current_node = phoneTable[phonehash];

    while(current_node != nullptr){
      if((current_node -> getPhoneNumber()).compare(phone) == 0){
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


int main(int argc, char* argv[]){


  std::string phonebookfile = "phonebook.txt";
  std::string testfile;
  if(argc > 1){
    testfile = argv[1];
  }

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

  // Some handy temp vars
  int tempint;
  std::string tempstring;
  DicNode* tempnode;
  std::string name;
  std::string address;
  std::string phone;
  std::string charges;
  std::string arguments[5];
  int option = 0;

  if(argc > 1){
    std::ifstream instructionfile(testfile);
    while(std::getline(instructionfile, line)){
      line = trim_copy(line);
      option = std::stoi(line);
      // Read in another line with arguments
      std::getline(instructionfile, line);
      line = trim_copy(line);
      if(option == 1){
        std::istringstream ss(line);
        for(int i = 0; i < 4; i++){
          std::getline(ss, tempstring, ',');
          arguments[i] = trim_copy(tempstring);
        }
        tempnode = new DicNode(arguments[0], arguments[1], arguments[2], arguments[3]);
        table.d_addByName(tempnode);
        std::cout << "Added " << arguments[0] << " to the hash table.\n";
      }
      else if(option == 2){
        std::istringstream ss(line);
        for(int i = 0; i < 4; i++){
          std::getline(ss, tempstring, ',');
          arguments[i] = trim_copy(tempstring);
        }
        tempnode = new DicNode(arguments[1], arguments[2], arguments[0], arguments[3]);
        table.d_addByPhone(tempnode);
        std::cout << "Added " << arguments[1] << " to the hash table.\n";
      }
      else if(option == 3){
        tempstring = trim_copy(line);
        tempnode = table.d_removeByName(tempstring);
        if(tempnode == nullptr){
          std::cout << "Could not find customer with name " << tempstring << ".\n";
        }
        else{
          std::cout << "Charges for " << tempnode -> getName() << " are " << tempnode -> getCharges() << ".\n";
        }
        delete tempnode;
      }
      else if(option == 4){
        tempstring = trim_copy(line);
        tempnode = table.d_removeByPhone(tempstring);
        if(tempnode == nullptr){
          std::cout << "Could not find customer with number " << tempstring << ".\n";
        }
        else{
          std::cout << "Charges for " << tempnode -> getName() << " are " << tempnode -> getCharges() << ".\n";
        }
        delete tempnode;
      }
      else if(option = 5){
        std::istringstream ss(line);
        for(int i = 0; i < 2; i++){
          std::getline(ss, tempstring, ',');
          arguments[i] = trim_copy(tempstring);
        }
        tempnode = table.getNodeAmbiguous(arguments[1]);
        if(tempnode == nullptr){
        }
        else{
          std::cout << "Balance to pay of " << tempnode -> getCharges() << " for " << tempnode -> getName() << ". Paying charge " << arguments[0] << ".\n";
          tempnode -> payCharges(arguments[0]);
          std::cout << "New balance of " << tempnode -> getCharges() << ".\n";
        }
      }
      else if(option == 6){
        std::istringstream ss(line);
        for(int i = 0; i < 2; i++){
          std::getline(ss, tempstring, ',');
          arguments[i] = trim_copy(tempstring);
        }
        tempnode = table.getNodeAmbiguous(arguments[1]);
        if(tempnode == nullptr){
        }
        else{
          std::cout << "Balance to pay of " << tempnode -> getCharges() << " for " << ". Applying charge of " << arguments[0] << "\n";
          arguments[0] = "-" + arguments[0];
          tempnode -> payCharges(arguments[0]);
          std::cout << "New balance of " << tempnode -> getCharges() << ".\n";
        }

      }
      else if(option == 7 || option == 8){
        tempstring = trim_copy(line);
        tempnode = table.getNodeAmbiguous(tempstring);
        std::cout << "Customer " << tempnode -> getName() << " has a balance of " << tempnode -> getCharges() << ".\n";
      }
      else if(option == 9){
        tempstring = trim_copy(line);
        std::cout << "Printing namehash " << tempstring << "...\n";
        tempint = std::stoi(tempstring);
        table.d_printByNameHash(tempint);
      }
      else if(option == 10){
        tempstring = trim_copy(line);
        table.d_printByDay(tempint);
      }
      else if(option == 11){
        tempstring = trim_copy(line);
        table.d_printByAreaCode(tempstring);
      }
      else if(option == 12){
        std::cout << "Exiting...\n";
        exit(0);
      }
      else{
        std::cout << "Invalid Option.\n";
      }

    }
  }



  bool cont = true;

  while(cont){
    std::cout << "1. Insert new by name.\n";
    std::cout << "2. Insert new by phone number.\n";
    std::cout << "3. Remove a customer by name.\n";
    std::cout << "4. Remove a customer by phone.\n";
    std::cout << "5. Add a payment by name or phone.\n";
    std::cout << "6. Add a charge by name or phone.\n";
    std::cout << "7. Print a bill by name.\n";
    std::cout << "8. Print a bill by phone.\n";
    std::cout << "9. Print all customers for a namehash.\n";
    std::cout << "10. Print monthly billing schedule.\n";
    std::cout << "11. Print all customers in area code.\n";
    std::cout << "12. EXIT.\n";
    std::cout << "13. Print nameTable.\n";
    std::cout << "14. Print phoneTable.\n";
    std::cout << "15. Print areacodeTable.\n";
    std::cout << "Select an option: ";
    std::cin >> option;
    // This cin BS is absolutely absurd. This has been a problem for
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
      delete tempnode;
      break;
    case 4:
      std::cout << "Phone number to remove: ";
      std::getline(std::cin, tempstring);
      std::cin.clear();
      tempstring = trim_copy(tempstring);
      tempnode = table.d_removeByPhone(tempstring);
      if(tempnode == nullptr){
        std::cout << "Could not find customer with number " << tempstring << ".\n";
      }
      else{
        std::cout << "Charges for " << tempnode -> getName() << " are " << tempnode -> getCharges() << ".\n";
      }
      delete tempnode;
      break;
    case 5:
    case 6:
      std::cout << "Name or phone number of customer: ";
      std::getline(std::cin, tempstring);
      std::cin.clear();
      tempnode = table.getNodeAmbiguous(tempstring);
      if(option == 5){
        std::cout << "Balance to pay of " << tempnode -> getCharges() << "? Enter amount to pay: ";
      }
      else{
        std::cout << "Balance to pay of " << tempnode -> getCharges() << "? Enter charges to apply: ";
      }
      std::getline(std::cin, tempstring);
      std::cin.clear();
      if(option == 6){
        tempstring = "-" + tempstring;
      }
      tempnode -> payCharges(tempstring);
      std::cout << "New balance of " << tempnode -> getCharges() << ".\n";
      break;
    case 7:
    case 8:
      if(option == 7){
        std::cout << "Name of customer: ";
      }
      else{
        std::cout << "Phone number of customer: ";
      }
      std::getline(std::cin, tempstring);
      std::cin.clear();
      tempnode = table.getNodeAmbiguous(tempstring);
      std::cout << "Customer " << tempnode -> getName() << " has a balance of " << tempnode -> getCharges() << ".\n";
      break;
    case 9:
      std::cout << "Namehash to print: ";
      std::cin >> tempint;
      std::cin.clear();
      std::cin.ignore();
      table.d_printByNameHash(tempint);
      break;
    case 10:
      std::cout << "Billing day to print: ";
      std::cin >> tempint;
      std::cin.clear();
      std::cin.ignore();
      table.d_printByDay(tempint);
      break;

    case 11:
      std::cout << "Area code to print: ";
      std::cin >> tempstring;
      std::cin.clear();
      std::cin.ignore();
      table.d_printByAreaCode(tempstring);
      break;
    case 13:
      table.printNameTableNodes();
      break;
    case 14:
      table.printPhoneTableNodes();
      break;
    case 15:
      table.printAreaCodeTableNodes();
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











