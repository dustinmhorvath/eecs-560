/*
 * Dustin Horvath
 * 2729265
 * EECS 560
 * Fraction operation program
 *
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Queue.h"

class Fraction {
public:
  int m_num;
  int m_den;
  int m_whole;

  Fraction(int a, int b){
    if(b < 0){
      b = b * -1;
      a = a * -1;
    }

    if(b == 1){
      m_whole = a;
      m_num = 0;
      m_den = 1;
    }

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

  Fraction(){
    //Use with caution
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
      std::cout << a.m_num << "/" << a.m_den;
    }
    else{
      std::cout << a.m_whole;
      if(a.m_num != 0){
        std::cout << " " << a.m_num << "/" << a.m_den; 
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
    Fraction x = mix(red(add(a, b)));
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
    if(b.m_den == 0){
      std::cout << "ERR: DIVBY0\n";
      return a;
    }
    else{

      Fraction x = red(Fraction(a.m_num * b.m_den, a.m_den * b.m_num));
      return x;
    }
  }

  Fraction xdiv(Fraction a, Fraction b){
    a = unm(a);
    b = unm(b);
    Fraction x = mix(div(a, b));
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

  bool checkLess(Fraction a, Fraction b){
    a = unm(a);
    b = unm(b);
    if((double)a.m_num/a.m_den <= (double)b.m_num/b.m_den){
      return true;
    }
    else return false;
  }

  bool equals(Fraction a, Fraction b){
    a = unm(a);
    b = unm(b);
    int new_denom = lcm(a, b);
    a = expandDenominator(a, new_denom);
    b = expandDenominator(b, new_denom);
    return (a.m_num == b.m_num);
  }

};

inline bool isInteger(const std::string & s){
  if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
  char * p ;
  strtol(s.c_str(), &p, 10) ;
  return (*p == 0) ;
}

Queue<Fraction> parseFractionPairs(std::string* input){
  Queue<Fraction> list;
  int i = 1;
  if(input[0].compare("SUM") == 0 || 
      input[0].compare("SORT") == 0 ||
      input[0].compare("MEDIAN") == 0 ||
      input[0].compare("MEAN") == 0 ||
      input[0].compare("MODE") == 0
    ){
    i++;
  }
  while(isInteger(input[i]) && isInteger(input[i + 1])){
    list.enqueue(Fraction(atoi(input[i].c_str()), atoi(input[i + 1].c_str())));
    i += 2;
  }
  return list;
}

Queue<Fraction> parseMixedFractions(std::string* input){
  Queue<Fraction> list;
  int i = 1;
  while(isInteger(input[i]) && isInteger(input[i + 1]) && isInteger(input[i + 2])){
    list.enqueue(Fraction(atoi(input[i].c_str()), atoi(input[i + 1].c_str()), atoi(input[i + 2].c_str())));
    i = i + 3;
  }
  return list;
}

void runCommand(std::string arr[]){
  FractionEngine engine = FractionEngine();
  if(arr[0].compare("SUM") == 0){
    int value = atoi(arr[1].c_str());
    Fraction sum = Fraction(value, 1);
    Queue<Fraction> pair = parseFractionPairs(arr);
    std::cout << value;
    while(pair.size() > 0){
      Fraction temp = pair.peekFront();
      std::cout << " + ";
      engine.print(temp);
      pair.dequeue();
      sum = engine.add(sum, temp);
    }
    std::cout << " = ";
    engine.print(sum);
    std::cout << std::endl;
  }

  if(arr[0].compare("MEAN") == 0){
    // Parse this crap into fractions, then dequeue it into an array because a
    // queue is a pain in my KJHBFCKJHB
    Queue<Fraction> pair = parseFractionPairs(arr);
    int pairlength = pair.size();
    Fraction list[1 + pairlength];
    list[0]= Fraction(atoi(arr[1].c_str()), 0, 1);
    for(int i = 1; i <= pairlength; i++){
      list[i] = pair.peekFront();
      pair.dequeue();
    }

    // Print the original order
    for(int i = 0; i <= pairlength; i++){
      engine.print(list[i]);
      std::cout << " ";
    }
    std::cout << "has mean ";

    Fraction sum = Fraction(0, 0, 1);
    for (int i = 0 ; i <= pairlength; i++){
      sum = engine.add(sum, list[i]);
    }
    Fraction avg = engine.div(sum, Fraction(pairlength + 1, 0, 1));
    engine.print(avg);
    std::cout << std::endl;
  }

  
  Queue<Fraction> modes;

  if(arr[0].compare("MODE") == 0){
    // Parse this crap into fractions, then dequeue it into an array because a
    // queue is a pain in my KJHBFCKJHB
    Queue<Fraction> pair = parseFractionPairs(arr);
    int pairlength = pair.size();
    Fraction list[1 + pairlength];
    list[0]= Fraction(atoi(arr[1].c_str()), 0, 1);
    for(int i = 1; i <= pairlength; i++){
      list[i] = pair.peekFront();
      pair.dequeue();
    }

    for(int i = 0; i <= pairlength; i++){
      engine.print(list[i]);
      std::cout << " ";
    }
    std::cout << "has modes ";

    // Use the bubblesort algorithm again
    for (int i = 0 ; i < pairlength; i++){
      Fraction temp;
      temp = list[i];
      for (int j = 0 ; j < pairlength; j++){
        if(!engine.checkLess(list[j],list[j+1])){
          Fraction swap = list[j+1];
          list[j+1] = list[j];
          list[j] = swap;
        }
      }
    }

    int counter = 1;
    int max = 0;
    modes.enqueue(list[0]);
    for (int pass = 0; pass < pairlength - 1; pass++){
      if (engine.equals(list[pass],list[pass+1])){
        counter++;
        if ( counter > max ){
          max = counter;
          while(modes.m_length > 0){
            modes.dequeue();
          }
          modes.enqueue(list[pass]);
        }
        else if(counter == max){
          modes.enqueue(list[pass]);
        }
      } 
      else{
        counter = 1; // reset counter.
      }
    }
    //    engine.print(mode);

  while(modes.m_length > 0){
    engine.print(modes.peekFront());
    std::cout << " ";
    modes.dequeue();
  }


    std::cout << "\n";
  }



  if(arr[0].compare("MEDIAN") == 0){
    // Parse this crap into fractions, then dequeue it into an array because a
    // queue is a pain in my KJHBFCKJHB
    Queue<Fraction> pair = parseFractionPairs(arr);
    int pairlength = pair.size();
    Fraction list[1 + pairlength];
    list[0]= Fraction(atoi(arr[1].c_str()), 0, 1);
    for(int i = 1; i <= pairlength; i++){
      list[i] = pair.peekFront();
      pair.dequeue();
    }

    // Print the original order
    for(int i = 0; i <= pairlength; i++){
      engine.print(list[i]);
      std::cout << " ";
    }
    std::cout << "has median ";

    // Use the bubblesort algorithm again
    for (int i = 0 ; i < pairlength; i++){
      Fraction temp;
      temp = list[i];
      for (int j = 0 ; j < pairlength; j++){
        if(!engine.checkLess(list[j],list[j+1])){
          Fraction swap = list[j+1];
          list[j+1] = list[j];
          list[j] = swap;
        }
      }
    }

    // Average values if even number of arguments, else get middle
    if((pairlength+1)%2 == 0){
      engine.print(engine.div(engine.add(list[(pairlength+1)/2], list[(pairlength+1)/2 + 1]), Fraction(2, 0, 1)));
    }
    else{
      engine.print(list[(pairlength+1)/2]);
    }
    std::cout << "\n";
  }


  if(arr[0].compare("SORT") == 0){
    // Parse this crap into fractions, then dequeue it into an array because a
    // queue is a pain in my KJHBFCKJHB
    Queue<Fraction> pair = parseFractionPairs(arr);
    int pairlength = pair.size();
    Fraction list[1 + pairlength];
    list[0]= Fraction(atoi(arr[1].c_str()), 0, 1);
    for(int i = 1; i <= pairlength; i++){
      list[i] = pair.peekFront();
      pair.dequeue();
    }

    // Print the original order
    for(int i = 0; i <= pairlength; i++){
      engine.print(list[i]);
      std::cout << " ";
    }
    std::cout << "sorts to ";

    // Bubblesort this broseph
    for (int i = 0 ; i < pairlength; i++){
      Fraction temp;
      temp = list[i];
      for (int j = 0 ; j < pairlength; j++){
        if(!engine.checkLess(list[j],list[j+1])){
          Fraction swap = list[j+1];
          list[j+1] = list[j];
          list[j] = swap;
        }
      }
    }

    // Print it sorted
    for(int i = 0; i <= pairlength; i++){
      engine.print(list[i]);
      std::cout << " ";
    }
    std::cout << std::endl;
  }

  if(arr[0].compare("ADD") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    pair.dequeue();
    Fraction b = pair.peekFront();
    engine.print(a);
    std::cout << " + ";
    engine.print(b);
    std::cout << " = ";
    engine.print(engine.add(a,b));
    std::cout << std::endl;
  }
  if(arr[0].compare("SUB") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    pair.dequeue();
    Fraction b = pair.peekFront();
    engine.print(a);
    std::cout << " - ";
    engine.print(b);
    std::cout << " = ";
    engine.print(engine.sub(a,b));
    std::cout << std::endl;
  }
  if(arr[0].compare("XADD") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    pair.dequeue();
    Fraction b = pair.peekFront();
    engine.print(a);
    std::cout << " + ";
    engine.print(b);
    std::cout << " = ";
    engine.print(engine.xadd(a,b));
    std::cout << std::endl;
  }
  if(arr[0].compare("MUL") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    pair.dequeue();
    Fraction b = pair.peekFront();
    engine.print(a);
    std::cout << " * ";
    engine.print(b);
    std::cout << " = ";
    engine.print(engine.mul(a,b));
    std::cout << std::endl;

  }
  if(arr[0].compare("DIV") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    pair.dequeue();
    Fraction b = pair.peekFront();
    engine.print(a);
    std::cout << " / ";
    engine.print(b);
    std::cout << " = ";
    engine.print(engine.div(a,b));
    std::cout << std::endl;
  }
  if(arr[0].compare("XDIV") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    pair.dequeue();
    Fraction b = pair.peekFront();
    engine.print(a);
    std::cout << " / ";
    engine.print(b);
    std::cout << " = ";
    engine.print(engine.xdiv(a,b));
    std::cout << std::endl;

  }
  if(arr[0].compare("REC") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    engine.print(a);
    std::cout << " inverts to ";
    engine.print(engine.rec(a));
    std::cout << std::endl;

  }
  if(arr[0].compare("RED") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    engine.print(a);
    std::cout << " reduces to ";
    engine.print(engine.red(a));
    std::cout << std::endl;
  }
  if(arr[0].compare("MIX") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    engine.print(a);
    std::cout << " as mixed is ";
    engine.print(engine.mix(a));
    std::cout << std::endl;
  }
  if(arr[0].compare("UNM") == 0){
    Queue<Fraction> pair = parseMixedFractions(arr);
    Fraction a = pair.peekFront();
    engine.print(a);
    std::cout << " as improper is ";
    engine.print(engine.unm(a));
    std::cout << std::endl;
  } 
  if(arr[0].compare("AMIX") == 0){
    bool fail = false;
    for(int i = 1; i < 7; i++){
      if(!isInteger(arr[i])){
        fail = true;
      }
    }
    if(!fail){
      std::string list1[2] = {arr[2], arr[3]};
      std::string* firstlist = list1;
      std::string list2[2] = {arr[5], arr[6]};
      std::string* secondlist = list2;

      int whole1 = atoi(arr[1].c_str());
      int whole2 = atoi(arr[4].c_str());

      Fraction frac1 = Fraction(atoi(arr[2].c_str()), atoi(arr[3].c_str()));
      Fraction frac2 = Fraction(atoi(arr[5].c_str()), atoi(arr[6].c_str()));

      std::cout << whole1 << " ";
      engine.print(frac1);
      std::cout << " + " << whole2 << " ";
      engine.print(frac2);
      std::cout << " = ";

      engine.print(engine.amix(whole1, frac1, whole2, frac2));
      std::cout << std::endl;
    }
  }
  if(arr[0].compare("LESS") == 0){
    Queue<Fraction> pair = parseFractionPairs(arr);
    Fraction a = pair.peekFront();
    pair.dequeue();
    Fraction b = pair.peekFront();
    std::cout << "Of fractions ";
    engine.print(a);
    std::cout << " and ";
    engine.print(b);
    std::cout << ", ";
    engine.print(engine.less(a,b));
    std::cout << " is less.";
    std::cout << std::endl;

  }
}

int main(){

  std::ifstream file("input.txt");
  std::string line;

  while(std::getline(file, line)){
    std::string arr[50];
    int i = 0;
    std::istringstream iss(line);
    while(iss.good()){
      iss >> arr[i];
      i++;
    }
    runCommand(arr);
  }

  std::cout << "Exiting...\n";
  return 0;
}











