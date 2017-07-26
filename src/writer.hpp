#ifndef WRITER_HPP
#define WRITER_HPP

#include <fstream>

void write_bw_to( const std::string& file_name,
		  const std::size_t dimx,
		  const std::size_t dimy,
		  const char* RGB_array)
{
  std::ostream file;
  ofstream.open( file_name, std::fstream::out );

  file << "P5\n";
  file << dim_x << " " << dim_y << "\n";
  file << "255\n";
  file.close();
  file.open( file_name, std::fstream::app | ios::binary);
  for ( std::size_t y = 0; y < dimy; ++y ) {
    for ( std::size_t x = 0; x < dimx; ++x ) {
      file << RGB_array[ 3*(x + dimx*y) ];
    }
  }
  file.close();
}
#endif
