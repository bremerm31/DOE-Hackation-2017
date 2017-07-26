#ifndef WRITER_HPP
#define WRITER_HPP

#include <fstream>

template<class mirror_t>
void write_bw_to( const std::string& file_name,
		  const std::size_t dimx,
		  const std::size_t dimy,
		  mirror_t RGB_array)
{
  std::ofstream file;
  file.open( file_name, std::fstream::out );

  file << "P5\n";
  file << dimx << " " << dimy << "\n";
  file << "255\n";
  file.close();
  file.open( file_name, std::fstream::app | std::ios::binary);
  for ( std::size_t y = 0; y < dimy; ++y ) {
    for ( std::size_t x = 0; x < dimx; ++x ) {
      file << 0;// RGB_array( 0, (x + dimx*y) );
    }
  }
  file.close();
}
#endif
