#pragma once

#include "vector.hpp"

namespace backends
{
    template<typename T>
    T sum(vector<T>& vec)
    {
        T ret = 0;
        for (unsigned int i = 0; i<vec.size(); ++i)
        {
            ret += vec[i];
        }
        return ret;
    }

    template<typename T>
    T mean(vector<T>& vec)
    {
        int N = vec.size();
        T ret = sum(vec)/N;
        return ret;
    }
}