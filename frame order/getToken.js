require('dotenv').config();

const userToken = process.env.USER_TOKEN;
const appId = process.env.APPID;

const axios = require('axios').default;

const FB = axios.create({
	baseURL: 'https://graph.facebook.com/v8.0/',
	timeout: 5000,
});

(async () => {
	try {
		console.log("get page access token");
		const res = await FB.get(`/${appId}/?fields=access_token&access_token=${userToken}`);


		console.log(res.data);
	} catch(e) {
		console.log (e);
	}


})();