/*
  LED Cube Assignment

  This programs uses 12 pins on the Arduino Uno to light 27 LEDs that are soldered 
  in the form of a 3 by 3 by 3 cube. This cube will light the LEDs in nine routines.
  The sequence is as follows:
  - Routine 1: Spiraling up the cube one LED at a time
  - Routine 2: Randomly lights LEDs for 30 seconds
  - Routine 3: LEDs start at the center and burst outward
  - Routine 4: Levels flashing up and down
  - Routine 5: Columns flashing side to side
  - Routine 6: Flash the walls in rotating motion
  - Routine 7: Randomly moving snake of LEDs
  - Routine 8: 3 LEDs spiraling in each level moving in different directions
  - Routine 9: Flashing numbers 1 to 9 only being visible at a 45 degree angle

  Made by: Daniel Roufail

  April 21, 2023

  Version 3
*/

// Declaring variables and arrays

// This array is used to store the pins of the positives of the LEDs
// The digital pins used are 0, 1, 2, 3, 4, 5, 6, 7, 8
byte positivePins[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

// This array stores the pins of the negatives of the LEDs
// The analog pins used are 3, 4, 5
byte negativePins[] = { A3, A4, A5};

// This arrays stores the order of the pins that would be used to create a spiral with the LEDs
// The order of the spiraling LED pins are 0, 1, 2, 5, 8, 7, 6, 3, 4
byte spiralPins[] = {0, 1, 2, 5, 8, 7, 6, 3, 4}; 

byte snakePins[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};


// This variable is used as an index for cycling through certain pins
byte y;

// Only runs code once
// Sets up the pins
void setup() {

  // Cycles through all the pins being used and sets them to output pins
  // When analog or digital pins are set to output they only have two values (on or off)
  // When a pin is turned off then it acts as the ground
  for(int i = 0; i < 9; i++){
    pinMode(positivePins[i], OUTPUT);
    pinMode(negativePins[i], OUTPUT);
  }
}

// Runs code infinitely
void loop() {

  // Calls the sequence setSequence
  // This will make the LEDs light in the given pattern
  setSequence();
  
}

// Calls all the sequence subroutines so that the LEDs light in the correct pattern
void setSequence(){
  // Lights routine 1
  spiralIn(0);
  spiralOut(1);
  spiralIn(2);

  // Lights routine 2
  starLight();

  // Lights routine 3
  starBurst();

  // Lights routine 4
  for (int x = 0; x < 3; x++){
    lightLevel(x);
  }
  lightLevel(1);
  lightLevel(0);

  // Lights routine 5
  for (int x = 0; x < 3; x++){
    lightColumn(x);
  }
  lightColumn(1);
  lightColumn(0);

  // Lights routine 6
  for (int i = 0; i < 3; i++){
    lightLevel(0);
    lightColumn(0);
    lightLevel(2);
    lightColumn(2);
  }

  // Lights routine 7
  randomSnake();

  // Lights routine 8 
  rotatingLevels();

  // Lights routine 9
  displayNumbers();
}

// This lights a three LED long snake to move randomly around the cube
void randomSnake(){
  
  // Sets the initial position of the snake and declares the direction and movement
  byte position[3][3] = {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}};
  int direction = 0;
  int movement = 0;

  // Makes the snake move 20 times
  for(int count = 0; count < 20; count++){

    // Loops 200 times for persistence of vision
    for (int vision = 0; vision < 200; vision++){

      //Lights the three LEDs at the same time
      for(int place = 0; place < 3; place++){
        lightLed(snakePins[position[place][1]][position[place][0]], position[place][2]);
        visionReset();
      }
    }

    // Receives a direction (x, y, z) and the movement (up/down, left/right)
    // This will loop until the new position is valid (in cube and doesn't move backwards)
    do{ 
      direction = random(0, 3);
      movement = random(0, 2);
      
      if (movement == 0){
        movement = -1;
      }
      else if (movement == 1){
        movement = 1;
      }

    }
    while((position[0][direction] + movement) < 0 || 
          (position[0][direction] + movement) > 2 ||
          (position[0][direction] + movement) == position[0][direction] ||
          (position[0][direction] + movement) == position[1][direction]);

    // Sets the new position for the back two LEDs
    for(int x = 0; x < 3; x++){
      position[2][x] = position[1][x];
      position[1][x] = position[0][x];  
    }

    // Sets the new position for the first LED
    position[0][direction] = position[0][direction] + movement;
  }
}

// This subroutine combines and calls all the number subroutines
// This will make the LEDs flash from 1 to 9 visible at a 45 degree angle
void displayNumbers(){
  
  // Turns off all the LEDs 
  resetLeds();
  
  // Lights the number 1
  numberOne();
  
  // Lights the number 2
  numberTwo();
  
  // Lights the number 3
  numberThree();
  
  // Lights the number 4
  numberFour();

  // Lights the number 5
  numberFive();

  // Lights the number 6
  numberSix();

  // Lights the number 7
  numberSeven();

  // Lights the number 8
  numberEight();

  // Lights the number 9
  numberNine();
}

