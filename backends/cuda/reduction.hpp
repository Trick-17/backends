#pragma once

#include "vector.hpp"

namespace backends
{
    namespace kernels
    {
        __inline__ __device__
        T warpReduceSum(T val)
        {
            for (int offset = warpSize/2; offset > 0; offset /= 2) 
                val += __shfl_down(val, offset);
            return val;
        }

        __inline__ __device__
        T blockReduceSum(T val)
        {
            static __shared__ T shared[32]; // Shared mem for 32 partial sums
            int lane = threadIdx.x % warpSize;
            int wid = threadIdx.x / warpSize;

            val = warpReduceSum(val);     // Each warp performs partial reduction

            if (lane==0) shared[wid]=val; // Write reduced value to shared memory

            __syncthreads();              // Wait for all partial reductions

            //read from shared memory only if that warp existed
            val = (threadIdx.x < blockDim.x / warpSize) ? shared[lane] : 0;

            if (wid==0) val = warpReduceSum(val); //Final reduce within first warp

            return val;
        }

        template<typename T>
        __global__ void sum(const T *in, T* out, int N)
        {
            // ToDo: this will only work with scalar types
            T sum = 0;
            for(int i = blockIdx.x * blockDim.x + threadIdx.x; 
                i < N; 
                i += blockDim.x * gridDim.x)
            {
                sum += in[i];
            }
            sum = blockReduceSum(sum);
            if (threadIdx.x == 0)
                atomicAdd(out, sum);
        }
    }

    template<typename T>
    T sum(vector<T>& vec)
    {
        int N = vec.size();
        int threads = 512;
        int blocks = min((N + threads - 1) / threads, 1024);

        vector<T> ret(1);
        kernels::sum<<<blocks, threads>>>(vec.data(), ret.data(), N);
        cudaDeviceSynchronize();
        return ret[0];
    }

    template<typename T>
    T mean(vector<T>& vec)
    {
        int N = vec.size();
        T ret = sum(vec)/N;
        return ret;
    }
}