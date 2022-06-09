#include <mach/arm/vm_types.h>
#include <mach/vm_region.h>
#include <mach/mach_vm.h>
#include <iostream>
#include <mach/mach_init.h>
#include "MacProcess.h"

void MacProcess::readMemoryChunks()
{
    int returnCode;
    mach_port_t task;

    returnCode = task_for_pid(mach_task_self_, mPid, &task);
    if (returnCode != KERN_SUCCESS)
    {
        std::cout << "task_for_pid() failed. kret = " << returnCode << "\n";
        exit(EXIT_FAILURE);
    }

    uint64_t address = 0;
    uint64_t size = 0;
    mach_port_t obj_name;
    struct vm_region_basic_info_64 info{};
    natural_t count = VM_REGION_BASIC_INFO_COUNT_64;

    while (::mach_vm_region(task, &address, &size, VM_REGION_BASIC_INFO_64,
                            (int *) &info, &count, &obj_name) ==
           KERN_SUCCESS)
    {
        mChunks.push_back(
                new MemoryChunk(reinterpret_cast<void *>(address), size));
        address += size;
    }
}