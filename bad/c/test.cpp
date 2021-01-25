#include "lz77.h" // header dari sini https://github.com/ivan-tkatchev/yalz77
#include <iostream>
#include <fstream>
#include <string>

int main() {
	int list_length = 256*192*3;

	// std::ofstream write;
	// write.open ("data_raw.dat", std::ios::out | std::ios::binary);
	// // for (int i=0; i< 10; i++) {
	// 	unsigned char list[5] = {120, 150, 200, 240, 255};
	// 	// for (int i=0; i<(list_length); i++) {
	// 		// unsigned char random = (unsigned char) rand();
	// 		// list[i] = random;
	// 	// }
	// 	write.write((char *) &list, sizeof(list));
	// // }
	// write.close();

	// read buffer
	lz77::compress_t compress;

	// // save to file
	std::ofstream wr;
	wr.open ("data_compress.dat", std::ios::out | std::ios::binary);
	// wr << compressed;
	// wr.close();

	std::ifstream in("data_raw.dat", std::ios::in | std::ios::binary);
	unsigned char * buffer = new unsigned char[256*192]();

	std::cout<<"buffer size "<<sizeof(buffer)<<std::endl;

	int count = 0;

	char nol[3] = {0x00, 0x44, 0x00};

	while(!in.eof()) {
	    in.read((char*)buffer, 256*192);
	    std::streamsize s=in.gcount();
	    if (s == 0) break;
	    ///do with buffer

	    std::string compressed = compress.feed(reinterpret_cast<char*>(buffer));
	    wr << compressed;
	    count++;
	    wr.write(nol, sizeof(nol));

	    std::cout<<count<<std::endl;
	}
	in.close();
	wr.close();

	std::cout<<count<<std::endl;

	// read
	// std::ifstream in2("append.txt", std::ios::in | std::ios::binary);
	// std::string data;
	// in2.seekg(0, std::ios::end);
	// data.resize(in2.tellg());
	// in2.seekg(0, std::ios::beg);
	// in2.read(&data[0], data.size());
	// in2.close();

	// char * data_char = const_cast<char*>(data.c_str());
	// for (int i=0; i<5; i++) std::cout << (int)reinterpret_cast<unsigned char*>(data_char)[i]<<std::endl;

	// lz77::compress_t compress;
	// std::string compressed = compress.feed(data);


	// // save to file
	// std::ofstream wr;
	// wr.open ("data_compress.dat", std::ios::out | std::ios::binary);
	// wr << compressed;
	// wr.close();


	// std::ifstream in3("data_compress.dat", std::ios::in | std::ios::binary);
	// std::string data;
	// in3.seekg(0, std::ios::end);
	// data.resize(in3.tellg());
	// in3.seekg(0, std::ios::beg);
	// in3.read(&data[0], data.size());
	// in3.close();

  return 0;
}
