#ifndef G_MEM_MAC_PROCESS_H
#define G_MEM_MAC_PROCESS_H

static const int DEFAULT_THREAD_COUNT = 5;

#include <vector>
#include "memory/MemoryChunk.h"

class Process
{
public:
    Process();

    explicit Process(pid_t pid);

    void extractRC4Maps(int threadCount);

    void extractRC4Map(MemoryChunk *chunk);

    void printRC4Possibilities();

    void printCachedResults(const std::vector<unsigned char *>& cache);

    ~Process();

    std::vector<MemoryChunk *> GetChunks();

private:
    std::vector<MemoryChunk *> mRC4Maps;
    std::vector<void *> mOutCache;

    /**
     * Read memory of external process
     *
     * @return a vector of MemoryChunk objects
     */
    virtual void readMemoryChunks() = 0;

    void clear();

protected:
    std::vector<MemoryChunk *> mChunks;
    pid_t mPid;

    void deleteChunkAndRC4References();
};


#endif //G_MEM_MAC_PROCESS_H