// Flashes the number 1
void numberOne(){
  
  // This sequence repeats 200 times for persistence of vision to occur
  for (int vision = 0; vision < 200; vision++){

    resetLeds();

    // The following code lights the specific LEDs required to form the number 1 

    for(int i = 0; i < 3; i++){
      lightLed(5, i);
      visionReset();
    }

    lightLed(4, 2);
    visionReset();
    lightLed(3, 2);
    visionReset();
  }
}

// Flashes the number 2
void numberTwo(){
  
  // This sequence repeats 200 times for persistence of vision to occur
  for(int vision = 0; vision < 200; vision++){

    resetLeds();
    
    // The following code lights the specific LEDs required to form the number 2

    for(int i = 0; i < 9; i++){
      if (!(i == 4 || i == 7)){
        lightLed(i, 2);
        visionReset();
      }
    }

    lightLed(8, 1);
    visionReset();

    lightLed(8, 0);
    visionReset();
    lightLed(5, 0);
    visionReset();
    lightLed(2, 0);
    visionReset();
  }
}

// Flashes the number 3
void numberThree(){
  
  // This sequence repeats 200 times for persistence of vision to occur
  for(int vision = 0; vision < 200; vision++){
    
    resetLeds();

    // The following code lights the specific LEDs required to form the number 3

    for(int i = 0; i < 9; i++){
      if(!(i == 4 || i == 7)){
        lightLed(i, 2);
        visionReset();
      }
    }

    lightLed(2, 1);
    visionReset();

    lightLed(8, 0);
    visionReset();
    lightLed(5, 0);
    visionReset();
    lightLed(2, 0);
    visionReset();
  }
}

// Flashes the number 4
void numberFour(){
    
  // This sequence repeats 200 times for persistence of vision to occur
  for(int vision = 0; vision < 200; vision++){
    
    resetLeds();

    // The following code lights the specific LEDs required to form the number 4

    for (int i = 0; i < 9; i++){
      if (!(i == 3 || i == 4)){
        lightLed(i, 2);
        visionReset();
      }
    }

    lightLed(2, 1);
    visionReset();

    lightLed(2, 0);
    visionReset();
  }
}

// Flashes the number 5
void numberFive(){
  
  // This sequence repeats 200 times for persistence of vision to occur
  for(int vision = 0; vision < 200; vision++){
    
    resetLeds();

    // The following code lights the specific LEDs required to form the number 5

    for (int i = 0; i < 9; i++){
      if(!(i == 1 || i == 4)){
        lightLed(i, 2);
        visionReset();
      }
    }

    lightLed(2, 1);
    visionReset();

    lightLed(8, 0);
    visionReset();
    lightLed(5, 0);
    visionReset();
    lightLed(2, 0);
    visionReset();
  }
}

// Flashes the number 6
void numberSix(){
  
  // This sequence repeats 200 times for persistence of vision to occur
  for(int vision = 0; vision < 200; vision++){
    
    resetLeds();
    
    // The following code lights the specific LEDs required to form the number 6

    for(int i = 5; i < 9; i++){
      lightLed(i, 2);
      visionReset();
    }
    
    lightLed(2, 2);
    visionReset();

    lightLed(8, 1);
    visionReset();
    lightLed(2, 1);
    visionReset();

    lightLed(8, 0);
    visionReset();
    lightLed(5, 0);
    visionReset();
    lightLed(2, 0);
    visionReset();
  }
}

// Flashes the number 7
void numberSeven(){
  
  // This sequence repeats 200 times for persistence of vision to occur
  for(int vision = 0; vision < 200; vision++){

    resetLeds();
    
    // The following code lights the specific LEDs required to form the number 7

    for(int i = 0; i < 4; i++){
      lightLed(i, 2);
      visionReset();
    }

    lightLed(6, 2);
    visionReset();

    lightLed(2, 1);
    visionReset();

    lightLed(2, 0);
    visionReset();
  }
}

// Flashes the number 8
void numberEight(){
  
  // This sequence repeats 200 times for persistence of vision to occur
  for(int vision = 0; vision < 200; vision++){
    resetLeds();

    // The following code lights the specific LEDs required to form the number 8
    
    for (int i = 0; i < 9; i++){
      if (!(i == 4)){
        lightLed(i, 2);
        visionReset(); 
      }
    }

    lightLed(2, 1);
    visionReset();
    lightLed(8, 1);
    visionReset();

    lightLed(8, 0);
    visionReset();
    lightLed(5, 0);
    visionReset();
    lightLed(2, 0);
    visionReset();
  }
}

