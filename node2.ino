//include required libraries
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DHT.h>
#include "actuator.h"
#include "telemetry.h"
#include "network.h"
#include "rpc.h"

#include "config.h"
#include "SensorManager.h"

static char sharedBuf[200];

//create object of type ethernet pubsubclient
static EthernetClient ethClient;
static PubSubClient mqttClient(ethClient);

unsigned long lastTelemetry =0;

static SensorManager sensors;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Node 2 is booting...");
  // put your setup code here, to run once:
   // initilase sensor 
   sensor_begin();
   sensor_init(&sensors);
   //initialise actutors
   actuators_begin();
   // coonect board to internet and mqtt
  telemetry_init(sharedBuf, sizeof(sharedBuf));
  rpc_init(&mqttClient,sharedBuf, sizeof(sharedBuf));

  // coonect board to internet and mqtt
  network_begin(&mqttClient,NULL);
}


void loop() 
{
  // put your main code here, to run repeatedly:
  //keep checking if board is connected to things board
  network_maintain();

  //read data from sensors
  SensorData data;
  sensor_read(&data, &sensors);//humidity,temp,ldr,motion status,door status
  
  //if humidity is more than 85 if relay is off
  if((int)data.humidity >=HUMIDITY_CRIT && !actuators_getRelayState())
  {
    actuators_setRelay(1);
  }

  //publish to cloud
  //check if network available then push data to things board
  if(network_isConnected())
  {  unsigned long now =millis();
    //publish data to things board for every 5s
    if(now-lastTelemetry>=TELEMETRY_INTERVAL) //if 5sec over
    {
      lastTelemetry=now;
      telemetry_publishTelemetry( &data ,actuators_getRelayState()); //converting sensor data into jaon format and publish
    }
  }

  actuators_updateStatusLEDs(network_isConnected(), data.sensorError);
}
