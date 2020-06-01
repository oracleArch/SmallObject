#include "small_obj_allocator.hh"
#include <iostream>

// nullify static instance unique pointer
std::unique_ptr<SmallObjAllocator> SmallObjAllocator::instance(nullptr);

SmallObjAllocator::SmallObjAllocator (std::size_t numChunkBytes, std::size_t SmallObjSizeLimit)
    : numChunkBytes_(numChunkBytes),
      SmallObjSizeLimit_(SmallObjSizeLimit),
      plastAlloc_(-1),
      plastDealloc_(-1)
{
}

void*
SmallObjAllocator::Allocate (std::size_t blockSize)
{
    if (blockSize > SmallObjSizeLimit_) {
        return new unsigned char[blockSize];
    }

    if (plastAlloc_ == -1 || pool_.at(plastAlloc_).blockSize_ != blockSize) {
        bool found = false;
        for (int i = 0; i < pool_.size(); ++i) {
            if (pool_[i].blockSize_ == blockSize) {
                found = true;
                plastAlloc_ = i;
                break;
            }
        }

        if (!found) {
            pool_.push_back(FixedAllocator(blockSize, numChunkBytes_));
            plastAlloc_ = pool_.size() - 1;
        }
    }

    return pool_.at(plastAlloc_).Allocate();
}

void
SmallObjAllocator::Deallocate (void *p, std::size_t blockSize)
{
    if (blockSize > SmallObjSizeLimit_) {
        free(p);
        return;
    }

    if (plastDealloc_ == -1 || pool_.at(plastDealloc_).blockSize_ != blockSize) {
        for (int i = 0; i < pool_.size(); ++i) {
            if (pool_[i].blockSize_ == blockSize) {
                plastDealloc_ = i;
                break;
            }
        }
    }

    return pool_.at(plastDealloc_).Deallocate(p);
}