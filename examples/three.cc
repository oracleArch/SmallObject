#include "small_obj_base.hh"
#include <memory>
#include <iostream>

constexpr std::size_t numChunkBytes = 64;
constexpr std::size_t SmallObjSizeLimit = 16;

class Test : public SmallObjBase<>
{
private:
    char c_;
    int num_;

public:
    Test(char c, int num)
        : c_(c),
          num_(num)
    {
    }

    void print ()
    {
        std::cout << c_ << ", " << num_ << std::endl;
    }
};

int main ()
{
    SmallObjAllocator *small_allocator = SmallObjAllocator::getSmallObjAllocator (numChunkBytes, SmallObjSizeLimit);

    Test* ptr = new Test('t', -18);
    Test* ptr2 = new Test('c', 5);
    Test* ptr3 = new Test('r', 8);

    ptr->print();
    ptr2->print();
    ptr3->print();

    delete ptr;
    delete ptr2;
    delete ptr3;
    delete small_allocator;
    return 0;
}