
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Fraction {
private:
  int m_num;
  int m_den;

public:
  Fraction(int a, int b){
    m_num = a;
    m_den = b;
  }

  int gcd(Fraction a, Fraction b) {
    int  gcd;
    for(int i = 1;i <= a.m_den && i <= b.m_den; i++){
      if(a.m_den % i == 0 && b.m_den % i == 0 ){
        gcd = i;
      }
    }
    return gcd;
  }

  Fraction expandDenominator(Fraction a, int den){
    return Fraction(a.m_num * den / a.m_den, den);
  }

  Fraction add(Fraction a, Fraction b){
    int new_denom = gcd(a, b);
    Fraction x = expandDenominator(a, new_denom);
    Fraction y = expandDenominator(b, new_denom);
    return Fraction(x.m_num + y.m_num, new_denom);
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
  Fraction y = Fraction(3,4);

  Fraction::add(x,y);

  return 0;
}
