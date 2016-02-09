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
    a = convertToImproper(a);
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
    Fraction x = red(Fraction(a.m_num + b.m_num, new_denom));
    return x;
  }

  Fraction xadd(Fraction a, Fraction b){
    Fraction x = red(convertToMixed(add(a, b)));
    return x;
  }

  Fraction sub(Fraction a, Fraction b){
    a = convertToImproper(a);
    b = convertToImproper(b);
    int new_denom = lcm(a, b);
    a = expandDenominator(a, new_denom);
    b = expandDenominator(b, new_denom);
    Fraction x = red(Fraction(a.m_num - b.m_num, new_denom));
    return x;    
  }

  Fraction mul(Fraction a, Fraction b){
    a = convertToImproper(a);
    b = convertToImproper(b);
    Fraction x = red(Fraction(a.m_num * b.m_num, a.m_den * b.m_den));
    return x;
  }

  Fraction div(Fraction a, Fraction b){
    a = convertToImproper(a);
    b = convertToImproper(b);
    Fraction x = red(Fraction(a.m_num * b.m_den, a.m_den * b.m_num));
    return x;
  }

  Fraction xdiv(Fraction a, Fraction b){
    a = convertToImproper(a);
    b = convertToImproper(b);
    Fraction x = convertToMixed(red(Fraction(a.m_num * b.m_den, a.m_den * b.m_num)));
    return x;
  }

  Fraction rec(Fraction a){
    a = convertToImproper(a);
    int temp = a.m_num;
    a.m_num = a.m_den;
    a.m_den = temp;
    return a;
  }

  Fraction red(Fraction a){
    a = convertToImproper(a);
    for (int i = a.m_den * a.m_num; i > 1; i--) {  
      if ((a.m_den % i == 0) && (a.m_num % i == 0)) {  
        a.m_den = a.m_den / i;
        a.m_num = a.m_num / i;
      }  

    }
    if(a.m_den == 1){
      a = convertToMixed(a);
    }
    return a;
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

  Fraction x = Fraction(3,2);
  Fraction y = Fraction(7,2);

  FractionEngine engine = FractionEngine();

// *works* //
//  engine.print(engine.add(x,y));
//  engine.print(engine.div(x,y));
//  engine.print(engine.xdiv(x,y));


  engine.print(engine.xadd(x,y));
  std::cout << "Exiting...\n";
  return 0;
}
