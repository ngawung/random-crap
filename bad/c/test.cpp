#include "lz77.h" // header dari sini https://github.com/ivan-tkatchev/yalz77
#include <iostream>
#include <fstream>

int main() {
 //  // compress
 // std::string input = "";
 //  lz77::compress_t compress;
 //  std::string compressed = compress.feed(input);

 //  // save to file
 //  std::ofstream write;
 //  write.open ("example.bin", std::ios::out | std::ios::binary);
 //  write << compressed;
 //  write.close();

 //  // read
 //  std::ifstream in("example.bin", std::ios::in | std::ios::binary);
 //  std::string data;
	// in.seekg(0, std::ios::end);
	// data.resize(in.tellg());
	// in.seekg(0, std::ios::beg);
	// in.read(&data[0], data.size());
	// in.close();
  
 //  // decompress
 //  lz77::decompress_t decompress;
 //  std::string temp;
 //  decompress.feed(data, temp);

 //  const std::string& uncompressed = decompress.result();
 //  std::cout << uncompressed <<std::endl;

	int list_length = 256*192*3;
	const char arrayNum[8] = {'a','b','c','d','e','f','g','h'};

	

	// for (int i=0; i<list_length; i++) std::cout<<(int)list[i]<<",";

	// std::cout<<"\nlist size "<<sizeof(list)<<std::endl;

	std::ofstream write;
	write.open ("data.dat", std::ios::out | std::ios::binary);
	for (int i=0; i< 150; i++) {
		unsigned char list[list_length];
		for (int i=0; i<list_length; i++) list[i] = arrayNum[rand() % 8];
		write.write((char *) &list, sizeof(list));
	}
	write.close();

	// read
	std::ifstream in("data.dat", std::ios::in | std::ios::binary);
	unsigned char * buffer = new unsigned char[4]();
	std::cout<<"buffer size "<<sizeof(buffer)<<std::endl;
	while(!in.eof()) {
	    in.read((char*)buffer, 4);
	    std::streamsize s=in.gcount();
	 //    if (s == 0) break;
	 //    ///do with buffer
	 //    for(int i = 0 ; i < 4 ; i ++ ) std::cout<<(int)buffer[i]<<",";
		// std::cout<<" done"<<std::endl;
	}
	in.close();

	// read
	std::ifstream in2("data.dat", std::ios::in | std::ios::binary);
	std::string data;
	in2.seekg(0, std::ios::end);
	data.resize(in2.tellg());
	in2.seekg(0, std::ios::beg);
	in2.read(&data[0], data.size());
	in2.close();

	lz77::compress_t compress;
	std::string compressed = compress.feed(data);


	// save to file
	std::ofstream wr;
	wr.open ("data_compress.dat", std::ios::out | std::ios::binary);
	wr << compressed;
	wr.close();



  return 0;
}
