#include <iostream>
#include <fftw3.h>
#include <complex>
#include <cmath>
#include <chrono>

int main() {
    int ntrials = 3; 

    // Allocating memory
    int nx, ny, nz, nxyz, ix, iy, iz;
    double dx, dy, dz, x, y, z, phase;
    std::complex<double> *wave, *fft_3, *d_dx, *d_dy, *d_dz;
    fftw_plan forward_plan, backward_plan; 

    // Defining cubic lattice dimensions
    const double lx = 1.0; // Length of the cubic lattice in x-direction
    const double ly = 1.0; // Length of the cubic lattice in y-direction
    const double lz = 1.0; // Length of the cubic lattice in z-direction

    // Wave vector components in reciprocal lattice units
    const double kx = 2.0 * M_PI / lx * 2; // Wave vector component in x-direction
    const double ky = 2.0 * M_PI / ly * 3; // Wave vector component in y-direction
    const double kz = 2.0 * M_PI / lz * 4; // Wave vector component in z-direction

    for (int n = 16; n <= 512; n *= 2) {

        // Parameters
        nx = n;     // Number of lattice points in x-direction
        ny = n;     // Number of lattice points in y-direction
        nz = n;     // Number of lattice points in z-direction



        // Allocate memory for wave, fft_3, d_dx, d_dy, and d_dz arrays
        wave = new std::complex<double>[nxyz];
        fft_3 = new std::complex<double>[nxyz];
        d_dx = new std::complex<double>[nxyz];
        d_dy = new std::complex<double>[nxyz];
        d_dz = new std::complex<double>[nxyz];


        // Total time for all trials
        std::chrono::duration<double> total_time(0);

        for (int t = 1; t <= ntrials; ++t) {

            auto startTime = std::chrono::high_resolution_clock::now();

            // Create forward and backward FFTW plans
            forward_plan = fftw_plan_dft_3d(nx, ny, nz, reinterpret_cast<fftw_complex *>(wave),
                                                    reinterpret_cast<fftw_complex *>(fft_3), FFTW_FORWARD, FFTW_ESTIMATE);
            backward_plan = fftw_plan_dft_3d(nx, ny, nz, reinterpret_cast<fftw_complex *>(fft_3),
                                                    reinterpret_cast<fftw_complex *>(fft_3), FFTW_BACKWARD, FFTW_ESTIMATE);

            // Generate complex plane wave on the cubic lattice
            for (int i = 0; i < nxyz; ++i)
            {
                ix = i % nx;
                iy = (i / nx) % ny;
                iz = i / (nx * ny);
                x = (ix - nx / 2) * dx;
                y = (iy - ny / 2) * dy;
                z = (iz - nz / 2) * dz;
                phase = kx * x + ky * y + kz * z;

                wave[i] = std::polar(1.0, phase);
            }

            // Perform forward FFT
            fftw_execute(forward_plan);

            // Copy the forward transform to wave 
            for (int i = 0; i < nxyz; ++i)
            {
                wave[i] = fft_3[i];
            }

            // Compute d/dx
            for (int i = 0; i < nxyz; ++i)
            {
                fft_3[i] = wave[i] * std::complex<double>(0.0, kx);
            }
            fftw_execute(backward_plan);
            for (int j = 0; j < nxyz; ++j)
            {
                d_dx[j] = fft_3[j] / static_cast<double>(nxyz);
            }

            // Compute d/dy
            for (int i = 0; i < nxyz; ++i)
            {
                fft_3[i] = wave[i] * std::complex<double>(0.0, ky);
            }
            fftw_execute(backward_plan);
            for (int j = 0; j < nxyz; ++j)
            {
                d_dy[j] = fft_3[j] / static_cast<double>(nxyz);
            }

            // Compute d/dz
            for (int i = 0; i < nxyz; ++i)
            {
                fft_3[i] = wave[i] * std::complex<double>(0.0, kz);
            }
            fftw_execute(backward_plan);
            for (int j = 0; j < nxyz; ++j)
            {
                d_dz[j] = fft_3[j] / static_cast<double>(nxyz);
            }

            auto endTime = std::chrono::high_resolution_clock::now();

            total_time += endTime - startTime;
        }
        
        // Clean up
        fftw_destroy_plan(forward_plan);
        fftw_destroy_plan(backward_plan);
        delete[] wave;
        delete[] fft_3;
        delete[] d_dx;
        delete[] d_dy;
        delete[] d_dz;

        double avg_time = total_time.count() / ntrials;

        std::cout << "n=" << n << ": " << avg_time << std::endl;
    }

    return 0;
}