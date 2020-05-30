#include <assert.h>
#include "fixed_allocator.hh"

FixedAllocator::FixedAllocator (std::size_t blockSize, std::size_t numChunkBytes)
    : blockSize_(blockSize),
      lastAllocChunk_(nullptr),
      lastDeallocChunk_(nullptr)
{
    numBlocksPerChunk_ = numChunkBytes / blockSize_;
}

void*
FixedAllocator::Allocate ()
{
    if (!lastAllocChunk_ || lastAllocChunk_->blocksAvailable_ == 0) {
        bool found = false;
        for (auto& chunk : chunks_) {
            if (chunk.blocksAvailable_ > 0) {
                found = true;
                lastAllocChunk_ = &chunk;
                break;
            }
        }

        if (!found) {
            chunks_.push_back(Chunk(blockSize_, numBlocksPerChunk_));
            lastAllocChunk_ = &chunks_.back();
        }
    }

    assert(lastAllocChunk_ && lastAllocChunk_->blocksAvailable_ > 0);
    return lastAllocChunk_->Allocate(blockSize_);
}

void
FixedAllocator::Deallocate (void *p)
{
    if (lastDeallocChunk_ &&
        lastDeallocChunk_->isOwner(p, blockSize_, numBlocksPerChunk_)) {
        
        lastDeallocChunk_->Deallocate(p, blockSize_);
    } else {
        for (auto& chunk : chunks_) {
            if (chunk.isOwner(p, blockSize_, numBlocksPerChunk_)) {
                chunk.Deallocate(p, blockSize_);
                lastDeallocChunk_ = &chunk;
                break;
            }
        }
    }
}