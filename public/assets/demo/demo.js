

var dataChartTemp = new Array();
var dataChartCahaya = new Array();
var dataChartLamp = new Array();
var dataGetTemp,dataGetCahaya,dataGetLamp ;
//var mqtt = require('mqtt')
var client = mqtt.connect('ws://x2.hcm-lab.id:9001')

client.on('connect', function () {
    client.subscribe("/sensor/temp", {
        qos: 1
    });

    client.subscribe("/sensor/cahaya", {
      qos: 1
    });
    client.subscribe("/aktuator/fuzzylamp", {
      qos: 1
    });


    console.log("Client Has subscribe to MQTT broker")
    // demo.initChartsPages()
});


client.on('message', function (topic, message) {
    if(topic === '/sensor/temp'){
      document.getElementById("temperature-val").innerHTML = message.toString() +" Farenheit";
      dataGetTemp = message.toString();

    }
    if(topic === '/sensor/cahaya'){
      document.getElementById("cahaya-val").innerHTML = message.toString() + " Lumens";
      dataGetCahaya = message.toString();
      // demo.initChartsPages();

    }
    if(topic === '/aktuator/fuzzylamp'){
      document.getElementById("fuzzy-val").innerHTML = message.toString();
      dataGetLamp = message.toString();
      // demo.initChartsPages(); 
      pushArray(dataGetTemp,dataGetCahaya,dataGetLamp)

    }


});


function pushArray(dataTemp,dataCahaya,dataLamp){
  dataChartTemp.push(dataTemp)
  dataChartCahaya.push(dataCahaya)
  dataChartLamp.push(dataLamp)

  if(dataChartTemp.length >=21){
    dataChartTemp.shift()
  }
  if(dataChartCahaya.length >=21){
    dataChartCahaya.shift()
  }
  if(dataChartLamp.length >=21){
    dataChartLamp.shift()
  }
  myChart.update();
}


function chartData() {

    
    chartColor = "#FFFFFF";

    ctx = document.getElementById('chartSensor').getContext("2d");

    myChart = new Chart(ctx, {
      type: 'line',

      data: {
        labels: [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'Now'],
        datasets: [{
            borderColor: "#6bd098",
            backgroundColor : "rgba(107, 208, 152,0.1)",
            pointRadius: 0,
            pointHoverRadius: 0,
            borderWidth: 3,
            data: dataChartCahaya
          },
          {
            borderColor: "#f17e5d",
            backgroundColor : "rgba(241, 126, 93,0.1)",
            pointRadius: 0,
            pointHoverRadius: 0,
            borderWidth: 3,
            data: dataChartLamp
          },
          {
            borderColor: "#fcc468",
            backgroundColor : "rgba(252, 196, 104,0.1)",
            pointRadius: 0,
            pointHoverRadius: 0,
            borderWidth: 3,
            data: dataChartTemp
          }
        ]
      },
      options: {
        animation :{
          duration : 0.1,
        },
        legend: {
          display: false
        },

        tooltips: {
          enabled: false
        },

        scales: {
          yAxes: [{

            ticks: {
              fontColor: "#9f9f9f",
              beginAtZero: false,
              maxTicksLimit: 5,
              //padding: 20
            },
            gridLines: {
              drawBorder: false,
              zeroLineColor: "#ccc",
              color: 'rgba(255,255,255,0.05)'
            }

          }],

          xAxes: [{
            barPercentage: 1.6,
            gridLines: {
              drawBorder: false,
              color: 'rgba(255,255,255,0.1)',
              zeroLineColor: "transparent",
              display: false,
            },
            ticks: {
              padding: 20,
              fontColor: "#9f9f9f"
            }
          }]
        },
      }
    });
  }
