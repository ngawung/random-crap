#include <iostream>
#include <fstream>
#include "lz77.h"

int main() {

    lz77::compress_t compress;

    std::ifstream in("data", std::ios::in | std::ios::binary);
    std::ofstream in2("compressed", std::ios::out | std::ios::binary);

    std::string data;
    data.resize(256*192);

    in.seekg(0, std::ios::beg);

    int frame = 0;
    uint16_t blockSize;

    while (!in.eof()) {
        in.read(&data[0], data.size());
        std::string out = compress.feed(data);
        blockSize = out.size();
        
        in2.write(reinterpret_cast<const char*>(&blockSize), sizeof(blockSize));
        in2.write(out.c_str(), blockSize);
        
        frame++;
        std::cout << frame << std::endl;
    }

    in.close();
    in2.close();

    return 0;
}