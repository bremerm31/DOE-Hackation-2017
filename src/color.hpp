#ifndef COLOR_HPP
#define COLOR_HPP

KOKKOS_INLINE_FUNCTION
void color( const float distance,
	    const int iterations,
	    const float radius,
	    const float pixel_sz,
	    char* RGD )
{
  if ( distance < 0.5 *pixel_sz ) {
    RGB[0] =  pow( distance/ (0.5 * pixel_sz), 1/3 );
  } else {
    return 255;
  }
}
#endif
