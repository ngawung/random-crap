#include <iostream>
#include <fstream>
#include "lz77.h"

int main() {

    std::ifstream in("test", std::ios::in | std::ios::binary);

    std::string inp;
    std::string data;
    in.seekg(0, std::ios::end);
    data.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&data[0], data.size());
    in.close();

    // inp.swap(data);

    lz77::compress_t compress;
    std::string out = compress.feed(data);

    std::cout << "Compressed size:   " << out.size() << std::endl;
    std::cout << "Uncompressed size: " << data.size() << std::endl;

    lz77::decompress_t decompress;

    std::string extra;

    if (!decompress.feed(out, extra) || extra.size() > 0) {
        std::cout << "Sanity error: failed to decompress whole buffer." << std::endl;
        return 1;
    }

    std::cout << decompress.result() << std::endl;

    std::ofstream in2("compressed", std::ios::out | std::ios::binary);
    in2.write(out.c_str(), out.size());
    in2.close();

    return 0;
}