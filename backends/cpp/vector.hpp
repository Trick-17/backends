#pragma once

#include <memory>
#include <vector>

namespace backends
{
    template<typename T, typename Alloc = std::allocator<T> >
    using vector = std::vector<T, Alloc>;
}