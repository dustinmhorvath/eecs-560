#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Fraction {
public:
  int m_num;
  int m_den;
  int m_whole;

  Fraction(int a, int b){
    m_whole = 0;
    m_num = a;
    m_den = b;
  }

  void convertToMixed(){
    int whole = m_num/m_den;
    int new_numerator = m_num % m_den;
    m_num = new_numerator;
    m_whole = m_whole + whole;
  }

  void convertToImproper(){
    if(m_whole != 0){
      m_num = m_num + (m_whole * m_den);
      m_whole = 0;
    }
  }

  void print(){
    if(m_whole == 0){
      std::cout << m_num << "," << m_den << "\n";
    }
    else{
      std::cout << m_whole << " " << m_num << "," << m_den << "\n"; 
    }
  }

  int lcm(Fraction a)
  {
    int m,n;
    m=a.m_den;
    n=this -> m_den;
    while(m!=n){
      if(m < n){
        m = m + a.m_den;
      }
      else{
        n = n + this -> m_den;
      }
    }
    return m;
  }

  Fraction expandDenominator(int den){
    m_num = m_num * den / m_den;
    m_den = den;
  }

  Fraction add(Fraction a){
    a.convertToImproper();
    this -> convertToImproper();
    int new_denom = this -> lcm(a);
    a.expandDenominator(new_denom);
    this -> expandDenominator(new_denom);
    Fraction x = Fraction(a.m_num + this -> m_num, new_denom);
    return x;
  }

  Fraction xadd(Fraction a){
    Fraction x = this -> add(a);
    x.convertToMixed();
    return x;;
  }

  Fraction sub(Fraction a){
    a.convertToImproper();
    this -> convertToImproper();
    int new_denom = this -> lcm(a);
    a.expandDenominator(new_denom);
    this -> expandDenominator(new_denom);
    Fraction x = Fraction(this -> m_num - a.m_num, new_denom);
    return x;    
  }

};

int main(){
  /*
     std::ifstream file("data2.txt");
     std::string line;

     while(std::getline(file, line)){
     std::stringstream  lineStream(line);
     int value;
     int index = 0;
     while(lineStream >> value){
     arr[index] = value;
     index++;
     }
     }
     */

  std::cout << "Exiting...\n";
  Fraction x = Fraction(1,2);
  Fraction y = Fraction(3,8);


// *works* //
  x = x.xadd(y);
  x.print();


  return 0;
}
