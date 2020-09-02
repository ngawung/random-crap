const io = require('socket.io-client')

for (var i=0; i<1000; i++) {
    connect(i)
}

function connect(i) {
    var client = io("https://socketio-chat-h9jt.herokuapp.com/", {forceNew: true});

    client.on('connect', function() {
        console.log("(+) " + i)
        client.emit("add user", "client " + i)
    });

    client.on('disconnect', () => {
        console.log("(-) " + i)
      });
}