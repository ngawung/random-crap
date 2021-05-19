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


// load gif file to buffer
const gif_buffer = fs.readFileSync("video/out.gif");

var gifData = new omg.GifReader(gif_buffer);

const num_pixels = gifData.width * gifData.height;
let current, buffer, newBlit, ca

const gif_pal_array = [];

var writeStream = fs.createWriteStream('data');

//// BLIT TO RGBA ////

// for (let i=0; i<gifData.numFrames(); i++) {
// 	current = gifData.frameInfo(i);

// 	buffer = new Uint8Array(num_pixels * 4)
// 	formated_buffer = Buffer.alloc(num_pixels)

// 	gifData.decodeAndBlitFrameRGBA(i, buffer)

// 	for (let i=0; i<num_pixels; i++) {
// 		const pal_name = `${buffer[4*i]},${buffer[4*i+1]},${buffer[4*i+2]},${buffer[4*i+3]}`
// 		if (gif_pal_array.indexOf(pal_name) == -1) gif_pal_array.push(pal_name);

// 		formated_buffer[i] = gif_pal_array.indexOf(pal_name);
// 	}

// 	writeStream.write(formated_buffer);
// 	console.log("blit to RGBA", i+1, gifData.numFrames());

// }


//////// HARDCODED VERSION ///////////

let last_frame;

for (let frame=0; frame<gifData.numFrames(); frame++) {
	current = gifData.frameInfo(frame);

	buffer = new Uint8Array(num_pixels * 4)
	formated_buffer = Buffer.alloc(num_pixels)

	gifData.decodeAndBlitFrameRGBA(frame, buffer)

	for (let i=0; i<num_pixels; i++) {
		// if (buffer[4*i+3] != 255) {
		// 	if (last_frame[4*(i)+3] == 255) {
		// 		buffer[4*i]   = last_frame[4*(i)]
		// 		buffer[4*i+1] = last_frame[4*(i)+1]
		// 		buffer[4*i+2] = last_frame[4*(i)+2]
		// 		buffer[4*i+3] = last_frame[4*(i)+3]
		// 	} else throw "error";
		// }

		const pal_name = `${buffer[4*i]},${buffer[4*i+1]},${buffer[4*i+2]},${buffer[4*i+3]}`
		if (gif_pal_array.indexOf(pal_name) == -1) gif_pal_array.push(pal_name);

		// if (pal_name == '0,0,1,255' || pal_name == '0,0,0,255')
		// 	formated_buffer[i] = 0;

		// else if (pal_name == '109,107,110,255' || pal_name == '254,254,254,255' || pal_name == '255,253,255,255')
		// 	formated_buffer[i] = 1;

		formated_buffer[i] = gif_pal_array.indexOf(pal_name);
		
	}

	writeStream.write(formated_buffer);

	last_frame = buffer;
	console.log("blit to RGBA", frame, gifData.numFrames());
}

writeStream.close();
console.log(gif_pal_array)
console.log(gif_pal_array.length)

var pal_stream = fs.createWriteStream('palette.txt');
pal_stream.write(gif_pal_array.join("\n"));