
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Node{
public:  
  int key;
  char height;
  Node* left;
  Node* right;

  Node(int k){
    key = k;
    left = nullptr;
    right = nullptr;
    height = 1;
  }
};


char height(Node* n){
  if(n != nullptr){
    return n -> height;
  }
  else{
    return 0;
  }
}

int balancefactor(Node* n){
  return height(n -> right) - height(n -> left);
}

void fixheight(Node* n){
  char leftheight = height(n -> left);
  char rightheight = height(n -> right);
  if(leftheight > rightheight){
    n -> height = leftheight + 1;
  }
  else{
    n -> height = rightheight + 1;
  }
}






class LocationArray{
  std::string m_arr[300];
  int m_length;

public:

  LocationArray(){
    m_length = 0;
  }

  void insert(std::string* pack){
    m_arr[m_length] = pack[0];
    m_arr[m_length + 1] = pack[1];
    m_arr[m_length + 2] = pack[2];
    m_length += 3;
  }

  void print(){
    int i = 0;
    while(i < m_length){
      std::cout << m_arr[i] << " " << m_arr[i+1] << " " << m_arr[i+2] << "\n";
      i += 3;
    }
  }

  void remove(std::string name){
    int i = 0;
    while(m_arr[i].compare(name) != 0 && i < m_length){
      i++;
    }
    if(i == m_length){
      std::cout << "City not in list.\n";
    }
    else{
      m_arr[i] = m_arr[m_length - 3];
      m_arr[i+1] = m_arr[m_length - 2];
      m_arr[i+2] = m_arr[m_length - 1];
      m_length -= 3;
    }


  }

};


int main(){

  LocationArray la = LocationArray();

  std::ifstream file("data.txt");
  std::string line;

  while(std::getline(file, line)){
    std::string temp_arr[3];
    int i = 0;
    std::istringstream iss(line);
    while(iss.good()){
      iss >> temp_arr[i];
      i++;
    }
    la.insert(temp_arr);
  }

  la.print();
  la.remove("Otherplace");
  la.print();




  std::cout << "Exiting...\n";
  return 0;
}
