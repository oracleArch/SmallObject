#include <assert.h>
#include "small_obj_base.hh"

template<typename Alloc>
static void*
SmallObjBase<Alloc>::operator new (std::size_t bytes)
{
    assert(Alloc::instance);
    return Alloc::instance->Allocate(bytes);
}

template<typename Alloc>
static void
SmallObjBase<Alloc>::operator delete (void *p, std::size_t bytes)
{
    assert(Alloc::instance);
    return Alloc::instance->Deallocate(p, bytes);
}

template class SmallObjBase<SmallObjAllocator>;