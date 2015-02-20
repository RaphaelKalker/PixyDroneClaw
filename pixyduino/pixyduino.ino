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

  const State defaultState = Claw::OPEN;
  State state;
  const uint8_t motorPin = 9;
  const uint8_t motorPinClose = 6;

  void initClaw(){
    Serial.println("Initializing Claw!");
    state = defaultState;
    pinMode(motorPin, OUTPUT);
    pinMode(motorPinClose, OUTPUT);
  }

  State getState(){
      return state;
    }
  
  void setState(State s) {
    state = s;
    Serial.println("We just set the state!");
  }

  boolean engage(){
    Serial.println("Engaging claw of fury....");
    state = OPENING;
    //ensure claw is open so we can clench onto the object
    if (openClaw()){
      
      //this will delay until open, best to have fallback
      closeClaw();
      
      //reset the whole thing
      delay(10000);
      initClaw();
    } else {
      Serial.print("FAILURE");
    }
    return true;
  }

  boolean release(){
    Serial.println("Releasing claw of fury....");
    return true;
  }

  private:
    boolean openClaw(){
      Serial.println("Opening claw...");
      state = OPENING;
      digitalWrite(motorPin, HIGH);
      delay(5000);
      digitalWrite(motorPin, LOW);
      state = OPEN;
      
      if (state == OPEN) {
        return true;
      }
      
      return false;
    }
    
    boolean closeClaw() {
      Serial.println("Closing claw...");
      state = CLOSING;
      digitalWrite(motorPinClose, HIGH);
      delay(5000);
      state = CLOSED;
      digitalWrite(motorPinClose, LOW);
      
      if (state == CLOSED){
        return true;
      }
      
      return false;
    }
};


//Some needed vars
Pixy pixy;
Claw claw;

int timer = 1000;
const uint8_t frames = 100;
uint16_t blocks;
uint8_t len;
int i = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting pixy\n");
  pixy.init();

  Serial.print("Starting claw\n");
  claw.initClaw();
}

void loop() {

  static int i = 0;
  blocks = pixy.getBlocks();
  len = sizeof(blocks);
  char buf[32];

  if (blocks && readyToScan()) {

    if (++i % frames == 0) {
      sprintf(buf, "Detected %d objects: \n", blocks);
      Serial.print(buf);

      //Print Informations about detected objects
      for(int j = 0; j < blocks; j++) {
        sprintf(buf, " block %d: ", j);
        Serial.print(buf);
        pixy.blocks[j].print();
      }

      if (isObjectInRange(pixy.blocks[getTarget()])){
        Serial.println("Object is in range");
        claw.engage();
      }
    }
  } else {
    sprintf(buf, "No blocks detected, i: %d", i);
  }
}

boolean isObjectInRange(Block object){
  return object.width > targetWidth || object.height > targetHeight;
}

boolean readyToScan() {
  return claw.state == claw.OPEN;
}

static uint8_t getTarget(){
  //need to determine which one is the target incase there are multiple objects detected
  return 0;
}

//pixy.setLED(r,g,b)
//pixy.setBrightness()


