const express = require('express')
const app = express()
var mqtt = require('mqtt')
const port = 3000
const fs = require("fs")
var path = require('path')



app.use(express.urlencoded({ extended: true }))

//main
app.get('/', function (req, res) {
    res.sendFile(path.join(__dirname + '/index.html'));
});

// script
app.get('/assets/browserMQTT.js', function (req, res) {
    res.sendFile(path.join(__dirname + '/assets/browserMQTT.js'));
});

app.get('/node_modules/chart.js/dist/Chart.js', function (req, res) {
    res.sendFile(path.join(__dirname + '/node_modules/chart.js/dist/Chart.js'));
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