#include <nds.h>
#include <filesystem.h>
#include <iostream>
#include <fstream>
#include "lz77.h"
#include "pallete.hpp"
#include <maxmod9.h>

FILE* file = 0;
bool shouldDraw;
bool requestQueue = false;
bool requestDone = false;
std::string currentQueue;
std::string nextQueue;
int currentFrame = 0;

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

void VBlankProc() {
	if (shouldDraw) {
		shouldDraw = false;

		// const char* cstr = currentQueue.c_str();

		// for (int x=0; x<256; x++) {
		// 	for (int y=0; y<192; y++) {
		// 		u16 pal = pallete[(int)cstr[x+y*256]];
		// 		if (pal != ARGB16(0,0,0,0)) dmaCopyWordsAsynch(2, &pal, VRAM_A + x+y*256, sizeof(pal));
		// 	}
		// }

		dmaCopyWordsAsynch(2, currentQueue.c_str(), VRAM_A, sizeof(currentQueue));
		std::cout << "copy" << std::endl;

		if (!requestDone) std::cout << "kosong" << std::endl;
		currentQueue = nextQueue;
		requestDone = false;
		requestQueue = true;
	}
}

void TimerTick() {
	shouldDraw = true;
}

int main(void) {
	consoleDemoInit();

	videoSetMode(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG);

	int bg = bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	bgUpdate();

	if(nitroFSInit(NULL)) {
		chdir("nitro:/");
		std::cout << "nitrofs init success" << std::endl;
	} else {
		std::cout << "cannot init nitrofs" << std::endl;
	}

	mmInitDefault((char*)"soundbank.bin");
	// mmLoadEffect(0);
	// mmEffect(0);

	lz77::decompress_t decompress;
	std::string extra;
	
	std::ifstream in("compressed", std::ios::in | std::ios::binary);
	uint16_t blockSize;
	std::string data;
	in.seekg(0, std::ios::beg);
	in.read((char*)&blockSize, sizeof(blockSize));
	data.resize(blockSize);
	in.read(&data[0], blockSize);

	decompress.feed(data, extra);
	currentQueue = decompress.result();

	u16* ptr = bgGetGfxPtr(bg);

	for (int x=0; x<256; x++) {
		for (int y=0; y<192; y++) {
			*(ptr+x+y*256) = pallete[(int)currentQueue.data()[x+y*256]];
		}
	}

	// in.read((char*)&blockSize, sizeof(blockSize));
	// data.resize(blockSize);
	// in.read(&data[0], blockSize);

	// decompress.feed(data, extra);
	// nextQueue = decompress.result();

	std::cout << currentQueue.size() << std::endl;

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

	while(true) {
		// uint8_t frameData[256*192*2];
		// for (int x=0; x<256; x++) {
		// 	for (int y=0; y<192; y++) {
		// 		*(VRAM_A+x+y*256) = (currentQueue.c_str()[x+y*256*2]) | (currentQueue.c_str()[x+y*256*2+1]<<8);
		// 	}
		// }

		// if (!in.eof()) {
		// 	in.read((char*)&blockSize, sizeof(blockSize));
		// 	data.resize(blockSize);
		// 	in.read(&data[0], blockSize);

		// 	decompress.feed(data, extra);
		// 	currentQueue = decompress.result();
		// 	std::cout << currentQueue.size();

		// 	for (int x=0; x<256; x++) {
		// 		for (int y=0; y<192; y++) {
		// 			*(VRAM_A+x+y*256) = (currentQueue.data()[x+y*256*2]) | (currentQueue.data()[x+y*256*2+1]<<8);
		// 		}
		// 	}

			// dmaCopyHalfWordsAsynch(3, currentQueue.data(), VRAM_A, sizeof(currentQueue));
		// }

		swiWaitForVBlank();
	}

	irqSet(IRQ_VBLANK, VBlankProc);
	timerStart(1, ClockDivider_1024, TIMER_FREQ_1024(30), TimerTick);
	
	while(true) {
		// update stream
		mmStreamUpdate();
		// std::cout << "loop" << std::endl;
		if (requestQueue) {
			std::cout << "read" << std::endl;
			in.read((char*)&blockSize, sizeof(blockSize));
			data.resize(blockSize);
			in.read(&data[0], blockSize);

			decompress.feed(data, extra);
			nextQueue = decompress.result();
			std::cout << "done" << std::endl;
			requestQueue = false;
			requestDone = true;
		}
	}

	return 0;
}
