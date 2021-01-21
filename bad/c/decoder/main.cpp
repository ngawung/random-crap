#include "gif_lib.h"
#include <iostream>

int main() {

	int ErrCode;
	GifFileType * gif = DGifOpenFileName("out.gif", &ErrCode);
	if (gif == NULL) {
		std::cout << "failed to open" << std::endl;
		return false;
	}

	if (DGifSlurp(gif) != GIF_OK) {
		std::cout << "failed to slurp" << std::endl;
		return false;
	}

	std::cout << gif->SWidth << ":" << gif->SHeight << std::endl;

	return 0;
}