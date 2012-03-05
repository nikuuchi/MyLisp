#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <boost/regex.hpp>

using namespace std;
namespace lisp{
  class Lisp{
    ifstream fin;
    string buf;
    int index;
    int depth;
    bool isInt(string s);
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

  union _Value{
    double type_d;
    int type_i;
    char type_c;
    string *type_s;
    void *point;
  };
  typedef union _Value VALUE;

  enum _TYPE{NIL,INT,DOUBLE,STRING,KLASS,NODE};
  typedef enum _TYPE TYPE;

  class Node
  {
    VALUE value;
    TYPE nodetype;
    Node *next;
  public:
    Node();
    Node(Node *next, TYPE nodetype, VALUE value);
    virtual ~Node();
  };
 
}
