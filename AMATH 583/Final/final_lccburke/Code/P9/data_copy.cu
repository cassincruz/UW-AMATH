#include <iostream>
#include <cuda.h>
#include <cuda_runtime.h>
#include <chrono>

int main()
{
    std::cout << "Time to/from CPU/GPU by buffer size" << std::endl;
    for (int dataSize = 8; dataSize <= 256; dataSize *= 2) {

        std::cout<< dataSize << " bytes: ";
        
        // Allocate and initialize input data on the host
        int *hostData = new int[dataSize]; 
        for (int i = 0; i < dataSize; i++) {
            hostData[i] = i + 1;
        }

        // Allocate memory on the device
        int *deviceData;
        cudaMalloc((void **)&deviceData, dataSize * sizeof(int));

        // Copy input data from host to device
        std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
        cudaMemcpy(deviceData, hostData, dataSize * sizeof(int), cudaMemcpyHostToDevice);
        std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        std::cout << "To GPU: " << duration << " microseconds "; 

        // Copy data back to host from device
        startTime = std::chrono::high_resolution_clock::now();
        cudaMemcpy(hostData, deviceData, dataSize * sizeof(int), cudaMemcpyDeviceToHost);
        endTime = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

        std::cout << "To CPU: " << duration << " microseconds" << std::endl;

        // Free memory
        delete[] hostData;
        cudaFree(deviceData);
    }

    return 0;
}
