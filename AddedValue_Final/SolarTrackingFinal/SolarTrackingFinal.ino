//This code was designed to be written to an arduino microcontroller that is connected to three servo motors
//and five photoresistors that are used to make a platform that will hold a solar panel follow the sun to
//allow the solar panel to have direct sunlight for longer periods of time rather than a short period of time.
//This code also implements an LCD screen that displays the voltage of the battery bank
#include <Servo.h>//allows the arduino IDE to access the servo lirary
#include <LiquidCrystal.h>//allows the arduino IDE to access the LCD lirary
LiquidCrystal lcd(12, 11, 10, 9, 8, 6);//assigns all the pins that the lcd will be attached
//initializes the analog pins for the photoresistors and the battery voltage and names the pin
const int pResistortop = A0;
const int pResistornorth = A1;
const int pResistoreast = A2;
const int pResistorsouth = A3;
const int pResistorwest = A4;
const int battvolt = A5;
//initializes the five different states and assigns a value to each
const int STILL = 0;
const int NORTH = 1;
const int EAST = 2;
const int SOUTH = 3;
const int WEST = 4;
//intializes these three variables as the names of the different servos used
Servo myservoX;
Servo myservoR;
Servo myservoL;
//initializes the variables for the values of the photoresistors read in
int top;
int north;
int east;
int south;
int west;
//initializes where the servos position should start at in this case 90 degrees
int posX = 90;
int posR = 90;
int posL = 90;
//initializes the variable for the value of the battery voltage read in
double volt;
//this is where the pin modes are assigned
void setup() {
 //sets the data rate in bits per second for serial data transmission
 Serial.begin(115200);
 //assigns which pins belong to which servo
  myservoX.attach(2);
  myservoR.attach(3);
  myservoL.attach(4);
  //writes to the servos what degree they should be starting the code at and causes them to move to that position
  myservoX.write(posX);
  myservoR.write(posR);
  myservoL.write(posL);
  //sets all the analog pins to inputs
  pinMode(pResistortop, INPUT);
  pinMode(pResistornorth, INPUT);
  pinMode(pResistoreast, INPUT);
  pinMode(pResistorsouth, INPUT);
  pinMode(pResistorwest, INPUT);
  pinMode(battvolt,INPUT);
  //allows the LCD to have information communicated with it
  lcd.begin(16,2);
  //causes the lcd to show nothing to help eliminate interference
  lcd.print("");
}
//this runs continuosly and executes the code within its brackets
void loop() {
  //reads the analog values from the input analog pins and assigns them to a variable
  volt = analogRead(battvolt);
  top = analogRead(pResistortop);
  north = analogRead(pResistornorth);
  east = analogRead(pResistoreast);
  south = analogRead(pResistorsouth);
  west = analogRead(pResistorwest);
  //converts the digital value of voltage to an actual voltage value between 0V-5V
  volt = (volt/1023)*5;
  //moves the cursor to the bottom row on the lcd
  lcd.setCursor(4,1);
  //sends the value of voltage to the lcd to be displayed
  lcd.print(volt);
  //initializes what state the system should start in
  static int state = STILL;
  //allows the code to switch from state to state based on the analog values
  switch (state)
  {
    //this state causes everything to remain constant until the condition is no longer true
    case STILL:
      if(top>north && top>east && top>south && top>west){
        posX=posX;
        posL=posL;
        posR=posR;
        myservoX.write(posX);
        myservoL.write(posL);
        myservoR.write(posR);
        delay(40);
      }  
      else{
        //allows the machine to move to the next state if this states condition doesn't hold
        state = NORTH;
      }
        break;
 
    case NORTH:
      if(top<north && posL>=40 && posR<=140){
        //increments the positions of the motors that case the platform to tilt north
        posL = posL-1;
        posR = posR+1;
        myservoL.write(posL);
        myservoR.write(posR);
        //allows servos 60 miliseconds to rotate to the new position
        delay(60);
      }
      else{
        //allows the machine to move to the next state if this states condition doesn't hold
        state = EAST;
      }
      break;
 
    case EAST:
      if(top<east){
        //checks to see if the platform is tilted towards the south
        //and if so the platform will begin to rotate counter-clockwise
        if(posR <=90 && posL >=90){
          posX = posX+1; 
          myservoX.write(posX);
          delay(40);
        }
        //has the platform rotate the other direction if the above condition isn't true
        else{
          posX = posX-1;
          myservoX.write(posX);
          delay(40);
        }
      }
      else{
        //allows the machine to move to the next state if this states condition doesn't hold
        state = SOUTH;
      }
      break;
 
    case SOUTH:
      if(top<south && posL<=140 && posR>=40){
        //increments the positions of the motors that case the platform to tilt south
        posL = posL + 1;
        posR = posR - 1;
        myservoL.write(posL);
        myservoR.write(posR);
        delay(60);
      }
      else{
        //allows the machine to move to the next state if this states condition doesn't hold
        state = WEST;
      }
      break;
 
    case WEST:
      if(top<west){
        //if the platform is pointing towards the south the platform will rotate clockwise
        if(posR <=90 && posL >=90){
          posX = posX - 1;
          myservoX.write(posX);
          delay(40);
        }
        //has the platform rotate the other direction if the above condition isn't true
        else{
          posX = posX + 1;
          myservoX.write(posX);
          delay(40);
        }
      }
      else{
        //allows the machine to move to the initial state if this states condition doesn't hold
        state = STILL;
      }
      break;
  }
}
