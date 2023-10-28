#include <iostream>
#include <vector>
#include <string>

struct Task
{
    uint32_t requiredMemory;
    uint32_t assignedAddress;
};

struct SparedMemoryBlock
{
    uint32_t startAddress;
    uint32_t memorySize;

    SparedMemoryBlock(uint32_t _startAddress, uint32_t _memorySize) 
    : startAddress(_startAddress) , memorySize(_memorySize) {}
};

bool AllocateMemory(std::vector<SparedMemoryBlock> &storageQueue, Task &task)
{
    for (size_t i = 0; i < storageQueue.size(); i++)
    {
        if (storageQueue[i].memorySize >= task.requiredMemory)
        {
            task.assignedAddress = storageQueue[i].startAddress;
            storageQueue[i].startAddress += task.requiredMemory;
            storageQueue[i].memorySize -= task.requiredMemory;

            return true;
        }
    }

    return false;
}

void ReclaimMemory(std::vector<SparedMemoryBlock> &storageQueue, Task &task)
{
    uint32_t startAddress = task.assignedAddress;
    uint32_t endAddress = task.requiredMemory + startAddress;

    auto i = storageQueue.begin();
    for (; i < storageQueue.end(); i++)
    {
        if (i->startAddress > endAddress)
            break;

        if (i->startAddress == endAddress)
        {
            endAddress += i->memorySize;
            i = storageQueue.erase(i);
            i--;
        }
        else if (i->startAddress + i->memorySize == startAddress)
        {
            startAddress = i->startAddress;
            i = storageQueue.erase(i);
            i--;
        }
    }
    storageQueue.emplace(i, startAddress, endAddress - startAddress);
}

void PrintQueque(const std::vector<SparedMemoryBlock> &storageQueue)
{
    size_t count = 0;

    for (auto i : storageQueue)
    {
        std::cout << "Number: " << count << " " << i.startAddress << " " << i.memorySize << std::endl;
        count++;
    }
}

int main()
{
    std::vector<SparedMemoryBlock> storageQueue;
    storageQueue.emplace_back(0, 1000);

    Task taskPool[100];

    std::string in;
    int a, b; // a: number  b: memoryRequire

    while ((std::cin >> in) && in != "#")
    {
        if (in[0] == 'A')
        {
            std::cin >> a >> b;
            taskPool[a].requiredMemory = b;
            bool success = AllocateMemory(storageQueue, taskPool[a]);
            if (success)
            {
                PrintQueque(storageQueue);
            }
            else
            {
                std::cout << "fail to allocate!" << std::endl;
            }
        }
        if(in[0] == 'R')
        {
            std::cin >> a;
            ReclaimMemory(storageQueue, taskPool[a]);
            PrintQueque(storageQueue);
        }
    }
}