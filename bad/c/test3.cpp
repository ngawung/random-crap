#include "lz77.h" // header dari sini https://github.com/ivan-tkatchev/yalz77
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

inline unsigned int to_uint(char ch) {
    // EDIT: multi-cast fix as per David Hammen's comment
    return static_cast<unsigned int>(static_cast<unsigned char>(ch));
}

int main() {

	lz77::compress_t compress;
	lz77::decompress_t decompress;

	std::ofstream wr;
	std::ifstream op;

	char data_raw_1[3] = {0, 0, 31};
	char data_raw_2[3] = {2, 2, 2};

	char separator[3] = {'\x00', '\x44', '\x00'};
	char eof[3] = {'\x00', '\x22', '\x00'};

	// save to data_raw.dat
	wr.open("data_raw.dat", std::ios::out | std::ios::binary);
	wr.write(data_raw_1, 3);
	wr.write(data_raw_2, 3);
	wr.close();

	// compress
	wr.open("data_compress.dat", std::ios::out | std::ios::binary);
	op.open("data_raw.dat", std::ios::in | std::ios::binary);
	char * buffer = new char[3]();
	while(!op.eof()) {
		op.read(buffer, 3);
		std::streamsize s=op.gcount();
	    if (s == 0) break;

	    std::string temp("");
		for (int i=0; i<3; i++) temp.push_back(buffer[i]);
		std::string compressed = compress.feed(temp);

		wr << compressed;
		wr.write(separator, 3);
	}
	wr.write(eof, 3);
	wr.close();
	op.close();

	// decompress

	// char example[5] = {3, 7, 0, 0, 31};
	// std::string temp("");
	// std::string tempp;
	// for (int i=0; i<5; i++) temp.push_back(example[i]);
	// decompress.feed(temp, tempp);
	// const std::string& temppp = decompress.result();

	// std::cout << std::hex;
	// for (char ch : temppp) std::cout << "0x" << to_uint(ch) << ' ';
	// std::cout << std::endl;

	op.open("data_compress.dat", std::ios::in | std::ios::binary);
	std::vector<unsigned char> buffer2(2, 0);
	std::string temp3("");
	while(!op.eof()) {
		op.read((char*)&buffer2[0], buffer2.size());
		std::streamsize s=op.gcount();
	    if (s == 0) break;

	    for (int i=0; i<buffer2.size(); i++) {
	    	if (buffer2[i] == '\x00' && buffer2[i+1] == '\x44' && buffer2[i+2] == '\x00') {
	    		std::cout << std::hex;
			    for (char ch : temp3) std::cout << "0x" << to_uint(ch) << ' ';
			    std::cout << std::endl;

	    		std::string temp2;
	    		decompress.feed(temp3, temp2);

	    		const std::string& result = decompress.result();

	    		std::cout << std::hex;
			    for (char ch : result) std::cout << "0x" << to_uint(ch) << ' ';
			    std::cout << std::endl;

				temp3 = "";
				i += 2;
			} else if (buffer2[i] == '\x00' && buffer2[i+1] == '\x22' && buffer2[i+2] == '\x00'){
				std::cout<<"eof"<<std::endl;
	    	} else {
	    		temp3.push_back(buffer2[i]);
	    	}
	    }
	}

	// // log
	// std::cout<<"sizeof "<<sizeof(temp)<<" "<<sizeof(compressed)<<std::endl;
	// std::cout<<"length "<<temp.length()<<" "<<compressed.length()<<std::endl;

	// std::cout << std::hex;
 //    for (char ch : temp) std::cout << "0x" << to_uint(ch) << ' ';
 //    std::cout << std::endl;

	// std::cout << std::hex;
 //    for (char ch : compressed) std::cout << "0x" << to_uint(ch) << ' ';
 //    std::cout << std::endl;

	// std::cout << std::hex;
 //    for (char ch : uncompressed) std::cout << "0x" << to_uint(ch) << ' ';
 //    std::cout << std::endl;

	// std::cout<<std::hex<<temp<<std::endl;
	// std::cout<<std::hex<<compressed<<std::endl;

	return 0;
}