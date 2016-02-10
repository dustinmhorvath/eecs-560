#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

class Fraction {
public:
  int m_num;
  int m_den;
  int m_whole;

  Fraction(int a, int b){
    if(b != 0){
      m_whole = 0;
    m_num = a;
    m_den = b;
    }
    else{
      // throw exception here
    }
  }

  Fraction(int a, int b, int c){
    m_whole = a;
    m_num = b;
    m_den = c;
  }

};

class FractionEngine {
public:

  Fraction mix(Fraction a){
    a = unm(a);
    int whole = a.m_num/a.m_den;
    int new_numerator = a.m_num % a.m_den;
    Fraction x = Fraction(a.m_whole + whole, new_numerator, a.m_den);
    return x;
  }

  Fraction unm(Fraction a){
    if(a.m_whole != 0){
      Fraction x = Fraction(0,  a.m_num + (a.m_whole * a.m_den), a.m_den);
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

  int lcm(Fraction a, Fraction b){
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
    Fraction x = Fraction(a.m_num * den / a.m_den, den);
    return x;
  }

  Fraction add(Fraction a, Fraction b){
    a = unm(a);
    b = unm(b);
    int new_denom = lcm(a, b);
    a = expandDenominator(a, new_denom);
    b = expandDenominator(b, new_denom);
    Fraction x = red(Fraction(a.m_num + b.m_num, new_denom));
    return x;
  }

  Fraction xadd(Fraction a, Fraction b){
    Fraction x = red(mix(add(a, b)));
    return x;
  }

  Fraction sub(Fraction a, Fraction b){
    a = unm(a);
    b = unm(b);
    int new_denom = lcm(a, b);
    a = expandDenominator(a, new_denom);
    b = expandDenominator(b, new_denom);
    Fraction x = red(Fraction(a.m_num - b.m_num, new_denom));
    return x;    
  }

  Fraction mul(Fraction a, Fraction b){
    a = unm(a);
    b = unm(b);
    Fraction x = red(Fraction(a.m_num * b.m_num, a.m_den * b.m_den));
    return x;
  }

  Fraction div(Fraction a, Fraction b){
    a = unm(a);
    b = unm(b);
    Fraction x = red(Fraction(a.m_num * b.m_den, a.m_den * b.m_num));
    return x;
  }

  Fraction xdiv(Fraction a, Fraction b){
    a = unm(a);
    b = unm(b);
    Fraction x = mix(red(Fraction(a.m_num * b.m_den, a.m_den * b.m_num)));
    return x;
  }

  Fraction rec(Fraction a){
    a = unm(a);
    int temp = a.m_num;
    a.m_num = a.m_den;
    a.m_den = temp;
    return a;
  }

  Fraction red(Fraction a){
    a = unm(a);
    for (int i = a.m_den * a.m_num; i > 1; i--) {  
      if ((a.m_den % i == 0) && (a.m_num % i == 0)) {  
        a.m_den = a.m_den / i;
        a.m_num = a.m_num / i;
      }  

    }
    if(a.m_den == 1){
      a = mix(a);
    }
    return a;
  }

  Fraction amix(int x, Fraction a, int y, Fraction b){
    a = unm(a);
    b = unm(b);
    a.m_num = a.m_num + x * a.m_den;
    b.m_num = b.m_num + y * b.m_den;
    return mix(add(a,b));
  }

  Fraction less(Fraction a, Fraction b){
    a = unm(a);
    b = unm(b);
    if((double)a.m_num/a.m_den < (double)b.m_num/b.m_den){
      return a;
    }
    else return b;
  }

};

inline bool isInteger(const std::string & s){
  if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
  char * p ;
  strtol(s.c_str(), &p, 10) ;
  return (*p == 0) ;
}

std::queue<Fraction> parseTwoFractions(std::string* input){
  std::queue<Fraction> list;
  if(isInteger(input[1]) && isInteger(input[2]) && isInteger(input[3]) && isInteger(input[4])){
    list.push(Fraction(atoi(input[1].c_str()), atoi(input[2].c_str())));
    list.push(Fraction(atoi(input[3].c_str()), atoi(input[4].c_str())));
  }
  return list;
}

int main(){

  std::ifstream file("input.txt");
  std::string line;
  FractionEngine engine = FractionEngine();

  while(std::getline(file, line)){
    std::string arr[5];
    int i = 0;
    std::istringstream iss(line);
    while(iss.good()){
      iss >> arr[i];
      i++;
    }
    if(arr[0].compare("add") == 0){
      std::queue<Fraction> pair = parseTwoFractions(arr);
      Fraction a = pair.front();
      pair.pop();
      Fraction b = pair.front();
      engine.print(engine.add(a,b));
    }

  }

  std::cout << "Exiting...\n";
  return 0;
}
