#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <Arduino.h>

class MemoryPool
{
public:
    MemoryPool(size_t blockSize, uint8_t blockCount);
    ~MemoryPool();

    void* allocate();
    void deallocate(void* ptr);

private:
    size_t _blockSize;
    uint8_t _blockCount;
    uint8_t* _pool;
    uint8_t* _freeList;

    void createFreeList();
};

#endif // MEMORY_POOL_H
