#include "MemoryChunk.h"

MemoryChunk::MemoryChunk(void *start, size_t size) :
        mStart(start),
        mSize(size)
{}