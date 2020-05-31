#ifndef __CHUNK_HH__
#define __CHUNK_HH__

#include <cstdlib>

/*
 * Lowest level memory chunk
 */
struct Chunk
{
    Chunk(std::size_t blockSize, unsigned char numBlocks);
    ~Chunk();

    // Copy Semantics are deleted
    Chunk (Chunk const& other) = delete;
    Chunk& operator = (Chunk const& other) = delete;

    // Move assignment is deleted
    Chunk& operator = (Chunk&& temp) = delete;

    // Move constructor is declared with noexcept
    Chunk (Chunk&& temp) noexcept;

    // void Init (std::size_t blockSize, unsigned char numBlocks);
    void* Allocate (std::size_t blockSize);
    void Deallocate (void *p, std::size_t blockSize);
    
    inline bool isOwner (void *p, std::size_t blockSize, unsigned char numBlocks) const
    {
        return p >= pData_ && p < (pData_ + blockSize * numBlocks);
    }

    unsigned char *pData_;
    unsigned char firstAvailableBlock_;
    unsigned char blocksAvailable_;
};

#endif