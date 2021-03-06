// Blue6502
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _6502
#define _6502



uint8_t LOW_RAM = false;



uint16_t access_adress = 0x00;
uint16_t return_value = 0x00;


/* Contents of file MyROM.bin */
const int MyROM_size = 256;
const uint8_t MyROM[256] = {
  //  code and opcodes generated in Commodore 128's emulator, in Monitor (old habits die hard)

  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xA9, 0x00,         //  LDA#00
  0x20, 0x00, 0x08,   //  JSR $1000
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0x20, 0x03, 0x10,   //  JSR $1003 ($030c)
  0x18,               // CLC
  0x90, 0xF8,         // BCC 030C
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP
  0xEA,               //  NOP


  0x4C, 0x0E, 0xFF,   //  JMP $ff0e

  0xEA, 0xA2, 0x00, 0xA0, 0x00, 0xC8, 0xC0, 0xFF, 0xD0,
  0xFB, 0xE8, 0xE0, 0xFF, 0xD0, 0xF4, 0xEA, 0xEA, 0xEA, 0xA2, 0x00, 0xA0, 0x00, 0xC8, 0xC0, 0xFF,
  0xD0, 0xFB, 0xE8, 0xE0, 0xFF, 0xD0, 0xF4, 0xEA, 0xEA, 0xEA, 0xA2, 0x00, 0xA0, 0x00, 0xC8, 0xC0,
  0xFF, 0xD0, 0xFB, 0xE8, 0xE0, 0xFF, 0xD0, 0xF4, 0xEA, 0xEA, 0xEA, 0xA2, 0x00, 0xA0, 0x00, 0xC8,
  0xC0, 0xFF, 0xD0, 0xFB, 0xE8, 0xE0, 0xFF, 0xD0, 0xF4, 0xEA, 0xEA, 0xEA, 0xA2, 0x00, 0xA0, 0x00,
  0xC8, 0xC0, 0xFF, 0xD0, 0xFB, 0xE8, 0xE0, 0xFF, 0xD0, 0xF4, 0xEA, 0xEA, 0xEA, 0xA2, 0x00, 0xA0,
  0x00, 0xC8, 0xC0, 0xFF, 0xD0, 0xFB, 0xE8, 0xE0, 0xFF, 0xD0, 0xF4, 0xEA, 0xEA, 0xEA, 0xA2, 0x00,
  0xA0, 0x00, 0xC8, 0xC0, 0xFF, 0xD0, 0xFB, 0xE8, 0xE0, 0xFF, 0xD0, 0xF4, 0xEA, 0xEA, 0xEA, 0x4C,
  0x0E, 0xFF, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA,
  0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA,
  0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA,
  0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA,
  0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, 0xEA, // Filler
  0xEA, 0xEA, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
  0x00, 0x03,   // NMI Vector
  0x00, 0x03,   // Reset Vector (This will jump to program at 0x0300 )
  0x00, 0x03    // IRQ/BRK Vector
};

//6502 defines
#define UNDOCUMENTED //when this is defined, undocumented opcodes are handled.
//otherwise, they're simply treated as NOPs.

//flag modifier macros
#define setcarry() cpustatus |= FLAG_CARRY
#define clearcarry() cpustatus &= (~FLAG_CARRY)
#define setzero() cpustatus |= FLAG_ZERO
#define clearzero() cpustatus &= (~FLAG_ZERO)
#define setinterrupt() cpustatus |= FLAG_INTERRUPT
#define clearinterrupt() cpustatus &= (~FLAG_INTERRUPT)
#define setdecimal() cpustatus |= FLAG_DECIMAL
#define cleardecimal() cpustatus &= (~FLAG_DECIMAL)
#define setoverflow() cpustatus |= FLAG_OVERFLOW
#define clearoverflow() cpustatus &= (~FLAG_OVERFLOW)
#define setsign() cpustatus |= FLAG_SIGN
#define clearsign() cpustatus &= (~FLAG_SIGN)


