#include "lz77.h" // header dari sini https://github.com/ivan-tkatchev/yalz77
#include <iostream>
#include <fstream>
#include <string>

int main() {


	lz77::compress_t compress;
	lz77::decompress_t decompress;

	std::ofstream wr;
	std::ifstream op;

	std::vector<unsigned char> separator{0x00, 0x24, 0x00};
	std::vector<unsigned char> eof{0x00, 0x22, 0x00};

	int buffer_size = 256*192;
	int count = 0;

	// compress
	wr.open("data_compress.dat", std::ios::out | std::ios::binary);
	op.open("data_raw.dat", std::ios::in | std::ios::binary);
	std::vector<unsigned char> buffer(buffer_size, 0);
	while(!op.eof()) {
		op.read((char*)&buffer[0], buffer.size());
		std::streamsize s=op.gcount();
	    if (s == 0) break;

	    std::string temp("");
		for (int i=0; i<buffer.size(); i++) temp.push_back(buffer[i]);
		std::string compressed = compress.feed(temp);

		wr << compressed;
		wr.write((char *)&separator[0], separator.size());

		count++;
		std::cout<< count << std::endl;
	}
	wr.write((char *)&eof[0], eof.size());
	wr.close();
	op.close();

	std::cout<< "done writing "<< count << std::endl;

  return 0;
}
