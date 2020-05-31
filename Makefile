.PHONY : all clean install examples

CXX = g++
CXXFLAGS = -std=c++11 -O3 -fpic
TARGET = libsmobjall.so
INST_PATH = /usr/local/
INC = -Iinclude/

SRC := $(wildcard src/*.cc)
OBJ := $(patsubst %.cc,%.o, $(SRC))
INST_INC := $(patsubst %.so,%, $(TARGET))

all: $(TARGET)

src/small_obj_base.o : include/small_obj_base.hh include/small_obj_allocator.hh include/fixed_allocator.hh include/chunk.hh
src/small_obj_allocator.o : include/small_obj_allocator.hh include/fixed_allocator.hh include/chunk.hh
src/fixed_allocator.o : include/fixed_allocator.hh include/chunk.hh
src/chunk.o : include/chunk.hh

$(TARGET) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) -shared -o $@ $^

install:
	sudo mkdir -p $(INST_PATH)/include/$(INST_INC)/
	sudo cp -r include/*.hh $(INST_PATH)/include/$(INST_INC)/
	sudo cp $(TARGET) $(INST_PATH)/lib/$(TARGET)

examples :
	$(MAKE) -C examples/

%.o : %.cc
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

clean:
	rm $(OBJ)
	rm $(TARGET)
	$(MAKE) clean -C examples/