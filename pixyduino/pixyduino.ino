#include <SPI.h>
#include <Pixy.h>

//Shape
const uint8_t targetWidth = 150;
const uint8_t targetHeight = 150;
const uint8_t TARGET_X1 = 150;
const uint8_t TARGET_X2 = 300;
const uint8_t TARGET_Y1 = 100;
const uint8_t TARGET_Y2 = 300;

struct Signature {
  private: 
    Signature *sig;
    Signature(){
      //disallow ctor instantiation
    }
  
  public:
    uint16_t x1 = 150;
    uint16_t x2 = 300;
    uint16_t y1 = 100;
    uint16_t y2 = 300;
    uint16_t width;
    uint16_t height;
    
    Signature newSignature(Block *block){
      sig = new Signature();
      sig->calibrate(block);
      return *sig;
    }
    
    void calibrate(Block *block) {
      width = block->width;
      height = block->height;
      x1 = block->x;
      x2 = block->x + width;
      y1 = block->y;
      y2 = block->y + height;
    }
};

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
    boolean test = false;

    void initClaw() {
      Serial.println("Initializing Claw!");
      state = defaultState;
      pinMode(motorPin, OUTPUT);
      pinMode(motorPinClose, OUTPUT);
    }

    State getState() {
      return state;
    }

    void setState(State s) {
      state = s;
      Serial.println("We just set the state!");
    }

    boolean engage() {
      Serial.println("Engaging claw of fury....");
      state = OPENING;
      //ensure claw is open so we can clench onto the object
      if (openClaw()) {

        //this will delay until open, best to have fallback
        closeClaw();

        //reset the whole thing
        delay(1000);
        initClaw();
      } else {
        Serial.print("FAILURE");
      }
      return true;
    }

    boolean release() {
      Serial.println("Releasing claw of fury....");
      return true;
    }

  private:
    boolean openClaw() {
      if (test) {
        state = OPEN;
        return false;
      }
      Serial.println("Opening claw...");
      state = OPENING;
      digitalWrite(motorPin, HIGH);
      delay(1000);
      digitalWrite(motorPin, LOW);
      state = OPEN;

      if (state == OPEN) {
        return true;
      }

      return false;
    }

    boolean closeClaw() {
      if (test) {
        return true;
      }

      Serial.println("Closing claw...");
      state = CLOSING;
      digitalWrite(motorPinClose, HIGH);
      delay(1000);
      state = CLOSED;
      digitalWrite(motorPinClose, LOW);

      if (state == CLOSED) {
        return true;
      }

      return false;
    }
};


//Some needed vars
Pixy pixy;
Claw claw;

int timer = 1000;
const uint8_t frames = 25;
uint16_t blocks;
uint8_t len;
int i = 0;
uint8_t btnPin = 13;

Signature *sig1;
Signature *sig2;
Signature *sig3;
Signature *sig4;
Signature *sig5;
Signature *sig6;
Signature *sig7;

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
      for (int j = 0; j < blocks; j++) {
        sprintf(buf, " block %d: ", j);
        Serial.print(buf);
        pixy.blocks[j].print();

        //confirm target based on centered object and size
        if (isObjectInRange(pixy.blocks[j])) {
          Serial.println("Object is in range");
          claw.engage();
          Serial.println("done");
        }
      }
    }
  } else {
    sprintf(buf, "No blocks detected, i: %d", i);
  }

  /*
  * Get current block on screen and create a Signature for comparison later
  */
  if (digitalRead(btnPin) == HIGH) {
    Serial.println("Read Signature");
    if (true) {
      sig1->newSignature(pixy.blocks); //temp assumption, handle case of tons of objects on the screen
    }
  }
}

boolean isObjectInRange(Block block) {

  /*
  * check if item is centered based on the some target thresholds for the object's size
  * this should ignore false positives for objects of the wrong size
  */

  if (block.x > TARGET_X1 && block.x < TARGET_X1 + block.width
      && block.y > TARGET_Y1 && block.y < TARGET_Y1 + block.height) {
    char buffalo[128];
    sprintf(buffalo, "Object is centered -> Sig: %d, xLeft: %d, xRight: %d, yTop: %d, yBottom: %d",
            block.signature, block.x, block.x + block.width, block.y, block.y + block.height);
    Serial.println(buffalo);
    return true;
  }
  return false;
  //  return block.width > targetWidth || block.height > targetHeight;
}

boolean readyToScan() {
  return claw.state == claw.OPEN;
}

//pixy.setLED(r,g,b)
//pixy.setBrightness()




