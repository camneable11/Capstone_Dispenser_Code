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

int MaxSpd = 100 ; //Top speed (0Â­255)

int timer3 =0;

int timer6 = 0;

int timer9 = 0;

int timer =0;

int currentstate=1;
static int MotorEnable = 0;
static int MotorEnable2 = 0;
static int MotorEnable3 = 0;
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

 
if (TimePotEncoderPosCount > 5 && TimePotEncoderPosCount<=10 && PortionPotAValue > 10 && PortionPotAValue <= 20 )
      { 
        Serial.write("#hrTimer");     
MotorEnable=MotorEnable+1;        
      }
            
        while (MotorEnable>0 );{
         
 //delay(500);
        rotateCW();
            
      }
       
  
  if (TimePotEncoderPosCount > 10 && TimePotEncoderPosCount<=15 )
  {
      
MotorEnable2=MotorEnable2+1;
     
      }
        while (MotorEnable2>0 && PortionPotEncoderPosCount <-1 );{
          
  //delay(2160000);
        rotateCW2();
            
      }    
   
     if (TimePotEncoderPosCount > 15 && TimePotEncoderPosCount<=20 )
      {
 
MotorEnable3=MotorEnable3+1;
             
      }  
        while (MotorEnable3>0 && PortionPotEncoderPosCount >0 );{
          
      //  delay(32400000);
        rotateCW3();
        
        }

 
// LIMIT RESETS   

     if (TimePotEncoderPosCount >= 21) TimePotEncoderPosCount =0;
     if (TimePotEncoderPosCount <=-10) TimePotEncoderPosCount =20;
 
      
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
   
    Serial.write("Manual PB ");
      analogWrite(MotorDriverF ,127);  //Send instructions to Backward motor pin
   delay(3000);
   analogWrite(MotorDriverF ,0);
  } else {
    // turn LED off:
    
    analogWrite(MotorDriverF ,0);
  }
  
  //HIGH LIMIT RESET

     if (PortionPotEncoderPosCount >= 40) PortionPotEncoderPosCount =0;
          
}


    void rotateCW(){
      if (PortionPotAValue > 10 && PortionPotAValue <= 20  && MotorEnable>0)
      {
        Serial.println("3 hrs");
      delay(5000);
      Serial.write(" 3 sec Forward 100%");
    
       analogWrite(MotorDriverF, MaxSpd );  //Send instructions to Forward motor pin
    delay(3000);
    analogWrite(MotorDriverF ,0);
    digitalWrite (MotorEnable,LOW);
   
    }
    }
    void rotateCW2(){
     if  (PortionPotAValue > 31 && PortionPotAValue <= 40 && MotorEnable2>0)
      {         
           Serial.println("6 hrs");
           delay(10000);
        Serial.write(" 6 sec Backward 100%");
      analogWrite(MotorDriverF ,MaxSpd);  //Send instructions to Backward motor pin
    delay(6000);
    analogWrite(MotorDriverF ,0);
      digitalWrite (MotorEnable2,LOW);
    
      } 
    }
      void rotateCW3(){
       if (PortionPotEncoderPosCount < -30 && PortionPotEncoderPosCount >=-40&& MotorEnable3>0)
      {
        Serial.println("9 hrs");
        delay(15000);
           Serial.write("9 sec Forward 50%");
       analogWrite(MotorDriverF ,127);  //Send instructions to Forward motor pin
    delay(9000);
    analogWrite(MotorDriverF ,0);  
       digitalWrite (MotorEnable3,LOW);
      }
   }
 


      
   
  
  




  
