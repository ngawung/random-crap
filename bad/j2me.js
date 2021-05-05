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

//// BLIT TO RGBA ////

var writeStream = fs.createWriteStream('data');

for (let i=0; i<gifData.numFrames(); i++) {
	current = gifData.frameInfo(i);

	buffer = new Uint8Array(num_pixels * 4)
	formated_buffer = Buffer.alloc(num_pixels)

	gifData.decodeAndBlitFrameRGBA(i, buffer)

	for (let i=0; i<num_pixels; i++) {
		const pal_name = `${buffer[4*i]},${buffer[4*i+1]},${buffer[4*i+2]},${buffer[4*i]+3}`
		if (gif_pal_array.indexOf(pal_name) == -1) gif_pal_array.push(pal_name);

		formated_buffer[i] = gif_pal_array.indexOf(pal_name);
	}

	writeStream.write(formated_buffer);
	console.log("blit to RGBA", i+1, gifData.numFrames());

}

writeStream.close();
console.log(gif_pal_array)

// // get palette with map
// const gif_pal = new Map();


// finalBlit.forEach(blit => {
//     for(let i=0; i<blit.length; i++) {
//         gif_pal.set(blit[i], "random value");
//     }
// })

// // convert map to array
// for (const [key, value] of gif_pal.entries()) {
//     gif_pal_array.push(key);
// }

// console.log(gif_pal_array);

// // format finalBlit

// finalBlit = finalBlit.map(blit => {
//     let temp = []
//     for(let i=0; i<blit.length; i++) {
//         temp.push(gif_pal_array.indexOf(blit[i]));
//     }

//     return temp;
// })

// var writeStream = fs.createWriteStream('data');

// finalBlit.forEach(blit => {
// 	let b = Buffer.alloc(blit.length);
// 	for(let i=0; i<blit.length; i++) {
//         b[i] = blit[i];
//     }
// 	writeStream.write(b)
// })

// writeStream.close();