#define USE_ARDUINO_INTERRUPTS true 
#include <PulseSensorPlayground.h> 

const int GSR=A2;
float sensorValue;
const int PulseWire = 0;
int Threshold = 500;
float sum=0;
 
PulseSensorPlayground pulseSensor;

void setup(){
  Serial.begin(9600);
  delay(3000);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()) {
  Serial.print(" Heart Rate Monitor");
  }
  
  for(int i=0;i<500;i++)
  {
  sensorValue=analogRead(GSR)*5/1024; //Convert to Voltage Reading [Reading*5/1024]== V.out
  float resistance=(5-sensorValue)/sensorValue; //line for the formula converting out voltage to resistance
  float conductance=1/resistance;//line for converting resistance to conductance
  sum=sum+conductance;
  delay(5);
  }
  float threshold = sum/500; //callibration 
}
  
  

void loop(){
  float temp;
  int condition;
  float sum = 0;
  
  int myBPM = pulseSensor.getBeatsPerMinute(); 
  // "myBPM" hold this BPM value now.
  if (pulseSensor.sawStartOfBeat()) { 
  //Serial.print("BPM: "); 
  //Serial.println(myBPM); 
  }
  
  for(int i=0;i<100;i++)
  {
  sensorValue=analogRead(GSR)*5/1024; //Convert to Voltage Reading [Reading*5/1024]== V.out
  float resistance=(5-sensorValue)/sensorValue; //line for the formula converting out voltage to resistance
  float conductance=1/resistance;//line for converting resistance to conductance
  sum=sum+conductance;
  delay(100);
  }
  float threshold = sum/100; //reading per minute

 
  
  Serial.print("GSR Value=");
  Serial.println(threshold);
  temp = threshold;
 
    // based on literature
  if(abs(temp)<2 && (myBPM >=60 && myBPM <=70)){
    //Serial.println("Emotion Changes Detected! Relaxed");
    condition = 1;
    delay(3000);
  }else if((abs(temp)>2 && abs(temp)<=4) && (myBPM >70 && myBPM <=90) ){
    //Serial.println("Emotion Changes Detected! Calm");
    delay(3000);
    condition = 2;
  }else if((abs(temp)>4 && abs(temp)<=6) && (myBPM >90 && myBPM <=100)){
    //Serial.println("Emotion Changes Detected! Tense");
    delay(3000);
    condition = 3;
  }else if(abs(temp)>6 && (myBPM >100)){
   // Serial.println("Emotion Changes Detected! Stressed");
    delay(3000);
    condition = 4;
  }


if (condition == 1){
//Serial.println("For your on/off task we recommend you to 1");
}else if (condition == 2){
//Serial.println("For your on/off task we recommend you to 2");
}else if (condition == 3){
//Serial.println("For your on/off task we recommend you to 3");
}else if (condition == 4){
//Serial.println("For your on/off task we recommend you to 4");
}


}
