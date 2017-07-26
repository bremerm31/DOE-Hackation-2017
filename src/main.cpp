#include <iostream>
#include <Kokkos_Core.hpp>
#include <Kokkos_Parallel.hpp>
#include <Kokkos_View.hpp>
#include "mpi.h"
#include <assert.h>
#include <limits> 
#include "color.hpp"
#include "mandelbrot.hpp"
#include "writer.hpp"

int main(int argc, char **argv) {
  // Initialize MPI before Kokkos
  MPI_Init(&argc, &argv);

  // Initialize Kokkos
  Kokkos::initialize(argc, argv);

  const float center_x = -0.75;
  const float center_y = -0.;

  const float length_x = 2.75;
  const float length_y = 2.;
  
  const float min_x = center_x - length_x/2.;
  const float max_y = center_y + length_y/2.;
 
  const size_t dimx = 8192;
  const float pixel_sz = length_x/dimx;
  const size_t dimy = length_y/pixel_sz;
  const size_t dimcolor = 3;

  // Allocate our arrays
  Kokkos::View<char**> pixels("pixels", dimcolor, dimx*dimy);    

  // Create host mirror of C
  auto pixels_mirror = Kokkos::create_mirror_view(pixels);

  int iterations = 1;
  Kokkos::Timer timer;
  for(int i=0; i<iterations; i++) {

  // Make Mandelbrot set
  Kokkos::parallel_for(dimx*dimy, KOKKOS_LAMBDA(int idxy) {
      const size_t i = idxy%dimx;
      const size_t j = idxy/dimx;
      const float x = min_x + i*pixel_sz;
      const float y = max_y - j*pixel_sz;
      auto ptr = Kokkos::subview(pixels, Kokkos::ALL(), idxy);
      Mandelbrot(x, y, pixel_sz, ptr);
  });

  }
  std::cout << "Avg time (s): " << (float) timer.seconds()/iterations << std::endl;
 
  // Update the mirror
  deep_copy(pixels_mirror, pixels);

  // write to file
  write_bw_to("mandelbrot.ppm", dimx, dimy, pixels_mirror);

  Kokkos::finalize();

  MPI_Finalize();

  return 0;
}
