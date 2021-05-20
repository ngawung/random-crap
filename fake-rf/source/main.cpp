#include <nds.h>
#include <filesystem.h>
#include <iostream>
#include <fstream>
#include "lz77.h"
#include "pallete.hpp"
#include <maxmod9.h>

FILE* file = 0;
bool shouldDraw;
bool queueAvaible;
std::string currentQueue;
const char*  nextQueue;
int frameInQueue = 0;
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

		if (queueAvaible) {
			queueAvaible = false;

			// for (int x=0; x<256; x++) {
			// 	for (int y=0; y<192; y++) {
			// 		VRAM_A[x+y*256] = pallete[(int)nextQueue[x+y*256]];
			// 	}
			// }

			dmaCopyWordsAsynch(3, nextQueue, VRAM_A, 256*192*2);

			std::cout << "draw" << std::endl;
		} else {
			std::cout << "no queue" << std::endl;
		}

		
	}
}

void TimerTick() {
	shouldDraw = true;
}

int main(void) {
	consoleDemoInit();

	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);

	if(nitroFSInit(NULL)) {
		chdir("nitro:/");
		std::cout << "nitrofs init success" << std::endl;
	} else {
		std::cout << "cannot init nitrofs" << std::endl;
	}

	mmInitDefault((char*)"soundbank.bin");
	// mmLoadEffect(0);
	// mmEffect(0);
	
	std::ifstream in("compressed", std::ios::in | std::ios::binary);
	uint16_t blockSize;
	std::string data;
	in.seekg(0, std::ios::beg);
	

	std::cout << currentQueue.size() << std::endl;

	mm_stream mystream;
	mystream.sampling_rate	= 22050;					// sampling rate = 25khz
	mystream.buffer_length	= 1200;						// buffer length = 1200 samples
	mystream.callback		= on_stream_request;		// set callback function
	mystream.format			= MM_STREAM_16BIT_MONO;		// format = stereo 16-bit
	mystream.timer			= MM_TIMER0;				// use hardware timer 0
	mystream.manual			= true;						// use manual filling
	file = fopen("bad.raw","rb");
	mmStreamOpen( &mystream );
	mmStreamUpdate(); mmStreamUpdate();

	irqSet(IRQ_VBLANK, VBlankProc);
	timerStart(2, ClockDivider_1024, TIMER_FREQ_1024(30), TimerTick);
	
	while(true) {

		// update stream
		mmStreamUpdate();

		if (!in.eof() && !queueAvaible) {
			std::cout << "start queue" << std::endl;
			in.read((char*)&blockSize, sizeof(blockSize));
			data.resize(blockSize);
			in.read(&data[0], blockSize);

			lz77::decompress_t decompress;
			std::string extra;
			decompress.feed(data, extra);
			nextQueue = decompress.result().data();
			queueAvaible = true;
			std::cout << "queue avaible" << std::endl;
		}

		swiWaitForVBlank();

	}

	return 0;
}
