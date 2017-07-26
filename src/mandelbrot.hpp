#include "color.hpp"
#include <Kokkos_Complex.hpp>

#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

KOKKOS_INLINE_FUNCTION
void Mandelbrot(const float x, const float y, const float pixel_sz, Kokkos::View<char*> rgb)
{
  unsigned int iter = 0;
  const unsigned int iter_max = 10000;
  float radius = 0.;
  Kokkos::complex<float> z(0.,0.);
  Kokkos::complex<float> dz(0.,0.);
  Kokkos::complex<float> c(x,y);
  float radius_max = 1<<18;
  float distance = 0.;
  while ( radius < radius_max && iter < iter_max ) {
    dz = 2.f*z*dz + 1.f;
    z = z*z + c;
    radius = abs(z);
    iter++;
  }
  distance = 2*log(abs(z))*abs(z)/abs(dz);
  color(distance, iter, radius, pixel_sz, rgb);
}

#endif
