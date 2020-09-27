const fs = require('fs');
const { Client, Location } = require('whatsapp-web.js');
const qrcode = require('qrcode-terminal');

const groupId = "6289636991298-1539868649@g.us"

const SESSION_FILE_PATH = './session.json';
let sessionCfg;
if (fs.existsSync(SESSION_FILE_PATH)) {
    sessionCfg = require(SESSION_FILE_PATH);
}

const client = new Client({ puppeteer: { headless: true }, session: sessionCfg });
// You can use an existing session and avoid scanning a QR code by adding a "session" object to the client options.
// This object must include WABrowserId, WASecretBundle, WAToken1 and WAToken2.

client.initialize();

client.on('qr', (qr) => {
    // NOTE: This event will not be fired if a session is specified.
    console.log('QR RECEIVED');
    qrcode.generate(qr, {small: true});
});

client.on('authenticated', (session) => {
    console.log('AUTHENTICATED');
    sessionCfg=session;
    fs.writeFile(SESSION_FILE_PATH, JSON.stringify(session), function (err) {
        if (err) {
            console.error(err);
        }
    });
});

client.on('auth_failure', msg => {
    // Fired if session restore was unsuccessfull
    console.error('AUTHENTICATION FAILURE', msg);
});

client.on('ready', () => {
    console.log('READY');
    client.sendMessage(groupId, "Masok...")
});

client.on('message', async msg => {
    if (msg.body == '!info') {
        msg.getChat().then(data => {
            if (data.isGroup) {
                data.sendMessage(`Nama: ${data.name}\nId: ${data.id}`)
            }
        })
    }
})

client.on('message_create', (msg) => {
    if (msg.fromMe) {
        if (msg.body == '!info') {
            msg.getChat().then(data => {
                if (data.isGroup) {
                    console.log(data)
                    data.sendMessage(`Nama: ${data.name}\nId: ${data.id.user}`)

                }
            })
        }
    }
});

client.on('group_join', async (notification) => {
    console.log('join', notification);
    console.log(notification)
    const chat = await notification.getChat()

    if (chat.isGroup && chat.id._serialized == groupId) {
        notification.reply()
    }
});