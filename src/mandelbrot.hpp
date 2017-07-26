#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

KOKKOS_INLINE_FUNCTION
char* Mandelbrot(const float x, const float y, const float pixel_sz)
{
  const unsigned int iter = 0;
  const unsigned int iter_max = 10000;
  float radius,z,dz = 0.;
  float radius_max = 1<<18;
  float distance = 0.;
  while ( radius < radius_max && iter < iter_max ) {
    dz = 2.*z*dz + 1.;
    z = z*z + c;
    radius = abs(z);
    iter++;
  }
  char* rgb;
  color(distance, iterations, radius, pixel_sz, rgb);
  return rgb;
}

#endif
