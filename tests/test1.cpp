//zis is cuda

#include "backends/cpp/vector.hpp"
#include "backends/cpp/algorithm.hpp"

int main()
{
    auto myVec = backends::vector<int>(1);
    myVec.front() = 13;
    backends::fill(myVec, 12);
    check(myVec.front() == 12);
}