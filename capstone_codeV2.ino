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

unsigned long DelayStart = 0; //Time the delay started

int TimePotEncoderPosCount = 0;
int TimePotALast;
int TimePotAValue;

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
buttonState = digitalRead(ManualPB);
  Serial.println(MotorEnable); 
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

 }
 TimePotALast = TimePotAValue;
 

 
//TIMEPOT CONTROL

  //3 HR TIMER SET
  analogRead(TimePotEncoderPosCount);
  if (TimePotEncoderPosCount > 10 && TimePotEncoderPosCount <= 20);
  {
    delay (20);
    {
    digitalWrite (MotorEnable,HIGH);   
    } 
  }

     
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
      digitalRead(MotorEnable); // read the incoming data byte
 if (MotorEnable,1);
 {
 analogRead (PortionPotEncoderPosCount);
 if (PortionPotEncoderPosCount > 10 && PortionPotEncoderPosCount <= 20)
  {
  
           Serial.write(" 3 sec Forward 100%");
    
       analogWrite(MotorDriverF, MaxSpd );  //Send instructions to Forward motor pin
    delay(3000);
    analogWrite(MotorDriverF ,0);
    digitalWrite (MotorEnable,LOW);
    
    
      }
     if (PortionPotEncoderPosCount> 20 && PortionPotEncoderPosCount <= 30)
      {     
        Serial.write(" 6 sec Backward 100%");
       
      analogWrite(MotorDriverF ,MaxSpd);  //Send instructions to Backward motor pin
    delay(6000);
    analogWrite(MotorDriverF ,0);
   digitalWrite (MotorEnable,LOW);
    
      } 
       if (PortionPotEncoderPosCount > 30 && PortionPotEncoderPosCount <= 40)
      {
           Serial.write("9 sec Forward 50%");
       analogWrite(MotorDriverF ,127);  //Send instructions to Forward motor pin
    delay(9000);
    analogWrite(MotorDriverF ,0);
    digitalWrite (MotorEnable,LOW);
    
      }
   }
 
}

      
   
  
  




  
