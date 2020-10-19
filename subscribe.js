var dataChart = new Array();
var dataGet;
//var mqtt = require('mqtt')
var client = mqtt.connect('ws://192.168.137.1:9001')

client.on('connect', function () {
    client.subscribe("/sensor/potensio", {
        qos: 1
    });
    console.log("Client Has subscribe to MQTT broker")
    drawChart();
});


client.on('message', function (topic, message) {

    // console.log(message.toString()); //if toString is not given, the message comes as buffer
    document.getElementById("potensiometer").innerHTML = message.toString();
    dataGet = message.toString();
    drawChart();
});

// setInterval(delayChart, 1000);


function drawChart() {
    for (var i = 0; i < 20; i++) {
        dataChart[i] = dataChart[i + 1];
    }
    dataChart[19] = dataGet;

    var ctx = document.getElementById('myChart').getContext('2d');
    var myChart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'Now'],
            datasets: [{
                label: 'Potensiometer',
                data: dataChart,
                backgroundColor: [
                    'rgba(255, 99, 132, 0.2)'
                ],
                borderColor: [
                    'rgba(255, 99, 132, 1)',
                    'rgba(54, 162, 235, 1)',
                    'rgba(255, 206, 86, 1)',
                    'rgba(75, 192, 192, 1)',
                    'rgba(153, 102, 255, 1)',
                    'rgba(255, 159, 64, 1)'
                ],
                borderWidth: 1
            }]
        },
        options: {
            animation:{
                duration: 0
            },
            scales: {
                yAxes: [{
                    ticks: {
                        min :0 ,
                        max : 1200
                    }
                }]
            }
        }
    });
}