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

int TriggerPin = 13;  //Food Level Ultrasonic Sensor, Trigger

int EchoPin = 12;     //Food Level Ultrasonic Sensor, Echo

int MaxSpd = 135 ; //Top speed (0Â­255)

int timer3 =0;

int timer6 = 0;

int timer9 = 0;

int timer =0;

int currentstate=1;
static int MotorEnable = 0;
unsigned long DelayStart = 0; //Time the delay started

int TimePotEncoderPosCount = 0;
int TimePotALast;
int TimePotAValue;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

boolean TimePotbCW;

int PortionPotEncoderPosCount = 0;
int PortionPotALast;
int PortionPotAValue;

boolean PortionPotbCW;

int buttonState = 0;
uint8_t char_in = 0; 

void setup() 
{

pinMode(ManualPB, INPUT);
pinMode(TriggerPin, OUTPUT); // Sets the TriggerPin for Food Level Sensor as an OUTPUT
pinMode(EchoPin, INPUT); // Sets the EchoPin for Food Level Sensor as an INPUT
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
buttonState = digitalRead(ManualPB);

//GREEN LED ON WHEN POWER TO ARDUINO
digitalWrite (LEDGreen, HIGH);

if (TimePotEncoderPosCount<-10)
{
  
//FOOD LEVEL ULTRASONIC SENSOR SETUP

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

//LED CONDITIONS, FOOD LEVEL ULTRASONIC SENSOR

if(distance <= 15) digitalWrite (LEDYellow, HIGH); //Low Food LED ON
else (LEDYellow, LOW);  //Low Food LED OFF
if (distance >= 20) digitalWrite (LEDRed, HIGH); // Empty Food LED ON
else (LEDRed, LOW); // Empty Food LED OFF

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

 }
 TimePotALast = TimePotAValue;
 
//HIGH LIMIT RESET
      
 if (TimePotEncoderPosCount >= 40) TimePotEncoderPosCount =0;


//TIMEPOT CONTROL

  analogRead(TimePotEncoderPosCount);

 
if (TimePotEncoderPosCount > 10 && TimePotEncoderPosCount<=20 )
      {
      
MotorEnable=MotorEnable+1;
        Serial.println("3 hrs");
      }
        
        else if(MotorEnable>0);{
 //delay(500);
        rotateCW();
          MotorEnable==0;
      }
  
  
  if (TimePotEncoderPosCount > 20 && TimePotEncoderPosCount<=30 )
  {
      
MotorEnable=MotorEnable+1;
        Serial.println("6 hrs");
      }
        else if(MotorEnable>0);{
  //delay(2160000);
        rotateCW();
        MotorEnable=0;
      }    
   
     if (TimePotEncoderPosCount > 30 && TimePotEncoderPosCount<=40 )
      {
      
MotorEnable=MotorEnable+1;
        Serial.println("9 hrs");
      
      }
      
        else if(MotorEnable>0);{
      //  delay(32400000);
        rotateCW();
        MotorEnable=0;
      }


  
 // if (TimePotEncoderPosCount > 10 && TimePotEncoderPosCount <= 20);
 // {
 //   digitalWrite (MotorEnable, HIGH);
 //   rotateCW();     
 // }

      
//PORTIONPOT SETUP


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

   //HIGH LIMIT RESET
      
 if (PortionPotEncoderPosCount >= 40) PortionPotEncoderPosCount =0;
   
//PORTION POT CONTROL
    
     if (buttonState == HIGH) {
    // turn LED on:
   
    Serial.write(" PB Backward 50%");
      analogWrite(MotorDriverF ,127);  //Send instructions to Backward motor pin
   delay(3000);
   analogWrite(MotorDriverF ,0);
  } else {
    // turn LED off:
    
    analogWrite(MotorDriverF ,0);
  }
      
}

    void rotateCW(){
      if (PortionPotEncoderPosCount > 10 && PortionPotEncoderPosCount <= 20 && MotorEnable>0){
      delay(5000);
      Serial.write(" 3 sec Forward 100%");
    
       analogWrite(MotorDriverF, MaxSpd );  //Send instructions to Forward motor pin
    delay(3000);
    analogWrite(MotorDriverF ,0);
    MotorEnable==0;
   
    }
    
// if (MotorEnable,HIGH);
 //{
 //analogRead (PortionPotEncoderPosCount);
 //if (PortionPotEncoderPosCount > 10 && PortionPotEncoderPosCount <= 00)
  //{
  //
    //       Serial.write(" 3 sec Forward 100%");
    
   //    analogWrite(MotorDriverF, MaxSpd );  //Send instructions to Forward motor pin
   // delay(3000);
   // analogWrite(MotorDriverF ,0);
   // digitalWrite (MotorEnable,LOW);
    
    //
     // }
     
     if (PortionPotEncoderPosCount> 20 && PortionPotEncoderPosCount <= 30 && MotorEnable>0)
      {         
        delay(10000);
        Serial.write(" 6 sec Backward 100%");
      analogWrite(MotorDriverF ,MaxSpd);  //Send instructions to Backward motor pin
    delay(6000);
    analogWrite(MotorDriverF ,0);
   
    
      } 
       if (PortionPotEncoderPosCount > 30 && PortionPotEncoderPosCount <= 40 && MotorEnable>0)
      {
        delay(15000);
           Serial.write("9 sec Forward 50%");
       analogWrite(MotorDriverF ,127);  //Send instructions to Forward motor pin
    delay(9000);
    analogWrite(MotorDriverF ,0);
    
   
    
      }
   }
 


      
   
  
  




  
