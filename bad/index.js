const fs = require("fs");
const omg = require("omggif");
const gify = require("gify-parse");
const rgb2hex = require("rgb-hex");

const write = require("write");

function chunkArray(myArray, chunk_size){
    var index = 0;
    var arrayLength = myArray.length;
    var tempArray = [];
    
    for (index = 0; index < arrayLength; index += chunk_size) {
        myChunk = myArray.slice(index, index+chunk_size);
        // Do something if you want with the group
        tempArray.push(myChunk);
    }

    return tempArray;
}


const gif_buffer = fs.readFileSync("out.gif");

let gif_info = gify.getInfo(gif_buffer);
const gif_pal = gif_info.globalPaletteColorsRGB.map(x => {
	return rgb2hex(x.r, x.g, x.b);
});

gif_info = null;

var gifData = new omg.GifReader(gif_buffer);

const stream = fs.createWriteStream("data_raw.dat", {flags: "a"});


const num_pixels = gifData.width * gifData.height;
let current, buffer, newBlit, ca

for (let i=0; i<gifData.numFrames(); i++) {
	current = gifData.frameInfo(i);

	buffer = new Uint8Array(num_pixels * 4);
	gifData.decodeAndBlitFrameRGBA(i, buffer)

	newBlit = new Uint8Array(num_pixels);

	ca = chunkArray(buffer, 4);

	console.log(i, gifData.numFrames());

	for (let k=0; k<ca.length; k++) {
		let rgb = rgb2hex(ca[k][0], ca[k][1], ca[k][2]);
		let index = gif_pal.indexOf(rgb);
		if (index == -1) console.log(rgb);
		newBlit[k] = index;
	}

	stream.write(newBlit);
	break;
}

stream.end();