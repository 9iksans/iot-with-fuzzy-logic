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

app.use("/web",express.static(path.join(__dirname,'/public/')))


app.listen(port, () => console.log(`Example app listening on port ${port}!`))