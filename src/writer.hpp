#ifndef WRITER_HPP
#define WRITER_HPP

#include <fstream>

template<class mirror_t>
void write_bw_to( const std::string& file_name,
		  const std::size_t dimx,
		  const std::size_t dimy,
		  mirror_t RGB_array)
{
  std::cout << "about to write to file!" << std::endl;
//  std::ofstream file;
//  file.open( file_name, std::fstream::out );
//
//  file << "P5\n";
//  file << dimx << " " << dimy << "\n";
//  file << "255\n";
//  file.close();
//  file.open( file_name, std::fstream::app | std::ios::binary);
//  for ( std::size_t y = 0; y < dimy; ++y ) {
//    for ( std::size_t x = 0; x < dimx; ++x ) {
//      file << 255;// RGB_array( 0, (x + dimx*y) );
//    }
//  }
//  file.close();

  std::ofstream output(file_name, std::ios::binary|std::ios::out);
  if(!output){
  std::cout << " unable to open the output file â"<< file_name << std::endl;
  }
  else{
  output << "P5" << std::endl;
  output << dimx;
  output << " ";
  output << dimy;
  output << std::endl;
  output << 255 << std::endl;
  for ( std::size_t y = 0; y < dimy; ++y ) {
    for ( std::size_t x = 0; x < dimx; ++x ) {
      output << RGB_array(0,x+dimx*y);
    }
  }
  std::cout << "wrote to file!" << std::endl;
  output.close();
  }
}
#endif
