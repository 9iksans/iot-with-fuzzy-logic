const express = require('express')
const app = express()
var mqtt = require('mqtt')
const port = 3000
const fs = require("fs")
var path = require('path')
var clientlampu = mqtt.connect('ws://192.168.137.1:9001')

// subpub lampu
clientlampu.on('connect', function(){
    clientlampu.subscribe("/aktuator/lampu",{qos:1});
    console.log("Client Has subscribe to MQTT broker topic /aktuator/lampu ")
});



app.use(express.urlencoded({ extended: true }))

//main
app.get('/', function (req, res) {
    res.sendFile(path.join(__dirname + '/index.html'));
});

// script
app.get('/assets/browserMQTT.js', function (req, res) {
    res.sendFile(path.join(__dirname + '/assets/browserMQTT.js'));
});


//filenode
app.get('/subscribe.js', function (req, res) {
    res.sendFile(path.join(__dirname + '/subscribe.js'));
});

//css
app.get('/assets/main.css', function (req, res) {
    res.sendFile(path.join(__dirname + '/assets/main.css'));
});

app.listen(port, () => console.log(`Example app listening on port ${port}!`))