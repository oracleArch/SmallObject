#include "small_obj_base.hh"
#include <memory>
#include <iostream>

constexpr std::size_t numChunkBytes = 64;
constexpr std::size_t SmallObjSizeLimit = 16;

class Test : public SmallObjBase<>
{
private:
    char c;
    int num;

public:
    Test()
        : c('r'),
          num(5)
    {
    }

    void print ()
    {
        std::cout << c << ", " << num << std::endl;
    }
};

int main ()
{
    SmallObjAllocator *small_allocator = SmallObjAllocator::getSmallObjAllocator (numChunkBytes, SmallObjSizeLimit);

    Test* ptr = new Test();
    ptr->print();

    delete ptr;
    return 0;
}