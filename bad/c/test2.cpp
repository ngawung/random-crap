#include "lz77.h" // header dari sini https://github.com/ivan-tkatchev/yalz77
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

bool getNewBuffer(std::ifstream* op, char* buffer, int buffer_size) {
	if (op->eof()) return false;

	op->read(buffer, buffer_size);
	std::streamsize s=op->gcount();
    if (s == 0) return false;
    else return true;
}

int main() {

	lz77::decompress_t decompress;
	std::ifstream op;

	std::vector<unsigned char> separator{0x00, 0x24, 0x00};
	std::vector<unsigned char> eof{0x00, 0x22, 0x00};

	int buffer_size = 128;
	int count = 0;

	int lastIndex = 0;
	std::vector<unsigned char> lastBuffer;
	std::string tempData("");

	op.open("data_compress.dat", std::ios::in | std::ios::binary);
	std::vector<unsigned char> buffer(buffer_size, 0);

	while(true) {

		if (lastBuffer.size() == 0) {
			getNewBuffer(&op, (char*)&buffer[0], buffer.size());
			lastBuffer = buffer;
		}

		if (tempData.length() == 0) {
			bool isSeparatorFound = false;

			for (int i=lastIndex; i<lastBuffer.size(); i++) {
				tempData.push_back(lastBuffer[i]);

				if (lastBuffer[i] == '\x00' && lastBuffer[i-1] == '\x24' && lastBuffer[i-2] == '\x00') {
					count++;
					std::cout<<"separator "<<count<<std::endl;
					lastIndex = 0;
					lastBuffer.erase(lastBuffer.begin(), lastBuffer.begin() + i);
					isSeparatorFound = true;
					break;
				} else if (lastBuffer[i] == '\x00' && lastBuffer[i-1] == '\x24' && lastBuffer[i-2] == '\x00') {
					std::cout<<"eof"<<std::endl;
					break;
				}

				lastIndex = i;
			}

			if (!isSeparatorFound) {
				getNewBuffer(&op, (char*)&buffer[0], buffer.size());
				lastBuffer.insert(lastBuffer.end(), buffer.begin(), buffer.end());
				lastIndex++;
				continue;
			}
		}

		tempData.pop_back();
		tempData.pop_back();
		tempData.pop_back();

		std::string temp2;
    	decompress.feed(tempData, temp2);
    	const std::string& result = decompress.result();

    	tempData = "";

    	if (result.length() != 256*192) {
    		std::cout<<"length "<<result.length()<<std::endl;
    		// return 0;
    	}

	}

	return 0;
}