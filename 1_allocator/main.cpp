#include "./common/log.h"
#include "alloctor.h"
#include  <vector>

using namespace std;;
int main()
{
    // ZAV::allocator<int>;
    int data[5] = {1, 2, 3, 4, 5};
    std::vector<int, ZAV::allocator<int>> tmp(data, data + 5);
    for (auto item : tmp)
    {
        ZLOGI("item=[%d]", item);
    }
}
