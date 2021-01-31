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
const gif_pal = new Map();
gif_info.globalPaletteColorsRGB.map((x, index) => {
	gif_pal.set(`${x.r}:${x.g}:${x.b}`, index);
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

	var index = 0;
	var indexed_num = 0;
    var arrayLength = buffer.length;
    var chunk_size = 4;
    
    for (index = 0; index < arrayLength; index += chunk_size) {
        myChunk = buffer.slice(index, index+chunk_size);
        // Do something if you want with the group
        if (!gif_pal.has(`${myChunk[0]}:${myChunk[1]}:${myChunk[2]}`)) throw `pal not found ${myChunk[0]}:${myChunk[1]}:${myChunk[2]}`;
        let indexed = gif_pal.get(`${myChunk[0]}:${myChunk[1]}:${myChunk[2]}`)
		newBlit[indexed_num] = indexed;
		indexed_num++;
    }

	console.log(i, gifData.numFrames());

	stream.write(newBlit);
}

stream.end();