const fs = require("fs");
const omg = require("omggif");

// load gif file to buffer
const gif_buffer = fs.readFileSync("video/out.gif");

var gifData = new omg.GifReader(gif_buffer);

const num_pixels = gifData.width * gifData.height;
let current, buffer, formated_buffer

const gif_pal_array = [];

var writeStream = fs.createWriteStream('data');


//////// HARDCODED VERSION ///////////

let last_buffer;

let bit_data = 0x0;
let bit_check = 0x1;

let pixel_array = [];
let bit_array = [];
let i, k, r, g, b, a = 0;
let chunk = 8;
let chunk_pixel = 4;

for (let frame=0; frame<gifData.numFrames(); frame++) {
	current = gifData.frameInfo(frame);

	buffer = new Uint8Array(num_pixels * 4)
	gifData.decodeAndBlitFrameRGBA(frame, buffer)
	formated_buffer = Buffer.alloc(num_pixels / chunk)

	// convert to single color
	for (i=0; i<num_pixels; i++) {
		if (buffer[i*4+3] != 255) {
			buffer[i*4]   = last_buffer[i*4]
			buffer[i*4+1] = last_buffer[i*4+1]
			buffer[i*4+2] = last_buffer[i*4+2]
			buffer[i*4+3] = last_buffer[i*4+3]
		}

		r = buffer[i*4]
		g = buffer[i*4+1]
		b = buffer[i*4+2]
		a = buffer[i*4+3]

		const pal_name = `${r},${g},${b},${a}`
		if (gif_pal_array.indexOf(pal_name) == -1) gif_pal_array.push(pal_name);

		// hardcoded pal color
		if (pal_name == '0,0,1,255' || pal_name == '0,0,0,255')
			pixel_array.push(0);

		else if (pal_name == '109,107,110,255' || pal_name == '254,254,254,255' || pal_name == '255,253,255,255')
			pixel_array.push(1);

		else throw "error " + pal_name;
	}


	// convert to bit
	for (i=0; i<num_pixels/8; i++) {
		bit_data = 0x0;

		for (k=0; k<8; k++) {
			if (pixel_array[i*8+k] == 1)
				bit_data = bit_data | (bit_check << k)
		}

		formated_buffer[i] = bit_data;
	}

	writeStream.write(formated_buffer);

	last_buffer = buffer;
	pixel_array = []
	console.log("blit to RGBA", frame, gifData.numFrames());
}


// 	// split frame pixel to chunk part (4 array each)
// 	for (i=0; i<(num_pixels/chunk); i++) {
// 		// temp = array.slice(i, i+chunk);

// 		// loop the chunk_pixel part
// 		for (let k=0; k<chunk; k++) {

// 			// update last_frame
// 			if (buffer[(chunk*i) + (chunk_pixel*k+3)] != 255) {
// 				console.log("test", i, k)
				
// 				buffer[(chunk*i) + (chunk_pixel*k)]   = last_frame[(chunk*i) + (chunk_pixel*k)]
// 				buffer[(chunk*i) + (chunk_pixel*k+1)] = last_frame[(chunk*i) + (chunk_pixel*k+1)]
// 				buffer[(chunk*i) + (chunk_pixel*k+2)] = last_frame[(chunk*i) + (chunk_pixel*k+2)]
// 				buffer[(chunk*i) + (chunk_pixel*k+3)] = last_frame[(chunk*i) + (chunk_pixel*k+3)]
// 			}

// 			r = buffer[(chunk*i) + (chunk_pixel*k)]
// 			g = buffer[(chunk*i) + (chunk_pixel*k+1)]
// 			b = buffer[(chunk*i) + (chunk_pixel*k+2)]
// 			a = buffer[(chunk*i) + (chunk_pixel*k+3)]

// 			// update pallete array
// 			const pal_name = `${r},${g},${b},${a}`
// 			if (gif_pal_array.indexOf(pal_name) == -1) gif_pal_array.push(pal_name);

// 			// hardcoded pal color
			
// 			// no need bit shift.. already 0
// 			// if (pal_name == '0,0,1,255' || pal_name == '0,0,0,255') {
// 			// 	bit_data = bit_data | (bit_check << k)
// 			// }

// 			if (pal_name == '109,107,110,255' || pal_name == '254,254,254,255' || pal_name == '255,253,255,255')
// 				bit_data = bit_data | (bit_check << k)

// 		}

// 		// throw dec2bin(bit_data)

// 		formated_buffer[(chunk*i) / 8] = bit_data;

// 		// reset bit_data
// 		bit_data = 0x0;
		
// 	}

// 	writeStream.write(formated_buffer);

// 	last_frame = buffer;
// 	console.log("blit to RGBA", frame, gifData.numFrames());
// }

// writeStream.close();
// console.log(gif_pal_array)


// function dec2bin(dec) {
//   return (dec >>> 0).toString(2);
// }