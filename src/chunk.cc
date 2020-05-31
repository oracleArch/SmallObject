#include <assert.h>
#include "chunk.hh"

Chunk::Chunk (std::size_t blockSize, unsigned char numBlocks)
{
    pData_ = new unsigned char[blockSize * numBlocks];
    firstAvailableBlock_ = 0;
    blocksAvailable_ = numBlocks;
    unsigned char *p = pData_;
    for (unsigned char i = 0; i < numBlocks; p += blockSize) {
        *p = ++i;
    }
}

Chunk::~Chunk()
{
    if (pData_) {
        delete [] pData_;
    }
}

Chunk::Chunk (Chunk&& temp) noexcept
{
    pData_ = temp.pData_;
    temp.pData_ = nullptr;
    firstAvailableBlock_ = temp.firstAvailableBlock_;
    blocksAvailable_ = temp.blocksAvailable_;
}

void*
Chunk::Allocate (std::size_t blockSize)
{
    if (!blocksAvailable_)
        return nullptr;
    
    unsigned char *pResult = pData_ + (firstAvailableBlock_ * blockSize);
    firstAvailableBlock_ = *pResult;
    --blocksAvailable_;
    
    return pResult;
}

void
Chunk::Deallocate (void *p, std::size_t blockSize)
{
    assert(p >= pData_);

    unsigned char *toRelease = static_cast<unsigned char *> (p);

    // Check for alignment
    assert((toRelease - pData_) % blockSize == 0);

    *toRelease = firstAvailableBlock_;
    firstAvailableBlock_ = static_cast<unsigned char> ((toRelease - pData_) / blockSize);

    assert(firstAvailableBlock_ == (toRelease - pData_) / blockSize);

    ++blocksAvailable_;
}