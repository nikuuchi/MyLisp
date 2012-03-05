
CXX = g++
DEFS = -std=gnu++0x 
LIBS = -lreadline -lboost_regex

SRCS = \
	lisp.cpp \
	parser.cpp \
	node.cpp 
OBJS = $(SRCS:.cpp=.o)
PROG = lisp

all: $(PROG)

$(PROG): $(OBJS)
	$(CXX) -g -o $@ $(OBJS) $(LIBS)

.cc.o:
	$(CXX) $(DEFS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(PROG)

