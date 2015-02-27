#ifndef Signature
#define Signature


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
