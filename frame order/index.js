require('dotenv').config();

// ExpressJSexpress.static('public')
const express = require('express');
const app = express();
const port = process.env.PORT || 3000;

app.use('/', express.static('public'));

app.listen(port, () => {
  console.log(`Express app listening at port ${port}`)
})

// Facebook Graph
const pageToken = process.env.PAGE_TOKEN;
const appId = process.env.APPID;

const axios = require('axios').default;
const sleep = require('sleep-async')().Promise;

const FB = axios.create({
	baseURL: 'https://graph.facebook.com/v8.0/',
	timeout: 20000,
});

let currentNumber = 8;
let maxNumber = 548;

(async () => {
	try {

		while (currentNumber <= maxNumber) {

			const str = "" + currentNumber;
			const pad = "000";
			const imageName = pad.substring(0, pad.length - str.length) + str;

			const res = await FB.post(`/108413741072506/photos`, {
				message: `Rune Factory 1 - Opening - Frame ${currentNumber} out of ${maxNumber}`,
				url: `http://139.180.215.74:${port}/rf1/${imageName}.bmp`, 
				access_token: pageToken
			});
			console.log(`[Success] Upload image ${currentNumber}.bmp`);
			currentNumber++;

			await sleep.sleep(360000); //6min
			// await sleep.sleep(1000 * 60); //1min
			
		}

		console.log("done");
        
	} catch(e) {
		console.log(`[Failed] Upload image ${currentNumber}.bmp`);
		console.log(e.stack || e);
	}

})();