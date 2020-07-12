.PHONY : all clean

CXX = g++
CXXFLAGS = -std=c++11 -O3

SRC := $(wildcard *.cc)
TARGETS := $(patsubst %.cc,%, $(SRC))

all : $(TARGETS)

$(TARGETS) : $(SRC)

% : %.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsmobjall

clean :
	rm $(TARGETS)