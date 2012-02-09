#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>


using namespace std;

class Lisp{
private:
  ifstream fin;
  string buf;
  int index;
  bool isInt(char c);
  string lexInt();
  int stoi(string s);
public:
  Lisp(char *file);
  virtual ~Lisp();
  void lmain();
  int eval();
  int plus();
  int mul();
  int sub();
  int div();
};

Lisp::~Lisp(){}

Lisp::Lisp(char *file){
  fin.open(file);
  index = 0;
}

bool Lisp::isInt(char c){
  if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' ||
     c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){
    return true;
  }else{
    return false;
  }
}

int Lisp::stoi(string s){
  stringstream ss;
  int ans;
  ss << s;
  ss >> ans;
  return ans;
}


string Lisp::lexInt(){
  int endof = 0;
  while(isInt(buf[index+endof])){
    ++endof;
  }
  string str = buf.substr(index,endof);
  index += endof;
  return str;
}


int Lisp::plus(){
  int a = eval();
  int b = eval();
  std::cout << "(+ " << a << " "<<b<<") => " << a+b << std::endl;

  return a+b;
}

int Lisp::mul(){
  int a = eval();
  int b = eval();
  std::cout << "(* " << a << " "<<b<<") => " << a*b << std::endl;

  return a*b;
}

int Lisp::div(){
  int a = eval();
  int b = eval();
  std::cout << "(/ " << a << " "<<b<<") => " << a/b << std::endl;

  return a/b;
}

int Lisp::sub(){
  int a = eval();
  int b = eval();
  std::cout << "(- " << a << " "<<b<<") => " << a-b << std::endl;

  return a-b;
}


int Lisp::eval(){
  if(buf[index] == ' ' || buf[index] == '(' || buf[index] == ')'){
    ++index;
    return eval();
  }else if(buf[index] == '+'){
    ++index;
    return plus();
  }else if(buf[index] == '-'){
    ++index;
    return sub();
  }else if(buf[index] == '*'){
    ++index;
    return mul();
  }else if(buf[index] == '/'){
    ++index;
    return div();
  }else if(isInt(buf[index])){
    return stoi(lexInt());
  }else{
    cout << "Error" << endl;
    return 0;
  }
}


void Lisp::lmain(){
  while(fin && getline(fin,buf)){
    index = 0;
    if(buf[index] == '('){
      ++index;
      cout << eval() << endl;
    }else{
      cout << "Error" << endl;
    }
  }
}

int main(int argc, char **argv){
  if(argc == 2){
    Lisp p(argv[1]);
    p.lmain();
  }else{
    cout << "Cannot open file" << endl;
  }
  return 0;
}


