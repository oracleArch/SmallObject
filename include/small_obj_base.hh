#ifndef __SMALL_OBJ_BASE_HH__
#define __SMALL_OBJ_BASE_HH__

#include "small_obj_allocator.hh"

template <typename Alloc = SmallObjAllocator>
class SmallObjBase
{
public:
    static void* operator new (std::size_t bytes);
    static void operator delete (void *p, std::size_t bytes);
    virtual ~SmallObjBase() {}
};

#endif