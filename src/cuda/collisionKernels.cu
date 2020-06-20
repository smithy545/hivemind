#include <cuda_runtime.h>


__device__ float *loadRect(const float *v, int offset) {
    auto rectArr = new float[8];
    rectArr[0] = v[offset];
    rectArr[1] = v[offset];
    rectArr[2] = v[offset+1];
    rectArr[3] = v[offset];
    rectArr[4] = v[offset];
    rectArr[5] = v[offset+1];
    rectArr[6] = v[offset+1];
    rectArr[7] = v[offset+1];
    return rectArr;
}

__device__ void rectCollision(float *v, int numComparisons) {
    for(int i = 0; i < numComparisons; i++) {
        //auto rect1 = loadRect(x, y, 8*i);
        //auto rect2 = loadRect(x, y, 8*i);
        // collision
    }
}
