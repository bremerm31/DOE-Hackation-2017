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

  const int dimx = 1000;
  const int dimy = 1000;
  const int dimcolor = 3;

  // Allocate our arrays
  Kokkos::View<double**> pixels("pixels", dimcolor*dimx*dimy);    

  // Create host mirror of C
  auto  pixels_mirror = Kokkos::create_mirror_view(pixels);

  // Make Mandelbrot set
  Kokkos::parallel_for(dimx*dimy, KOKKOS_LAMBDA(int idxy) {
      const size_t i = idxy/dimy;
      const size_t j = idxy%dimy;
      pixels(dimcolor*idxy) = 0.; // Mandelbrot(x(i),y(j));
  });
 
  // Update the mirror
  deep_copy(pixels_mirror, pixels);

  Kokkos::finalize();

  MPI_Finalize();

  return 0;
}
