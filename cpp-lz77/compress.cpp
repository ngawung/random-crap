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

    while (!in.eof()) {
        in.read(&data[0], data.size());
        std::string out = compress.feed(data);
        in2.write(out.c_str(), out.size());
        
        frame++;
        std::cout << frame << std::endl;
    }

    in.close();
    in2.close();

    return 0;
}