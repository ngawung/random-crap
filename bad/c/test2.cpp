#include "lz77.h" // header dari sini https://github.com/ivan-tkatchev/yalz77
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {

	int length = 1024;

	std::ifstream in("data_compress.dat", std::ios::in | std::ios::binary);
	unsigned char * buffer = new unsigned char[length]();

	int lastCount = 0;
	int count = 0;

	std::stringstream ss;
	std::string str;

	lz77::decompress_t decompress;

	while(!in.eof()) {
		in.read((char*)buffer, length);
	    std::streamsize s=in.gcount();
	    if (s == 0) break;

	    for (int i=0; i<length; i++) {
	    	if (buffer[i] == '\x00' && buffer[i+1] == '\x44' && buffer[i+2] == '\x00') {
	    		// if (count == 5) break;


	    		ss.seekg(0, std::ios::end);
	    		int size = ss.tellg();
	    		ss.seekg(0, std::ios::beg);
	    		ss.str().swap(str);
	    		str.resize(size);

	    		std::cout<<std::endl<<count<< "size "<<sizeof(str)<<std::endl;

	    		std::string sss;
	    		decompress.feed(ss.str(), sss);
	    		const std::string&  res = decompress.result();

	    		// // sss.seekg(0, std::ios::end);
	    		std::cout<<std::endl<<count<< "size "<<res.size()<<std::endl;


	    		// current.clear();
	    	} else {
	    		count++;
	    		ss << buffer[i];
	    		// current.push_back(buffer[i]);
	    	}
	    }
	    // std::cout<<"yet,";
	}

	// std::cout<<"size "<<current.size()<<std::endl;

	return 0;
}