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
  int depth;
  bool isInt(char c);
  string lexInt();
  int stoi(string s);
  int eval();
  int plus();
  int mul();
  int sub();
  int div();
public:
  Lisp(char *file);
  virtual ~Lisp();
  void lmain();
};

Lisp::~Lisp(){}

Lisp::Lisp(char *file){
  fin.open(file);
  index = 0;
  depth = 0;
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
  int a = 0;
  int d = depth - 1;
  while(d != depth){
    int tmp = eval();
    if(d == depth)
      break;
    a += tmp;
  }
  std::cout << "(+) => " << a << std::endl;

  return a;
}

int Lisp::mul(){
  int a = 1;
  int d = depth - 1;
  while(d != depth){
    int tmp = eval();
    if(d == depth)
      break;
    a *= tmp;
  }
  std::cout << "(*) => " << a << std::endl;

  return a;
}

int Lisp::div(){
  int a = eval();
  int d = depth - 1;
  while(d != depth){
    int tmp = eval();
    if(d == depth)
      break;
    a /= tmp;
  }
  std::cout << "(/) => " << a << std::endl;

  return a;
}

int Lisp::sub(){
  int a = eval();
  int d = depth - 1;
  while(d != depth){
    int tmp = eval();
    if(d == depth)
      break;
    a -= tmp;
  }
  std::cout << "(-) => " << a << std::endl;

  return a;
}

int Lisp::eval(){
  switch(buf[index]){
  case '(':
    ++depth;
  case ' ':
  case '\t':
    ++index;
    return eval();
  case ')':
    --depth;
    ++index;
    return 0; //eval()を続けないという意味であり、0に意味があるわけではない。
  case '+':
    ++index;
    return plus();
  case '-':
    ++index;
    return sub();
  case '*':
    ++index;
    return mul();
  case '/':
    ++index;
    return div();
  default:
    break;
  }

  if(isInt(buf[index])){
    return stoi(lexInt());
  }else{
    cout << "Error" << endl;
    return 0;
  }
}


void Lisp::lmain(){
  string line = "";
  while(fin && getline(fin,line)){
    buf += line;
  }
  index = 0;
  cout << eval() << endl;
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


