//This code was designed to be written to an arduino microcontroller that is connected to three servo motors
//and five photoresistors that are used to make a platform that will hold a solar panel follow the sun to
//allow the solar panel to have direct sunlight for longer periods of time rather than a short period of time.
#include <Servo.h>//allows the arduino IDE to access the servo lirary
//initializes the analog pins for the photoresistors and names the pin
const int pResistortop = A0;
const int pResistornorth = A1;
const int pResistoreast = A2;
const int pResistorsouth = A3;
const int pResistorwest = A4;
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
}
//this runs continuously and executes the code within its brackets
void loop() {
  //reads the analog values from the input analog pins and assigns them to a variable
  top = analogRead(pResistortop);
  north = analogRead(pResistornorth);
  east = analogRead(pResistoreast);
  south = analogRead(pResistorsouth);
  west = analogRead(pResistorwest);
  //checks to see if the top sensor has a smaller value than the north sensor
  //if so then the code inside the if statement will run
  if(top < north){
    //this will change the tilt of the platform and tilt it towards the north side of the platform base
    for (posR, posL; posR <= 140, posL >= 40; posR += 1, posL -=1) {
      //tells the servos their new position
      myservoR.write(posR);
      myservoL.write(posL);
      //allows a 60 milisecond delay so that the servos can rotate to their new position
      delay(60);
      //checks the analog values again 
      top = analogRead(pResistortop);
      north = analogRead(pResistornorth);
      east = analogRead(pResistoreast);
      south = analogRead(pResistorsouth);
      west = analogRead(pResistorwest);
      //causes the for loop to stop if the top sensor has a higher value than the north sensor
      if(top > north){
        break;
      }
    }
  }
  //checks if the top sensor is less than the east sensor
  //if it is the for loop will run
  if(top < east){
    //checks to see if the platform is tilted towards the south
    //and if so the platform will begin to rotate counter-clockwise
    if(posR <= 90 && posL >= 90){
      for (posX; posX <= 180; posX += 1) {
        //tells the rotating servo its new position
        myservoX.write(posX);
        //allows the servo to get to its new position before the code moves on
        delay(60);
        //checks the values again
        top = analogRead(pResistortop);
        north = analogRead(pResistornorth);
        east = analogRead(pResistoreast);
        south = analogRead(pResistorsouth);
        west = analogRead(pResistorwest);
        //stops the for loop if top has a higher value than east
        if(top > east){
          break;
        }
      }
    }
    //if the platform is tilted towards the north this will cause the platform to rotate clockwise
    else{      
      for (posX; posX >= 0; posX -= 1) {
        //tells the servo its new position
        myservoX.write(posX);
        //allows the servo to reach new position before code continues
        delay(60);
        //checks the sensor values again
        top = analogRead(pResistortop);
        north = analogRead(pResistornorth);
        east = analogRead(pResistoreast);
        south = analogRead(pResistorsouth);
        west = analogRead(pResistorwest);
        //stops the for loop if the top has a higher value than the east
        if(top > east){
          break;
        }
      }  
    }
  }
  //checks to see if top has a lower value then south and if so
  // this code causes the platform to tilt south
  if(top < south){
    for (posR, posL; posR >= 40, posL <= 140; posR -= 1, posL += 1) {
      //tells the servos their new position
      myservoR.write(posR);
      myservoL.write(posL);
      //allows the servo to reach their new position before the code continues
      delay(60); 
      //checks the sensor values again
      top = analogRead(pResistortop);
      north = analogRead(pResistornorth);
      east = analogRead(pResistoreast);
      south = analogRead(pResistorsouth);
      west = analogRead(pResistorwest);
      //the for loop will stop if the top value is greater than the south value
      if(top > south){
        break;
      }
    }
  }
  //checks to see if the top value is lower than the west value
  if(top < west){
    //if the platform is pointing towards the south the platform will rotate clockwise
    if(posR <= 90 && posL >= 90){
      //causes the platform to tun clockwise a degree at a time
      for (posX; posX >= 0; posX -= 1) {
        //tells the servo its new position
        myservoX.write(posX);
        //allows the servo to reach its new position before the code continues
        delay(60);
        //checks the sensor values again
        top = analogRead(pResistortop);
        north = analogRead(pResistornorth);
        east = analogRead(pResistoreast);
        south = analogRead(pResistorsouth);
        west = analogRead(pResistorwest);
        //stops the for loop if the top value is larger than the west value
        if(top > west){
          break;
        }
      }
    }
    //if the platform is tilted towards the north side then the platform will rotate counter-clockwise
    else{ 
      //makes the platform rotate counter-clockwise one degree at a time     
      for (posX; posX <= 180; posX += 1) {
        //tells the servo its new position
        myservoX.write(posX);
        //allows the servo to reach its new position before the code continues
        delay(60);
        //checks the sensors values again
        top = analogRead(pResistortop);
        north = analogRead(pResistornorth);
        east = analogRead(pResistoreast);
        south = analogRead(pResistorsouth);
        west = analogRead(pResistorwest);
        //if the top value is larger than the west value then the for loop will stop
        if(top > west){
          break;
        }
      }  
    }
  }
}

