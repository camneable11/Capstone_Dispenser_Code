//MX1508_ControllerSimplev0.ino
/*
This is a quick Demo sketch for control of a low voltage
brushed DC motor using the MX1508 breakout board.
We will only control one motor but drive it forward and reverse.
To keep it simple(ish), no input from the user is used.
Motor maximum voltage is 3V
Pin connections (Arduino Nano):
D9  To Motor Controller Port IN2
D10 To Motor Controller Port IN1
*/
uint8_t char_in = 0; 
const int ManualPB = 9;   //Manual Dispense Pushbutton
const int FwdPin = 10; //Forward Motor Pin
const int BwdPin = 11;  //Backward Motor Pin
long ActTime = 1500; // The time for a particular part of the cycle.
int MaxSpd = 255; //Top speed (0­255)
int LED = 2 ;
int Green = 4 ; 
boolean DirFlag = true; //Flag for direction
int buttonState = 0;

void setup()
{
   pinMode (LED, OUTPUT);  // set pin for output
  pinMode(FwdPin, OUTPUT);
  pinMode(BwdPin, OUTPUT);
  digitalWrite (LED, LOW); 
  Serial.begin(9600);
   

}

//MANUAL PUSHBUTTON CONTROL
void loop() 

{
  buttonState = digitalRead(ManualPB);
  Serial.println(buttonState); 
 while (!Serial);


  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
   
    Serial.write(" Backward 50%");
      analogWrite(BwdPin,127);  //Send instructions to Backward motor pin
   delay(3000);
   analogWrite(BwdPin,0);
  } else {
    // turn LED off:
    
    analogWrite(BwdPin,0);
  }
   
      } 
      
 
      
