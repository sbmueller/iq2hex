#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <iomanip>

int main(int argc, char* argv[])
{
  if(argc < 3) {
    std::cout << "Usage: " << argv[0] << " INPUT OUTPUT" << std::endl;
		return 1;
  }
  std::ifstream input(argv[1], std::ios::binary);
	std::vector<char> buffer((std::istreambuf_iterator<char>(input)), 
								           (std::istreambuf_iterator<char>()));
	input.close();
  std::ofstream output(argv[2]);
  bool samp_finished = false;
	output << std::uppercase << std::hex << std::setfill('0');
	std::cout << "Converting " << buffer.size()/8 << " Samples" << std::endl;
  for(unsigned int i = 0; i < buffer.size()-3; i += 4) {
    // only use 2 of 4 bytes (= 16 of 32 bit) per real and imaginary part
    output << std::setw(2)  << (int)(*(unsigned char*)(&buffer[i])) << std::setw(2) << (int)(*(unsigned char*)(&buffer[i+1]));
    if(samp_finished) {
      output << std::endl;
      samp_finished = false;
    } else {
      samp_finished = true;
    }
  }
  output.close();
  return 0;
}
