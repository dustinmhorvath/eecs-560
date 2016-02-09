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

  Fraction(){
  }

};

class FractionEngine {
public:

  Fraction convertToMixed(Fraction a){
    int whole = a.m_num/a.m_den;
    int new_numerator = a.m_num % a.m_den;
    Fraction x;
    x.m_num = new_numerator;
    x.m_whole = a.m_whole + whole;
    x.m_den = a.m_den;
    return x;
  }

  Fraction convertToImproper(Fraction a){
    if(a.m_whole != 0){
      Fraction x;
      x.m_num = a.m_num + (a.m_whole * a.m_den);
      x.m_whole = 0;
      x.m_den = a.m_den;
      return x;
    }
    else return a;
  }

  void print(Fraction a){
    if(a.m_whole == 0){
      std::cout << a.m_num << "," << a.m_den << "\n";
    }
    else{
      if(a.m_num != 0){
        std::cout << a.m_whole << " " << a.m_num << "," << a.m_den << "\n"; 
      }
      else{
        std::cout << a.m_whole << std::endl;
      }
    }
  }

  int lcm(Fraction a, Fraction b)
  {
    int m,n;
    m=a.m_den;
    n=b.m_den;
    while(m!=n){
      if(m < n){
        m = m + a.m_den;
      }
      else{
        n = n + b.m_den;
      }
    }
    return m;
  }

  Fraction expandDenominator(Fraction a, int den){
    Fraction x;
    x.m_num = a.m_num * den / a.m_den;
    x.m_den = den;
    return x;
  }

  Fraction add(Fraction a, Fraction b){
    a = convertToImproper(a);
    b = convertToImproper(b);
    int new_denom = lcm(a, b);
    a = expandDenominator(a, new_denom);
    b = expandDenominator(b, new_denom);
    Fraction x = Fraction(a.m_num + b.m_num, new_denom);
    return x;
  }

  Fraction xadd(Fraction a, Fraction b){
    Fraction x = convertToMixed(add(a, b));
    return x;
  }

  Fraction sub(Fraction a, Fraction b){
    a = convertToImproper(a);
    b = convertToImproper(b);
    int new_denom = lcm(a, b);
    a = expandDenominator(a, new_denom);
    b = expandDenominator(b, new_denom);
    Fraction x = Fraction(a.m_num - b.m_num, new_denom);
    return x;    
  }

  Fraction mul(Fraction a, Fraction b){
    a = convertToImproper(a);
    b = convertToImproper(b);
    Fraction x = Fraction(a.m_num * b.m_num, a.m_den * b.m_den);
    return x;
  }

  Fraction div(Fraction a, Fraction b){
    a = convertToImproper(a);
    b = convertToImproper(b);
    Fraction x = Fraction(a.m_num * b.m_den, a.m_den * b.m_num);
    return x;
  }

  Fraction xdiv(Fraction a, Fraction b){
    a = convertToImproper(a);
    b = convertToImproper(b);
    Fraction x = convertToMixed(Fraction(a.m_num * b.m_den, a.m_den * b.m_num));
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

  Fraction x = Fraction(12,2);
  Fraction y = Fraction(2,1);

  FractionEngine engine = FractionEngine();

// *works* //
//  x = x.xadd(y);
//  x.print();
//  engine.print(engine.mul(x,y));
//  engine.print(engine.div(x,y));
//  engine.print(engine.xdiv(x,y));


  std::cout << "Exiting...\n";
  return 0;
}
