#pragma once

#include <vector>

namespace backends
{
    template<typename T, typename Alloc = allocator<T> >
    using vector = std::vector<T, Alloc>;
}