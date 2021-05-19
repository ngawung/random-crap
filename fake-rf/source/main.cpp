#include <nds.h>
#include <filesystem.h>
#include <iostream>
#include <fstream>
#include "lz77.h"

int main(void) {
	consoleDemoInit();

	videoSetMode(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG);


	if(nitroFSInit(NULL)) {
		chdir("nitro:/");
		std::cout << "success nitrofs" << std::endl;
		
		std::ifstream in("compressed", std::ios::in | std::ios::binary);

		std::string inp;
		std::string data;
		in.seekg(0, std::ios::end);
		data.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&data[0], data.size());
		in.close();

		std::string out;

		// swiDecompressLZSSWram(data.data(), &out);
		// decompress(data.c_str(), &out, LZ77);

		lz77::decompress_t decompress;
		std::string extra;

		if (!decompress.feed(data, extra) || extra.size() > 0) {
			std::cout << "Sanity error: failed to decompress whole buffer." << std::endl;
			return 1;
		}

		std::cout << decompress.result() << std::endl;

	} else {
		std::cout << "failed nitrofs" << std::endl;
	}

	
	int bg = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	u16* videMemoryMain = bgGetGfxPtr(bg);

	for (int x=0; x<256; x++) {
		for (int y=0; y<256; y++) {
			videMemoryMain[x+y*256] = ARGB16(1, 31, 0 ,31);
		}
	}
	
	while(true) swiWaitForVBlank();

	return 0;
}
