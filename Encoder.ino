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

int timer3 = 0;

int timer6 = 0;

int timer9 = 0;

int MotorEnable = 0;

unsigned long DelayStart = 0; //Time the delay started

int TimePotEncoderPosCount = 0;
int TimePotALast;
int TimePotAValue;

boolean TimePotbCW;

int PortionPotEncoderPosCount = 0;
int PortionPotALast;
int PortionPotAValue;

boolean PortionPotbCW;

void setup() {
 pinMode (TimePotA,INPUT);
 pinMode (TimePotB,INPUT);
 /* Read Pin A
 Whatever state it's in will reflect the last position
 */
TimePotALast = digitalRead(TimePotA);
 Serial.begin (9600);
}


//ROTARY ENCODER SETUP TEST

void loop()
{
digitalWrite (LEDGreen, HIGH );

if (digitalRead(LEDGreen== HIGH));
{  
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
 Serial.print("Timer Position: ");
 Serial.println(TimePotEncoderPosCount);

 }
 TimePotALast = TimePotAValue;
} 

if (digitalRead(LEDGreen== HIGH));
  
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
    
     
      {
 void PORTIONS()
 if (PortionPotAValue >= 0 && PortionPotAValue <= 10)
 {
     MotorDriverF= 1;
   delay(3000);
      MotorDriverF=0;
 }
      
 
 //6 PORTIONS
 if (PortionPotAValue > 10 && PortionPotAValue <= 20)
    {
     MotorDriverF= 1;
   delay(6000);
      MotorDriverF=0;
 }
 
 //9 PORTIONS
 if (PortionPotAValue > 21 && PortionPotAValue <= 30) 
   {
     MotorDriverF= 1;
   delay(9000);
     MotorDriverF=0;
 }
      
      
 // 12 PORTIONS       
 if (PortionPotAValue > 31 && PortionPotAValue <= 40)   
   {
    MotorDriverF= 1;
   delay(12000);
   MotorDriverF=0;
   }
      }
}
