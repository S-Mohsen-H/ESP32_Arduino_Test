#include "MemoryPool.h"

MemoryPool::MemoryPool(size_t blockSize, uint8_t blockCount)
    : _blockSize(blockSize), _blockCount(blockCount)
{
    _pool = new uint8_t[_blockSize * _blockCount];
    createFreeList();
}

MemoryPool::~MemoryPool()
{
    delete[] _pool;
}

void* MemoryPool::allocate()
{
    if (!_freeList)
        return nullptr;

    void* ptr = _freeList;
    _freeList = *reinterpret_cast<uint8_t**>(_freeList);
    return ptr;
}

void MemoryPool::deallocate(void* ptr)
{
    if (!ptr)
        return;

    *reinterpret_cast<uint8_t**>(ptr) = _freeList;
    _freeList = static_cast<uint8_t*>(ptr);
}

void MemoryPool::createFreeList()
{
    _freeList = _pool;

    for (uint8_t i = 0; i < _blockCount - 1; ++i)
    {
        uint8_t* next = _pool + (i + 1) * _blockSize;
        *reinterpret_cast<uint8_t**>(_pool + i * _blockSize) = next;
    }

    *reinterpret_cast<uint8_t**>(_pool + (_blockCount - 1) * _blockSize) = nullptr;
}
