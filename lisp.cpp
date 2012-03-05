#include "lisp.hpp"


int main(int argc, char **argv){
  if(argc == 2){
    lisp::Lisp p(argv[1]);
    p.lmain();
  }else{
    cout << "Cannot open file" << endl;
  }
  return 0;
}


