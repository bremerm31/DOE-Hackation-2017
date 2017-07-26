#include <iostream>
#include <Kokkos_Core.hpp>
#include <Kokkos_Parallel.hpp>
#include <Kokkos_View.hpp>
#include "mpi.h"
#include <assert.h>
#include <limits> 

int main(int argc, char **argv) {
  // Initialize MPI before Kokkos
  MPI_Init(&argc, &argv);

  // Initialize Kokkos
  Kokkos::initialize(argc, argv);

  const float center_x = -0.75;
  const float center_x = -0.;

  const float length_x = 2.75;
  const float length_y = 2.;
  
  const float min_x = center_x - length_x/2.;
  const float max_y = center_y + length_y/2.;
 
  const size_t dimx = 8192;
  const float pixel_sz = length_x/dimx;
  const size_t dimy = length_y/pixel_sz;
  const size_t dimcolor = 3;

  // Allocate our arrays
  Kokkos::View<double**> pixels("pixels", dimcolor*dimx*dimy);    

  // Create host mirror of C
  auto  pixels_mirror = Kokkos::create_mirror_view(pixels);

  // Make Mandelbrot set
  Kokkos::parallel_for(dimx*dimy, KOKKOS_LAMBDA(int idxy) {
      const size_t i = idxy/dimy;
      const size_t j = idxy%dimy;
      pixels(dimcolor*idxy) = Mandelbrot(x(i),y(j), pixel_sz);
  });
 
  // Update the mirror
  deep_copy(pixels_mirror, pixels);

  Kokkos::finalize();

  MPI_Finalize();

  return 0;
}
