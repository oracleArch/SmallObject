#include "small_obj_allocator.hh"

// nullify static instance variable
SmallObjAllocator *SmallObjAllocator::instance = nullptr;

SmallObjAllocator::SmallObjAllocator (std::size_t numChunkBytes, std::size_t SmallObjSizeLimit)
    : numChunkBytes_(numChunkBytes),
      SmallObjSizeLimit_(SmallObjSizeLimit),
      plastAlloc_(nullptr),
      plastDealloc_(nullptr)
{
}

SmallObjAllocator::~SmallObjAllocator()
{
    instance = nullptr;
}

void*
SmallObjAllocator::Allocate (std::size_t blockSize)
{
    if (blockSize > SmallObjSizeLimit_) {
        return new unsigned char[blockSize];
    }
    
    if (!plastAlloc_ || plastAlloc_->blockSize_ != blockSize) {
        bool found = false;
        for (auto& fa : pool_) {
            if (fa.blockSize_ == blockSize) {
                found = true;
                plastAlloc_ = &fa;
                break;
            }
        }

        if (!found) {
            pool_.push_back(FixedAllocator(blockSize, numChunkBytes_));
            plastAlloc_ = &pool_.back();
        }
    }
    
    return plastAlloc_->Allocate();
}

void
SmallObjAllocator::Deallocate (void *p, std::size_t blockSize)
{
    if (blockSize > SmallObjSizeLimit_) {
        free(p);
        return; 
    }

    if (plastDealloc_ &&
        plastDealloc_->blockSize_ == blockSize) {
        
        plastDealloc_->Deallocate(p);
    } else {
        for (auto& fa : pool_) {
            if (fa.blockSize_ == blockSize) {
                fa.Deallocate(p);
                plastDealloc_ = &fa;
                break;
            }
        }
    }
}