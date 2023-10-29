#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

std::vector<int> GenerateRandomSequence(int count)
{
    std::random_device seed;
    std::ranlux48 engine(seed());
    std::uniform_int_distribution uniformInt_09(0,9);

    std::vector<int> sequence;

    for(int i=0;i<count;i++)
    {
        sequence.emplace_back(uniformInt_09(engine));
    }

    return sequence;
}

bool SearchElement(const std::vector<int> &pageTable, int element)
{
    if (pageTable.size() == 0)
        return false;

    for (auto i : pageTable)
    {
        if (i == element)
            return true;
    }

    return false;
}

void FIFOMaintainFrame(std::vector<int> &pageTable, std::vector<int> &queue,const int element, int frameMaxCount)
{
    if (pageTable.size() < frameMaxCount)
    {
        pageTable.emplace_back(element);
        queue.emplace_back(element);
    }
    else
    {
        auto pos = std::find(pageTable.begin(), pageTable.end(), queue[0]);
        *pos = element;
        queue.erase(queue.begin());
        queue.emplace_back(element);
    }

    // std::cout << "current page table: ";
    // for(auto i : pageTable)
    // {
    //    std::cout << i << " ";
    // }
    // std::cout << std::endl;
}

size_t PageStorage(const std::vector<int> &pageSequence, int frameMaxCount)
{
    // for(auto i : pageSequence)
    // {
    //     std::cout << i << " ";
    // }

    size_t pageFault = 0;

    std::vector<int> pageTable;
    std::vector<int> queue;

    for (auto i : pageSequence)
    {
         //std::cout << "current page: "<< i << " ";
         if(SearchElement(pageTable,i))
             continue;
    
         pageFault++;
         FIFOMaintainFrame(pageTable,queue,i,frameMaxCount);
    }
    //std::cout << std::endl;

    return pageFault;
}

int main()
{
    auto&& sequence = GenerateRandomSequence(15);
    std::cout << "Page Sequence: "<<std::endl;
    for(auto i : sequence)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    auto faultCount = PageStorage(sequence,5);
    std::cout << "Page Fault: " << faultCount<<std::endl;

}