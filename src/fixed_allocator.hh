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
    Chunk *lastAllocChunk_;
    Chunk *lastDeallocChunk_;

public:
    FixedAllocator(std::size_t blockSize, std::size_t numChunkBytes);

    void* Allocate ();
    void Deallocate (void *p);

    friend class SmallObjAllocator;
};

#endif