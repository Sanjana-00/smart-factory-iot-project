#include "SensorManager.h"
#include <DHT.h>

static DHT dht(PIN_DHT, DHT_TYPE);

static float lastTemp;
static float lastHumidity;

void sensor_init  (SensorManager* sm)
{
  sm->lastTemp= 0.0f;
  sm->lastHumidity= 0.0f;
  sm->motionActive= false;
  sm->motionClearTime = 0;
}

void sensor_begin(void)
{
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_DOOR, INPUT_PULLUP);
  dht.begin();
}




//read sensor of PIR for motion
static bool readPIR(SensorManager* sm)
{
  // read the value from motion sensor , check if it is true for next 10 secs
  const bool pirHigh = (digitalRead(PIN_PIR) == HIGH);
  const unsigned long now = millis();
  if(pirHigh)
  {
    sm->motionActive = true;
    sm->motionClearTime = now + MOTION_CLEAR_MS;
  }
  else if( sm->motionActive && (now >sm->motionClearTime )) 
  {
    sm->motionActive = false;
  }
  return sm->motionActive;
}  



//read door status
static bool readDoor(void)
{
  return (digitalRead(PIN_DOOR) == LOW); // 0 door is open , 1 door is closed
} 
  
  //read ldr sensor-light present in room or not
static uint16_t readLDR(void)
{
  uint16_t sum = 0;
  uint8_t i;
  for(i = 0; i < 4; i++) // read the average of 4 readings
  {
    sum += (uint16_t)analogRead(PIN_LDR); // 0 to 1023
    delay(2); //2ms
  }
  return sum/4; // wear house is dark or not [300 > val -> dark , light is avaliable
}



//read data from sensor,return dht22 status ,return 0 on error
bool sensor_read(SensorData* out,SensorManager* sm)
{
  //read dht22 sensor
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  //if error in DHT sensor
  if( isnan(t) || isnan(h))
 {  
    out->sensorError =1;
    out->temperature = sm->lastTemp;
    out->humidity= sm->lastHumidity;
 }
 else
  {
    out->sensorError = 0;
    out->temperature = round(t * 10.0f) * 0.1f;
    out->humidity = round(h * 10.0f) * 0.1f;
    sm->lastTemp = out->temperature;
    sm->lastHumidity = out->humidity;
  }

//read ldr sensor //read door status //read motion detected
  //read motion detected
  out->motionDetected = readPIR(sm);
  //read door status
  out->doorOpen = readDoor();
  //read ldr sensor
  out->ldrValue = readLDR();
  out->isDark = (out->ldrValue < LDR_DARK_THRESH); //300 > val -> dark , light is avaliable

  return !out->sensorError;

}