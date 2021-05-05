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
const gif_buffer = fs.readFileSync("out.gif");

var gifData = new omg.GifReader(gif_buffer);

const num_pixels = gifData.width * gifData.height;
let current, buffer, newBlit, ca

let finalBlit = []

for (let i=0; i<gifData.numFrames(); i++) {
	current = gifData.frameInfo(i);

	buffer = new Uint8Array(num_pixels * 4);
	gifData.decodeAndBlitFrameRGBA(i, buffer)

	newBlit = [];

	var index = 0;
	var indexed_num = 0;
    var arrayLength = buffer.length;
    var chunk_size = 4;
    
    for (index = 0; index < arrayLength; index += chunk_size) {
        myChunk = buffer.slice(index, index+chunk_size);
        // Do something if you want with the group
        if (myChunk[3] != 255 && i == 0) throw new Error(`${myChunk[0]},${myChunk[1]},${myChunk[2]},${myChunk[3]}`)
		newBlit.push(`${myChunk[0]},${myChunk[1]},${myChunk[2]},${myChunk[3]}`);
		indexed_num++;
    }

    finalBlit.push(newBlit);

	console.log("blit to RGBA", i+1, gifData.numFrames());

}

console.log("remove transparent");

// remove any transparent
for (let i=0; i<finalBlit.length; i++) {
    let temp = [];

    for(let i2=0; i2<finalBlit[i].length; i2++) {
        let rgb = finalBlit[i][i2].split(",");

        // console.log(rgb)

        if (rgb[3] == 0) {
            temp.push(finalBlit[i-1][i2]);
        } else {
            temp.push(finalBlit[i][i2]);
        }

    }

    finalBlit[i] = temp;
}

// get palette with map
const gif_pal = new Map();
const gif_pal_array = [];

finalBlit.forEach(blit => {
    for(let i=0; i<blit.length; i++) {
        gif_pal.set(blit[i], "random value");
    }
})

// convert map to array
for (const [key, value] of gif_pal.entries()) {
    gif_pal_array.push(key);
}

console.log(gif_pal_array);
return;

// format finalBlit

finalBlit = finalBlit.map(blit => {
    let temp = []
    for(let i=0; i<blit.length; i++) {
        temp.push(gif_pal_array.indexOf(blit[i]));
    }

    return temp;
})



// draw

finalBlit.forEach((blit, index) => {
    let final_out = '';
    console.log("frame", index);

    for (i = 0; i < blit.length; i += gifData.width) {
        let chunk = blit.slice(i, i+gifData.width);

        chunk.forEach(x => {
            // final_out += x;
            if (x == 0) final_out += "▓"
            else if (x == 1) final_out += "▒"
            else if (x == 2) final_out += "░"
            else if (x == 3) final_out += "⠀"
            else if (x == 4) final_out += "⠀"
        })

        final_out += "\n"
    }


    console.log(final_out)
})