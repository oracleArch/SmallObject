#include <assert.h>
#include "fixed_allocator.hh"

FixedAllocator::FixedAllocator (std::size_t blockSize, std::size_t numChunkBytes)
    : blockSize_(blockSize),
      lastAllocChunk_(-1),
      lastDeallocChunk_(-1)
{
    numBlocksPerChunk_ = numChunkBytes / blockSize_;
}

FixedAllocator::FixedAllocator (FixedAllocator&& temp) noexcept
{
    blockSize_ = temp.blockSize_;
    numBlocksPerChunk_ = temp.numBlocksPerChunk_;
    chunks_ = std::move(temp.chunks_);
    lastAllocChunk_ = temp.lastAllocChunk_;
    lastDeallocChunk_ = temp.lastDeallocChunk_;
}

void*
FixedAllocator::Allocate ()
{
    if (lastAllocChunk_ == -1 || chunks_.at(lastAllocChunk_).blocksAvailable_ == 0) {
        bool found = false;
        for (int i = 0; i < chunks_.size(); ++i) {
            if (chunks_[i].blocksAvailable_ > 0) {
                found = true;
                lastAllocChunk_ = i;
                break;
            }
        }

        if (!found) {
            chunks_.push_back(Chunk(blockSize_, numBlocksPerChunk_));
            lastAllocChunk_ = chunks_.size() - 1;
        }
    }

    assert(lastAllocChunk_ != -1 && chunks_.at(lastAllocChunk_).blocksAvailable_ > 0);

    return chunks_.at(lastAllocChunk_).Allocate(blockSize_);
}

void
FixedAllocator::Deallocate (void *p)
{
    if (lastDeallocChunk_ == -1 ||
        !chunks_.at(lastDeallocChunk_).isOwner(p, blockSize_, numBlocksPerChunk_)) {
        
        for (int i = 0; i < chunks_.size(); ++i) {
            if (chunks_[i].isOwner(p, blockSize_, numBlocksPerChunk_)) {
                lastDeallocChunk_ = i;
                break;
            }
        }
    }

    return chunks_.at(lastDeallocChunk_).Deallocate(p, blockSize_);
}