// Flashes the number 9
void numberNine(){
  
  // This sequence repeats 200 times for persistence of vision to occur
  for(int vision = 0; vision < 200; vision++){
    
    resetLeds();

    // The following code lights the specific LEDs required to form the number 9
    
    for (int i = 0; i < 9; i++){
      if (!(i == 4)){
        lightLed(i, 2);
        visionReset();
      }
    }

    lightLed(2, 1);
    visionReset();

    lightLed(8, 0);
    visionReset();
    lightLed(5, 0);
    visionReset();
    lightLed(2, 0);
    visionReset();
  }
}

// This subroutine will make each level spiral its LEDs at the same time but at different directions
void rotatingLevels(){
  
  // Makes the whole sequence run three time so that it is more noticable
  for (int i = 0; i < 3; i++){
    
    // Sets the starting point for the LEDs in the second level
    y = 7;
    
    // Cycles through the positive pins of the top and bottom level
    for (int x = 0; x < 6; x++){
      
      // This sequence repeats 100 times for persistence of vision to occur
      for (int vision = 0; vision < 100; vision++){  
        
        resetLeds();

        // Lights three LEDs at a time on the top and bottom level
        // Spirals in one direction
        lightLed(spiralPins[x], 0);
        lightLed(spiralPins[x+1], 0);
        lightLed(spiralPins[x+2], 0);
        lightLed(spiralPins[x], 2);
        lightLed(spiralPins[x+1], 2);
        lightLed(spiralPins[x+2], 2);
        delay(1);
        resetLeds();

        // Lights three LEDs at a time on the middle level
        // Spirals in the other direction
        lightLed(spiralPins[y], 1);
        lightLed(spiralPins[y-1], 1);
        lightLed(spiralPins[y-2], 1);
        delay(1);
        
      }
        y--;
    }
  }
}

// This will light a column of LEDs at the given plane
void lightColumn(byte plane){
  
  // Cycles through all the LEDs in the given column and turns them on
  for (int i = 0; i < 3; i++){
    lightLed(i + (plane * 3), i);
  }
  delay(200);
  resetLeds();
}

// This will light a level of LEDs at the given plane
void lightLevel(byte plane){
  
  // Cycles through all LEDs in the given plane and turns them on
  for (int i = 0; i < 9; i ++){
    lightLed(i, plane);
  }
  delay(200);
  resetLeds();
}

// This will light the LED at the center then burst the LEDs to the corners
void starBurst(){
  
  // Flashes the center LED
  lightLed(4, 1);
  delay(500);
  resetLeds();

  // Flashes the corner LEDs
  lightLed(0, 0);
  lightLed(2, 0);
  lightLed(6, 0);
  lightLed(8, 0);
  lightLed(0, 2);
  lightLed(2, 2);
  lightLed(6, 2);
  lightLed(8, 2);

  delay(500);
  resetLeds();
}

// This will randomly flash LEDs for 30 seconds
void starLight(){
  
  // For 60 cycles it will light a random LED for half a second making this routine run for 30 seconds
  for (int x = 0; x < 60; x++){  
    lightLed(random(0, 9), random(0, 3));
    delay(500); 
    resetLeds();
  }
}

// This will spiral LEDs on the given plane starting at the middle and making its way out
void spiralOut(byte plane){
  
  //Cycles through all the LEDs in the opposite spiral pattern and turns them on accordingly
  for (int x = 9; x > 0; x--){
    lightLed(spiralPins[x-1], plane);
    delay(100);
    resetLeds();
    }
}

// This will spiral LEDs on the given plane starting on a corner and making its way towards the middle
void spiralIn(byte plane){
  
  //Cycles through all the LEDs in the spiral pattern and turns them on accordingly
  for (int x = 0; x < 9; x++){
    lightLed(spiralPins[x], plane);
    delay(100);
    resetLeds();
  }
}

// This subroutine is for reseting the LEDs and adding the delay for persistence of vistion
void visionReset(){
  delay(1);
  resetLeds();
}

// This will light a singular LED at the given line and plane (specific coordinate)
void lightLed(byte line, byte plane){
  
  // Turns on the postive pin at the given line
  digitalWrite(positivePins[line], HIGH);

  // Turns off the negative pin at the given plane
  // This will complete the circuit and light the LED
  digitalWrite(negativePins[plane], LOW);
}

// This will reset all the LEDs to turn off
void resetLeds(){
  
  // Cycles through all the positive pins and turns them off
  for(int i = 0; i < 9; i++){
    digitalWrite(positivePins[i], LOW);

  }


  // Cycles through all the negative pins and turns them on
  for(int i = 0; i < 3; i++){
    digitalWrite(negativePins[i], HIGH);
  }
}
