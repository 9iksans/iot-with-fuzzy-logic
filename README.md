
## IoT simple Project Using MQTT and ESP8266
This is an Assignment to make simple IoT Project from Worksho Teknik Kompilasi Course

## Description
This project purpose is to make some monitoring a Potentiometer and controll LED via website

## Video Documentation
[![IoT Project Workshop Teknik Kompilasi CE 2017](https://i.ytimg.com/vi/GtCJnHdL41Q/hqdefault.jpg)](https://www.youtube.com/watch?v=GtCJnHdL41Q&list=PLXA2ixTftgBN1AUagIgYz1PbGW8RsYSud)

## Tools
  - NodeMCU ESP8266
  - Potentiometer 10k Ohms
  - BreadBoard
  - LED

## Installation

The easiest way to make this project run to your PC is clone this project

```bash
$ git clone https://github.com/9iksans/workshop-teknik-kompilasi2017a-kelompok1.git
```

<b>For the Server</b>

Install NodeJS and Node command line program. 
Run the following command in Terminal:

```bash
$ npm install
```

<b>For the NodeMCU</b>

Add some library to the NodeMCU, it is called "PubSubClient by Nick 'O Larry"
And change the WiFi configurations,
Dont forget the Arduino file, you have to adjust the MQTT server address



## How to use?

<b>For the Server</b>
You have to change the server address of MQTT in subscribe.js and index.html file, 

then you could run your server

```bash
$ node server.js
```

<b>For the NodeMCU</b>

dont forget to upload the arduino program to NodeMCU ESP8266, that is where the potentio and LED connected to.

*Note: The NodeMCU port are written on Arduino file*


## Credits
This project belongs to Team-1 Teknik Kompilasi CE2K17

EEPIS © [Team-1 Teknik Kompilasi CE217](https://github.com/9iksans)
