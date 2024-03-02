#ifndef _PORT_H
#define _PORT_H

/*==========================================
writePinP1(a,b) - Write pin "a" of port 1
with value "b"
readPinP1(a) - Setup pin "a" of port 1 for reading 
and return value at pin
==========================================*/
void writePinP1(const tByte, const bit);
bit readPinP1(const tByte);

#endif