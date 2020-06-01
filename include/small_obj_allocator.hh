#ifndef __SMALL_OBJ_ALLOCATOR_HH__
#define __SMALL_OBJ_ALLOCATOR_HH__

#include <memory>
#include "fixed_allocator.hh"

// Forward declaring to allow friend class
template <typename Alloc>
class SmallObjBase;

class SmallObjAllocator
{
private:
    static std::unique_ptr<SmallObjAllocator> instance;

    // Private constructor for being singleton
    SmallObjAllocator (std::size_t numChunkBytes, std::size_t SmallObjSizeLimit);

    std::size_t numChunkBytes_;
    std::size_t SmallObjSizeLimit_;

    using FixedAllocators = std::vector<FixedAllocator>;
    FixedAllocators pool_;

    int plastAlloc_;
    int plastDealloc_;

public:
    // All other constructors are deleted
    SmallObjAllocator () = delete;
    SmallObjAllocator (SmallObjAllocator const& other) = delete;
    SmallObjAllocator (SmallObjAllocator&& temp) = delete;
    SmallObjAllocator& operator = (SmallObjAllocator const& other) = delete;
    SmallObjAllocator& operator = (SmallObjAllocator&& temp) = delete;

    void* Allocate (std::size_t blockSize);
    void Deallocate (void *p, std::size_t blockSize);

    /* 
     * Singleton class with instance being a smart pointer (unique).
     * This allows for automatic garbage collection as clients
     * only need to call this function without worrying about
     * destructing SmallObjAllocator.
     */
    static void createSmallObjAllocator (std::size_t numChunkBytes, std::size_t SmallObjSizeLimit)
    {
        if (!instance) {
            instance.reset(new SmallObjAllocator(numChunkBytes, SmallObjSizeLimit));
        }
    }

    friend class SmallObjBase<SmallObjAllocator>;
};

#endif
