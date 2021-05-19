#include <nds.h>
#include <filesystem.h>
#include <iostream>
#include <fstream>
#include "lz77.h"
#include "pallete.hpp"
#include <maxmod9.h>

FILE* file = 0;

mm_word on_stream_request( mm_word length, mm_addr dest, mm_stream_formats format ) {
	if(file){
		size_t samplesize = 1;
		switch(format){
			case MM_STREAM_8BIT_MONO: samplesize = 1; break;
			case MM_STREAM_8BIT_STEREO: samplesize = 2; break;
			case MM_STREAM_16BIT_MONO: samplesize = 2; break;
			case MM_STREAM_16BIT_STEREO: samplesize = 4; break;
		}
	
		int res = fread(dest,samplesize,length,file);
		if(res){
			length = res;
		} else {
			mmStreamClose();
			fclose(file);
			length = 0;
		}
	}
	return length;
}

int main(void) {
	consoleDemoInit();

	videoSetMode(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG);

	if(nitroFSInit(NULL)) {
		chdir("nitro:/");
		std::cout << "nitrofs init success" << std::endl;
	} else {
		std::cout << "cannot init nitrofs" << std::endl;
	}

	mmInitDefault((char*)"soundbank.bin");
	// mmLoadEffect(0);
	// mmEffect(0);

	mm_stream mystream;
	mystream.sampling_rate	= 22050;					// sampling rate = 25khz
	mystream.buffer_length	= 1024;						// buffer length = 1200 samples
	mystream.callback		= on_stream_request;		// set callback function
	mystream.format			= MM_STREAM_16BIT_MONO;	// format = stereo 16-bit
	mystream.timer			= MM_TIMER0;				// use hardware timer 0
	mystream.manual			= true;						// use manual filling
	file = fopen("bad.raw","rb");
	mmStreamOpen( &mystream );
	mmStreamUpdate(); mmStreamUpdate();

	
	int bg = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	u16* videMemoryMain = bgGetGfxPtr(bg);

	lz77::decompress_t decompress;
	std::string extra;
	
	std::ifstream in("compressed", std::ios::in | std::ios::binary);
	std::string data;
	uint16_t blockSize;
	in.seekg(0, std::ios::beg);
	
	
	int delay = 0;
	int maxDelay = 2;

	while(true) {

		// wait until line 0
		// swiIntrWait( 0, IRQ_VCOUNT);
		
		// update stream
		mmStreamUpdate();

		if (delay >= maxDelay && !in.eof()) {
			delay = 0;

			in.read((char*)&blockSize, sizeof(blockSize));
			data.resize(blockSize);
			in.read(&data[0], blockSize);

			if (!decompress.feed(data, extra) || extra.size() > 0) {
				std::cout << "Sanity error: failed to decompress whole buffer." << std::endl;
			}

			// std::cout << blockSize << std::endl;
			// std::cout << decompress.result().size() << std::endl;

			std::string map = decompress.result();

			for (int x=0; x<256; x++) {
				for (int y=0; y<192; y++) {
					u16 pal = pallete[(int)map.c_str()[x+y*256]];
					if (pal != ARGB16(0,0,0,0)) videMemoryMain[x+y*256] = pal;
				}
			}
		}

		


		swiWaitForVBlank();
		delay++;
	}

	return 0;
}
