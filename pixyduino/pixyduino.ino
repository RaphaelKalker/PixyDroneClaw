#include <SPI.h>
#include <Pixy.h>

//Shape
const uint8_t targetWidth = 150;
const uint8_t targetHeight = 150;

//Claw 
struct Claw {
  
  enum State {
   OPEN,
   OPENING,
   CLOSED,
   CLOSING,
   NA
  };
  
  State defaultState = Claw::OPEN;
  State state;

  void initClaw(){  
    state = defaultState;
    Serial.println("Initializing Claw!");
  }
  
  void setState(State s) {
    state = s;
    Serial.println("We just set the state!");
  }
  
  boolean engage(){
    Serial.println("Engaging claw of fury....");
    state = OPENING;
    //start up claw and wait for callback 
    return true;
  }
  
  boolean release(){
    Serial.println("Releasing claw of fury....");
    return true;
  }
  
  State getState(){
    return state;
  }
};


//Some needed vars
Pixy pixy;
Claw claw;

int timer = 1000;
const uint8_t frames = 25;
const int PINS[] = {11, 10, 13};

uint16_t blocks;
uint8_t len;
int i = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting pixy\n");
  pixy.init();
  
  Serial.print("Starting claw\n");
//  claw = new Claw();
  claw.initClaw();
  
  
  for (int i = 0; i < sizeof(PINS); i++) {
    pinMode(PINS[i], OUTPUT);
  }
}

void loop() {
  
  static int i = 0;
  blocks = pixy.getBlocks();
  len = sizeof(blocks);
  char buf[32];
  static int target = 0; //TODO: need to make sure this points to the correct target
  
  if (blocks) {
 
    if (++i % frames == 0) {
      sprintf(buf, "Detected %d objects: \n", blocks);
      Serial.print(buf);
      
      //Print Informations about detected objects
      for(int j = 0; j < blocks; j++) {
        sprintf(buf, " block %d: ", j);
        Serial.print(buf);
        pixy.blocks[j].print();
      }
      
      if (isObjectInRange(pixy.blocks[target])){
        Serial.println("ENGAGE THE CLAW OF FURY");
        claw.engage();
      }
    }
  } else {
    sprintf(buf, "No blocks detected, i: %d", i);
  }
}

boolean isObjectInRange(Block object){
  
 if (object.width > targetWidth || object.height > targetHeight) {
   Serial.println("Object is in range!");
   return true;
 } else {
   return false;
 }
} 

void printPixyWithDelay(int d) {
  
  for (int i = 0; i < sizeof(pixy.getBlocks()); i++ ){
    Serial.println(pixy.blocks[2].x);
    Serial.println(pixy.blocks[2].y);
  }
  delay(d);
}

boolean pixyReady() {

  if (pixy.blocks[1].signature  != 0)
  {
    timer = 2000;
    return true;
  }


  //if no repole

  //check if blocks are coming in


  return false;
}

//pixy.setLED(r,g,b)
//pixy.setBrightness()

  //printPixyWithDelay(500);

  //  checkCam();
//  if (pixyReady()) {
//    int led = 13;
//    digitalWrite(led, HIGH);
//    delay(timer);
//    digitalWrite(led, LOW);
//    delay(timer);
//  }


