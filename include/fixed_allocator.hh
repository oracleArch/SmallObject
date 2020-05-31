#ifndef __FIXEDALLOCATOR_HH__
#define __FIXEDALLOCATOR_HH__

#include <vector>
#include "chunk.hh"

class FixedAllocator
{
private:
    std::size_t blockSize_;
    unsigned char numBlocksPerChunk_;

    using Chunks = std::vector<Chunk>;

    Chunks chunks_;
    int lastAllocChunk_;
    int lastDeallocChunk_;

public:
    FixedAllocator (std::size_t blockSize, std::size_t numChunkBytes);

    // Move constructor
    FixedAllocator (FixedAllocator&& temp) noexcept;

    // All other constructors are deleted
    FixedAllocator () = delete;
    FixedAllocator (FixedAllocator const& other) = delete;
    FixedAllocator& operator = (FixedAllocator const& other) = delete;
    FixedAllocator&& operator = (FixedAllocator&& temp) = delete;


    void* Allocate ();
    void Deallocate (void *p);

    friend class SmallObjAllocator;
};

#endif