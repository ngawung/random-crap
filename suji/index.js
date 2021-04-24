const wget = require('wget-improved');
const src = 'https://suji.jp/rff/dat/src/';
const types = ["png", "gif", "jpg", "jpeg"]

function download(src, output) {
	return new Promise((resolve, reject) => {
		let download = wget.download(src, output);

		download.on('error', function(err) {
		    reject(err);
		});
		download.on('end', function(output) {
		    resolve(output);
		});
	});
}

(async () => {

	let number = 1805;
	let missing = []

	while(number > 0) {

		console.log(`===={ ${number} }====`)

		for (let i=0; i<types.length; i++) {

			try {
				await download(`${src}RFF${pad_with_zeroes(number, 4)}.${types[i]}`, `./tmp/${number}.${types[i]}`);
				console.log(`${types[i]} SUCCESS`)
				break;
			} catch(e) {
				console.log(`${types[i]} FAILED`)

				if (i == types.length - 1) {
					console.log(`>>> MISSING <<<`);
					missing.push(number);
				}
				
			}
		}

		number--;
		

	}

	console.log("done");
	console.log("missing")
	console.log(missing.join(", "))
	
})();

function pad_with_zeroes(number, length) {

    var my_string = '' + number;
    while (my_string.length < length) {
        my_string = '0' + my_string;
    }

    return my_string;

}