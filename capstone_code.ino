int LEDYellow = 7;        //Low food LED

int LEDRed = 2;           //Food empty LED

int LEDGreen = 8;         //Power enabled

int MotorDriverF = 11; //Motor Driver Forward

int MotorDriverB = 10; //Motor Driver Back

int TimePotA = 3;    // Time set potentiometer, CLK pin

int TimePotB = 4;   //Time set Potentiometer, DT pin

int PortionPotA = 5; //Portion set potentiometer, CLK pin

int PortionPotB = 6; //Portion set potentiometer, DT pin

int ManualPB = 9;   //Manual Dispense Pushbutton

int TriggerPin = 13;  //U.S Sensor, Trigger

int EchoPin = 12;     //U.S Sensor, Echo

int MaxSpd = 127.5 ; //Top speed (0Â­255)

int timer3 =0;

int timer6 = 0;

int timer9 = 0;

int timer =0;

int MotorEnable = 0;

int currentstate=1;
int distance =0;

unsigned long DelayStart = 0; //Time the delay started

int TimePotEncoderPosCount = 0;
int TimePotALast;
int TimePotAValue;

boolean TimePotbCW;

int PortionPotEncoderPosCount = 0;
int PortionPotALast;
int PortionPotAValue;

boolean PortionPotbCW;


void setup() 
{

pinMode(ManualPB, INPUT);
pinMode(TriggerPin, OUTPUT); // Sets the TriggerPin as an OUTPUT
pinMode(EchoPin, INPUT); // Sets the EchoPin as an INPUT
pinMode(TimePotA, INPUT); //CLK Pin
pinMode(TimePotB, INPUT); //DT Pin
pinMode(PortionPotA, INPUT); //CLK Pin
pinMode(PortionPotB, INPUT); //DT Pin


pinMode(LEDYellow, OUTPUT);
pinMode(LEDRed, OUTPUT);
pinMode(LEDGreen, OUTPUT);
pinMode(MotorDriverF, OUTPUT);
pinMode(MotorDriverB, OUTPUT);

TimePotALast = digitalRead(TimePotA);
PortionPotALast = digitalRead(PortionPotA);

Serial.begin(9600); //start serial monitor

}

void loop() 
{

//GREEN LED ON WHEN POWER TO ARDUINO
digitalWrite (LEDGreen, HIGH);
 
//TIMEPOT SETUP 
 TimePotAValue = digitalRead(TimePotA); 
 if (TimePotAValue != TimePotALast){ // Means the knob is rotating
 // if the knob is rotating, we need to determine direction
 // We do that by reading pin B.
 if (digitalRead(TimePotB) != TimePotAValue) { // Means pin A Changed first - We're Rotating Clockwise.
 TimePotEncoderPosCount ++;
  TimePotbCW = true;
  } else {// Otherwise B changed first and we're moving CCW
 TimePotbCW = false;
 TimePotEncoderPosCount--;
 }
 Serial.print ("Rotated: ");
 if (TimePotbCW){
 Serial.println ("clockwise");
 }else{
 Serial.println("counterclockwise");
 }
 Serial.print("Time pot Position: ");
 Serial.println(TimePotEncoderPosCount);

 
 TimePotALast = TimePotAValue;
 }



//TIMEPOT CONTROL
  //3 HR TIMER SET
  digitalRead(TimePotAValue);
  if (TimePotAValue > 10 && TimePotAValue <= 20);
  {
  timer3=!timer3+currentstate ;
   
    if (timer3<=10800000);
   {
 Serial.print(timer3);
   }  
    if  (timer3>=10800000);
    {
    MotorEnable=1;
    timer3=0;
    } 
  }


//HIGH LIMIT RESET
      
if (TimePotAValue >= 40) TimePotAValue =0;

//ULTRASONIC SENSOR SETUP

{
#define EchoPin 2 // attach pin D12 Arduino to pin Echo of HC-SR04
#define TriggerPin 3 //attach pin D13 Arduino to pin Trig of HC-SR04

// Defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

// Clears the TriggerPin condition
digitalWrite(TriggerPin, LOW);
delayMicroseconds(2);
  
// Sets the TriggerPin HIGH (ACTIVE)
digitalWrite(TriggerPin, HIGH);

// Reads the EchoPin, returns the sound wave travel time in microseconds
duration = pulseIn(EchoPin, HIGH);

// Calculating the distance
  
distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
// Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

//LED CONDITIONS, ULTRASONIC SENSOR
 {
if(distance <= 800) digitalWrite (LEDYellow, HIGH); //Low Food LED ON
else (LEDYellow, LOW);  //Low Food LED OFF
if (distance >= 1000) digitalWrite (LEDRed, HIGH); // Empty Food LED ON
else (LEDRed, LOW); // Empty Food LED OFF
}


//MANUAL PUSHBUTTON CONTROL
  {
if (ManualPB, HIGH);
      {     
        Serial.write("Dispensing");
         analogWrite(MotorDriverF,MaxSpd);  //Send instructions to Forward motor pin
    delay(3000);
    analogWrite(MotorDriverF,0);
      }

//PORTIONPOT SETUP

if (digitalRead(LEDGreen) == HIGH);
  
{
  
 PortionPotAValue = digitalRead(PortionPotA); 
 if (PortionPotAValue != PortionPotALast){ // Means the knob is rotating
 // if the knob is rotating, we need to determine direction
 // We do that by reading pin B.
 if (digitalRead(PortionPotB) != PortionPotAValue) { // Means pin A Changed first - We're Rotating Clockwise.
 PortionPotEncoderPosCount ++;
  PortionPotbCW = true;
  } else {// Otherwise B changed first and we're moving CCW
 PortionPotbCW = false;
 PortionPotEncoderPosCount--;
 }
 Serial.print ("Rotated: ");
 if (PortionPotbCW){
 Serial.println ("clockwise");
 }else{
 Serial.println("counterclockwise");
 }
 Serial.print("Portion pot Position: ");
 Serial.println(PortionPotEncoderPosCount);

 }
 PortionPotALast = PortionPotAValue;
} 
      
//PORTION POT CONTROL
    
 if (MotorEnable=1 && LEDGreen, HIGH);     
      {      
 //3 PORTIONS
 if (PortionPotAValue >= 0 && PortionPotAValue <= 10)
 {
    MotorDriverF= 1;
  
     MotorDriverF=0;
 }
      
 
 //6 PORTIONS
 if (PortionPotAValue > 10 && PortionPotAValue <= 20)
    {
    MotorDriverF= 1;
  
     MotorDriverF=0;
 }
 
 //9 PORTIONS
 if (PortionPotAValue > 21 && PortionPotAValue <= 30) 
   {
    MotorDriverF= 1;
   
     MotorDriverF=0;
 }
      
      
 // 12 PORTIONS       
 if (PortionPotAValue > 31 && PortionPotAValue <= 40)   
   {
    MotorDriverF= 1;
   
     MotorDriverF=0;
   }
 }
}
}

      
   
  
  
      
   
  
  
