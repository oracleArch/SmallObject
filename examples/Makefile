.PHONY : all clean

CXX = g++
CXXFLAGS = -std=c++11 -O3
INC = -I/usr/local/include/libsmobjall/

SRC := $(wildcard *.cc)
TARGETS := $(patsubst %.cc,%, $(SRC))

all : $(TARGETS)

$(TARGETS) : $(SRC)

% : %.cc
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $^ -lsmobjall

clean :
	rm $(TARGETS)