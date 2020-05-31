#ifndef __SMALL_OBJ_ALLOCATOR_HH__
#define __SMALL_OBJ_ALLOCATOR_HH__

#include "fixed_allocator.hh"

// Forward declaring to allow friend class
template <typename Alloc>
class SmallObjBase;

class SmallObjAllocator
{
private:
    static SmallObjAllocator* instance;

    // Private constructor for being singleton
    SmallObjAllocator (std::size_t numChunkBytes, std::size_t SmallObjSizeLimit);

    std::size_t numChunkBytes_;
    std::size_t SmallObjSizeLimit_;

    using FixedAllocators = std::vector<FixedAllocator>;
    FixedAllocators pool_;

    int plastAlloc_;
    int plastDealloc_;

public:
    ~SmallObjAllocator();

    // All other constructors are deleted
    SmallObjAllocator () = delete;
    SmallObjAllocator (SmallObjAllocator const& other) = delete;
    SmallObjAllocator (SmallObjAllocator&& temp) = delete;
    SmallObjAllocator& operator = (SmallObjAllocator const& other) = delete;
    SmallObjAllocator& operator = (SmallObjAllocator&& temp) = delete;

    void* Allocate (std::size_t blockSize);
    void Deallocate (void *p, std::size_t blockSize);

    // FIXME: Clients need to call delete manually
    static SmallObjAllocator* getSmallObjAllocator (std::size_t numChunkBytes, std::size_t SmallObjSizeLimit)
    {
        if (!instance) {
            instance = new SmallObjAllocator(numChunkBytes, SmallObjSizeLimit);
        }
        
        return instance;
    }

    friend class SmallObjBase<SmallObjAllocator>;
};

#endif
