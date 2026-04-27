//include required libraries
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DHT.h>

#include "config.h"
#include "SensorManager.h"
#include "actuator.h"
#include "network.h"
#include "telemetry.h"
#include "rpc.h"

static char sharedBuf[200];

//create object of ethernet and pubsubclient
static EthernetClient ethClient;
static PubSubClient mqttClient(ethClient);

unsigned long lastTelemetry=0;
void setup()
{
  Serial.begin(9600);
  delay(1000);

  Serial.println("Node1 is booting...");

  sensor_begin();
  Serial.println("Sensors initialized");

  actuators_begin();
  Serial.println("Actuators initialized");

  telemetry_init(sharedBuf, sizeof(sharedBuf));
  Serial.println("Telemetry ready");
  rpc_init(&mqttClient,sharedBuf, sizeof(sharedBuf));

  // upon reciving the data which function needs to be called back
  mqttClient.setCallback(rpc_mqttCallback);
  //coonect board to internet and mqtt
  network_begin(&mqttClient);
  Serial.println("Network initialized");
  mqttClient.setCallback(rpc_mqttCallback);
}

void loop() {
  // put your main code here, to run repeatedly:
  //keep checking if board is connected to things board
  network_maintain();

  //read data from sensors
  SensorData data;
  sensors_read(&data);//humidity,temp,lm35,vibration,sensor error,machine_status
  
  //publish to cloud
  //check if network available then push data to things board
  if(network_isConnected())
  {  unsigned long now =millis();
    //publish data to things board for every 5s
    if(now-lastTelemetry>=TELEMETRY_INTERVAL) //if 5sec over
    {
      lastTelemetry=now;
      telemetry_publishTelemetry( &data ,actuators_getRelayState); //converting sensor data into jaon format and publish
    }
  }

  actuators_updateStatusLEDs(network_isConnected(), data.sensorError);
}