#define  saveaccum( n)  a = ((uint8_t)(n) & 0x00FF);

//flag calculation macros
#define zerocalc( n)  if ((n) & 0x00FF) clearzero();  else setzero();


#define  signcalc( n)  {    if ((n) & 0x0080) setsign();    else clearsign();  }

#define carrycalc( n)  {    if ((n) & 0xFF00) setcarry();    else clearcarry();  }

#define  overflowcalc( n,  m,  o)   { if (((n) ^ (m)) & ((n) ^ (o)) & 0x0080) setoverflow();    else clearoverflow();  }

uint8_t FLAG_CARRY    = 0x01;
uint8_t  FLAG_ZERO    =  0x02;
uint8_t  FLAG_INTERRUPT = 0x04;
uint8_t  FLAG_DECIMAL  = 0x08;
uint8_t  FLAG_BREAK     = 0x10;
uint8_t  FLAG_CONSTANT  = 0x20;
uint8_t  FLAG_OVERFLOW = 0x40;
uint8_t  FLAG_SIGN     = 0x80;

uint16_t  BASE_STACK    = 0x100;




uint8_t  a = 0;
uint8_t x = 0;
uint8_t y = 0;
uint8_t  sp = 0xFD;
uint8_t cpustatus;
//helper variables
uint32_t instructions = 0; //keep track of total instructions executed
int32_t clockticks6502 = 0, clockgoal6502 = 0;
uint16_t oldpc, ea, reladdr, value, result;
uint8_t opcode, oldcpustatus, useaccum;
uint16_t pc;
// end 0f Blue6502 defines and variable declarations
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// globaling locals (make local variables global, to minimize push to stack time
uint16_t temp16;
uint16_t startpage;
uint16_t eahelp, eahelp2;

const uint8_t ticktable[256] = {
  /*        |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  A  |  B  |  C  |  D  |  E  |  F  |     */
  /* 0 */      7,    6,    2,    8,    3,    3,    5,    5,    3,    2,    2,    2,    4,    4,    6,    6,  /* 0 */
  /* 1 */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* 1 */
  /* 2 */      6,    6,    2,    8,    3,    3,    5,    5,    4,    2,    2,    2,    4,    4,    6,    6,  /* 2 */
  /* 3 */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* 3 */
  /* 4 */      6,    6,    2,    8,    3,    3,    5,    5,    3,    2,    2,    2,    3,    4,    6,    6,  /* 4 */
  /* 5 */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* 5 */
  /* 6 */      6,    6,    2,    8,    3,    3,    5,    5,    4,    2,    2,    2,    5,    4,    6,    6,  /* 6 */
  /* 7 */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* 7 */
  /* 8 */      2,    6,    2,    6,    3,    3,    3,    3,    2,    2,    2,    2,    4,    4,    4,    4,  /* 8 */
  /* 9 */      2,    6,    2,    6,    4,    4,    4,    4,    2,    5,    2,    5,    5,    5,    5,    5,  /* 9 */
  /* A */      2,    6,    2,    6,    3,    3,    3,    3,    2,    2,    2,    2,    4,    4,    4,    4,  /* A */
  /* B */      2,    5,    2,    5,    4,    4,    4,    4,    2,    4,    2,    4,    4,    4,    4,    4,  /* B */
  /* C */      2,    6,    2,    8,    3,    3,    5,    5,    2,    2,    2,    2,    4,    4,    6,    6,  /* C */
  /* D */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7,  /* D */
  /* E */      2,    6,    2,    8,    3,    3,    5,    5,    2,    2,    2,    2,    4,    4,    6,    6,  /* E */
  /* F */      2,    5,    2,    8,    4,    4,    6,    6,    2,    4,    2,    7,    4,    4,    7,    7   /* F */
};





#endif
#ifdef __cplusplus
} // extern "C"
#endif
