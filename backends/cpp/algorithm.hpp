#pragma once

#include <algorithm>
#include "vector.hpp"

namespace backends
{
    template<typename T>
    void fill(vector<T>& vec, const T& val)
    {
        #pragma omp parallel for
        for (unsigned int i = 0; i<vec.size(); ++i)
        {
            vec[i] = val;
        }
    }
}