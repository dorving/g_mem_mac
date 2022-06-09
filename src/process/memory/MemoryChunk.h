#ifndef G_MEM_MAC_MEMORYCHUNK_H
#define G_MEM_MAC_MEMORYCHUNK_H

#include <cstddef>

/**
 * Represents a piece of
 */
class MemoryChunk
{
public:
    MemoryChunk(void *start, std::size_t size);
    void *mStart;
    size_t mSize;
};

#include <vector>

#endif //G_MEM_MAC_MEMORYCHUNK_H
