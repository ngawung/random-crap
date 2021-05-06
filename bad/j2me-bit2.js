const fs = require("fs");
const omg = require("omggif");
const gify = require("gify-parse");
const rgb2hex = require("rgb-hex");

const write = require("write");

// load gif file to buffer
const gif_buffer = fs.readFileSync("video/out.gif");

var gifData = new omg.GifReader(gif_buffer);

const num_pixels = gifData.width * gifData.height;
let current, buffer, newBlit, ca

const gif_pal_array = [];

var writeStream = fs.createWriteStream('data');


//////// HARDCODED VERSION ///////////

let last_frame;

let bit_data = 0x0;
let bit_check = 0x1;

let frame = 1254;

current = gifData.frameInfo(frame);


buffer = new Uint8Array(num_pixels * 4)
gifData.decodeAndBlitFrameRGBA(frame, buffer)

let i, r, g, b, a = 0;
let chunk = 32;
let chunk_pixel = 8;

formated_buffer = Buffer.alloc(num_pixels / chunk_pixel)

let counter = 0;

// split frame pixel to chunk part (4 array each)
for (i=0; i<(buffer.length/chunk); i++) {
	// temp = array.slice(i, i+chunk);

	// loop the chunk_pixel part
	for (let k=0; k<chunk_pixel; k++) {

		// update last_frame
		if (buffer[(chunk*i) + (chunk_pixel*k+3)] != 255) {
	// console.log("test", i, k)
			
			// buffer[(chunk*i) + (chunk_pixel*k)]   = last_frame[(chunk*i) + (chunk_pixel*k)]
			// buffer[(chunk*i) + (chunk_pixel*k+1)] = last_frame[(chunk*i) + (chunk_pixel*k+1)]
			// buffer[(chunk*i) + (chunk_pixel*k+2)] = last_frame[(chunk*i) + (chunk_pixel*k+2)]
			// buffer[(chunk*i) + (chunk_pixel*k+3)] = last_frame[(chunk*i) + (chunk_pixel*k+3)]
		
			buffer[(chunk*i) + (chunk_pixel*k)]   = 0
			buffer[(chunk*i) + (chunk_pixel*k+1)] = 0
			buffer[(chunk*i) + (chunk_pixel*k+2)] = 0
			buffer[(chunk*i) + (chunk_pixel*k+3)] = 255

		}

		r = buffer[(chunk*i) + (chunk_pixel*k)]
		g = buffer[(chunk*i) + (chunk_pixel*k+1)]
		b = buffer[(chunk*i) + (chunk_pixel*k+2)]
		a = buffer[(chunk*i) + (chunk_pixel*k+3)]

		// update pallete array
		const pal_name = `${r},${g},${b},${a}`
		if (gif_pal_array.indexOf(pal_name) == -1) gif_pal_array.push(pal_name);

		// hardcoded pal color
		
		// no need bit shift.. already 0
		// if (pal_name == '0,0,1,255' || pal_name == '0,0,0,255') {
		// 	bit_data = bit_data | (bit_check << k)
		// }

		if (pal_name == '109,107,110,255' || pal_name == '254,254,254,255' || pal_name == '255,253,255,255')
			bit_data = bit_data | (bit_check << k)

	}

	console.log(counter, dec2bin(bit_data))
	counter++

	formated_buffer[Math.floor((chunk*i) / chunk_pixel)] = bit_data;

	// reset bit_data
	bit_data = 0x0;
	
}

writeStream.write(formated_buffer);

last_frame = buffer;
console.log("blit to RGBA", frame, gifData.numFrames());


writeStream.close();
console.log(gif_pal_array)


function dec2bin(dec) {
  return (dec >>> 0).toString(2);
}