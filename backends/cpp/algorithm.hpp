#pragma once

#include <algorithm>
#include "vector.hpp"

namespace backends
{
    template<typename T>
    void fill(vector<T>& vec, const T& val)
    {
        std::fill(vec.begin(), vec.end(), val);
    }
}