const fs = require("fs");
const decodeGif = require("decode-gif");
const write = require('write');
 
var gif = decodeGif(fs.readFileSync("out.gif"));
console.log(gif.frames.length);
// write.sync('foo.json', gif.frames[0].data.toString().split(",255").toString().replace(/,,/g, "\n"), { newline: false, overwrite: true }); 
