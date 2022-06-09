#ifndef G_MEM_MAC_MACPROCESS_H
#define G_MEM_MAC_MACPROCESS_H

#include "../Process.h"

class MacProcess
        : public Process
{
    using Process::Process;

public:
    void readMemoryChunks() override;
};

#endif //G_MEM_MAC_MACPROCESS_H
