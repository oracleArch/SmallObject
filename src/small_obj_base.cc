#include "small_obj_base.hh"

template<typename Alloc>
void*
SmallObjBase<Alloc>::operator new (std::size_t bytes)
{
    return Alloc::instance->Allocate(bytes);
}

template<typename Alloc>
void
SmallObjBase<Alloc>::operator delete (void *p, std::size_t bytes)
{
    return Alloc::instance->Deallocate(p, bytes);
}

template class SmallObjBase<SmallObjAllocator>;