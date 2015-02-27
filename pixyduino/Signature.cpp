#include "Signature.h"

Signature::Signature(Block *block){
	calibrate(block);

}

void Signature::calibrate(Block *block) {
	width = block->width;
	height = block->height;
	x1 = block->x;
	x2 = block->x + width;
	y1 = block->y;
	y2 = block->y + height;
}