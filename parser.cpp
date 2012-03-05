#include "lisp.hpp"

namespace lisp{
  using namespace std;

  Lisp::~Lisp(){}

  Lisp::Lisp(char *file){
    fin.open(file);
    index = 0;
    depth = 0;
  }


  bool Lisp::isInt(string s){
    boost::regex r("[0-9]+");
    return boost::regex_match(s,r);
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
    while(isInt(buf.substr(index+endof,1))){
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

    if(isInt(buf.substr(index,1))){
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
    while(index < buf.size())
      cout << eval() << endl;
  }
}
