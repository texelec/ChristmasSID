//LED Code Added by Kevin Williams for Christmas SID

//#define LED_MAING1      PB3                 //LED pairs on main PCB from left to right
//#define LED_MAINR1      PA15
//#define LED_MAING2      PB5
//#define LED_MAINR2      PB4
//#define LED_MAING3      PB7  
//#define LED_MAINR3      PB6  
//#define LED_MAING4      PB8  
//#define LED_MAINR4      PB9  
//#define LED_FL_LEFTG    PB14                //LED pairs on Flame PCB from left, right & Center
//#define LED_FL_LEFTR    PB10  
//#define LED_FL_RIGHTG   PB1  
//#define LED_FL_RIGHTR   PB0  
//#define LED_FL_CENTG    PB13 
//#define LED_FL_CENTR    PB12 

#include "STM32TimerInterrupt.h"            //Interrupt timer for LED Update routine
#include "STM32_ISR_Timer.h"

const int maxpat=11;                         //total number of LED patterns

const int LED_DATA[maxpat][750] ={         //Each chunk below is a different pattern
 {1300,                                     //The top number controls a loop in the update routine.
     0, 0,1 , 0,0 , 0,0 , 0,0,              //The first number in each row after that is where in the 
    50, 0,0 , 0,1 , 0,0 , 0,0,              //loop to trigger the data.  The data matches the mantle
   100, 0,0 , 0,0 , 0,1 , 0,0,              //LED locations, IE, the first pair is the left-most LED.
   150, 0,0 , 0,0 , 0,0 , 0,1,              //Each pair controls the Green, Red where 0 is off 1 is on.
   200, 0,0 , 0,0 , 0,1 , 0,0,              //The routine will autorepeat until changed.  
   250, 0,0 , 0,1 , 0,0 , 0,0,              
   300, 0,1 , 0,0 , 0,0 , 0,0,
   350, 0,0 , 0,0 , 0,0 , 0,0,                         
   400, 0,0 , 0,0 , 0,0 , 1,0,
   450, 0,0 , 0,0 , 1,0 , 0,0,
   500, 0,0 , 1,0 , 0,0 , 0,0,
   550, 1,0 , 0,0 , 0,0 , 0,0,                        
   600, 0,0 , 1,0 , 0,0 , 0,0,
   650, 0,0 , 0,0 , 1,0 , 0,0,
   700, 0,0 , 0,0 , 0,0 , 1,0,
   750, 0,0 , 0,0 , 0,0 , 0,0,
   800, 1,0 , 0,0 , 0,0 , 0,1,
   850, 0,0 , 1,0 , 0,1 , 0,0,
   900, 0,0 , 0,1 , 1,0 , 0,0,
   950, 0,1 , 0,0 , 0,0 , 1,0,                        
  1000, 0,0 , 0,0 , 0,0 , 0,0,
  1050, 0,1 , 0,0 , 0,0 , 1,0,
  1100, 0,0 , 0,1 , 1,0 , 0,0,
  1150, 0,0 , 1,0 , 0,1 , 0,0,
  1200, 1,0 , 0,0 , 0,0 , 0,1,                        
  1250, 0,0 , 0,0 , 0,0 , 0,0},

  {125,     
     0, 1,1 , 1,1 , 1,1 , 1,1,
    25, 0,1 , 0,1 , 0,1 , 0,1,
    75, 0,0 , 0,0 , 0,0 , 0,0,
   100, 1,0 , 1,0 , 1,0 , 1,0},

 {125, 
     0, 1,1 , 0,1 , 0,0 , 1,0,
    25, 1,0 , 1,1 , 0,1 , 0,0,
    75, 0,0 , 1,0 , 1,1 , 0,1,
   100, 0,1 , 0,0 , 1,0 , 1,1},

{500,
0, 0, 1, 1, 0, 0, 1, 1, 0,
100, 1, 1, 0, 1, 1, 0, 0, 1,
200, 1, 0, 1, 1, 0, 1, 1, 0,
300, 0, 1, 1, 0, 1, 1, 0, 1,
400, 1, 0, 0, 1, 1, 0, 1, 1},

{2400,
0,1,0,0,0,0,0,0,0,
100,1,0,1,0,0,0,0,0,
200,1,0,1,0,1,0,0,0,
300,1,0,1,0,1,0,1,0,
400,0,1,1,0,1,0,1,0,
500,1,0,0,1,1,0,1,0,
600,1,0,1,0,0,1,1,0,
700,1,0,1,0,1,0,0,1,
800,1,1,1,0,1,0,1,0,
900,1,0,1,1,1,0,1,0,
1000,1,0,1,0,1,1,1,0,
1100,1,0,1,0,1,0,1,1,
1200,1,0,1,0,1,1,1,1,
1300,1,0,1,1,1,1,1,1,
1400,1,1,1,1,1,1,1,1,
1500,1,1,1,1,1,1,0,1,
1600,1,1,1,1,0,1,0,1,
1700,1,1,0,1,0,1,0,1,
1800,0,1,0,1,0,1,0,1,
1900,0,1,0,1,0,1,1,0,
2000,0,1,0,1,1,0,0,0,
2100,0,1,1,0,0,0,0,0,
2200,1,0,0,0,0,0,0,0,
2300,0,0,0,0,0,0,0,0},

{600,
0  ,1,0,1,0,1,0,1,0,
200,0,1,0,1,0,1,0,1,
400,1,1,1,1,1,1,1,1},

{1200,
  0  ,1,0,0,1,1,0,0,1,
200  ,1,1,0,1,1,1,0,1,
400  ,1,1,1,0,1,1,1,0,
600  ,0,1,1,0,0,1,1,0,
800  ,0,1,1,1,0,1,1,1,
1000  ,1,0,1,1,1,0,1,1},

{1200,
0,0,1,0,0,0,0,0,0,
10,0,1,0,0,0,0,0,0,
20,0,1,0,0,0,0,0,0,
30,0,0,0,1,0,0,0,0,
40,0,0,0,1,0,0,0,0,
50,0,0,0,0,0,1,0,0,
60,0,0,0,0,0,1,0,0,
70,0,0,0,0,0,0,0,1,
80,0,0,0,0,0,0,0,1,
90,0,0,0,0,0,0,0,1,
100,0,0,0,0,0,0,0,0,
110,0,0,0,0,0,0,0,0,
120,0,0,0,0,0,0,0,0,
130,0,0,0,0,0,0,0,0,
140,0,0,0,0,0,0,0,0,
150,0,0,0,0,0,0,0,1,
160,0,0,0,0,0,0,0,1,
170,0,0,0,0,0,0,0,1,
180,0,0,0,0,0,1,0,0,
190,0,0,0,0,0,1,0,0,
200,0,0,0,1,0,0,0,0,
210,0,0,0,1,0,0,0,0,
220,0,1,0,0,0,0,0,0,
230,0,1,0,0,0,0,0,0,
240,0,1,0,0,0,0,0,0,
250,0,0,0,0,0,0,0,0,
400,1,0,0,0,0,0,0,0,
410,1,0,0,0,0,0,0,0,
420,1,0,0,0,0,0,0,0,
430,0,0,1,0,0,0,0,0,
440,0,0,1,0,0,0,0,0,
450,0,0,0,0,1,0,0,0,
460,0,0,0,0,1,0,0,0,
470,0,0,0,0,0,0,1,0,
480,0,0,0,0,0,0,1,0,
490,0,0,0,0,0,0,1,0,
500,0,0,0,0,0,0,0,0,
510,0,0,0,0,0,0,0,0,
520,0,0,0,0,0,0,0,0,
530,0,0,0,0,0,0,0,0,
540,0,0,0,0,0,0,0,0,
550,0,0,0,0,0,0,1,0,
560,0,0,0,0,0,0,1,0,
570,0,0,0,0,0,0,1,0,
580,0,0,0,0,1,0,0,0,
590,0,0,0,0,1,0,0,0,
600,0,0,1,0,0,0,0,0,
610,0,0,1,0,0,0,0,0,
620,1,0,0,0,0,0,0,0,
630,1,0,0,0,0,0,0,0,
640,1,0,0,0,0,0,0,0,
650,0,0,0,0,0,0,0,0,
800,1,1,0,0,0,0,0,0,
810,1,1,0,0,0,0,0,0,
820,1,1,0,0,0,0,0,0,
830,0,0,1,1,0,0,0,0,
840,0,0,1,1,0,0,0,0,
850,0,0,0,0,1,1,0,0,
860,0,0,0,0,1,1,0,0,
870,0,0,0,0,0,0,1,1,
880,0,0,0,0,0,0,1,1,
890,0,0,0,0,0,0,1,1,
900,0,0,0,0,0,0,0,0,
910,0,0,0,0,0,0,0,0,
920,0,0,0,0,0,0,0,0,
930,0,0,0,0,0,0,0,0,
940,0,0,0,0,0,0,0,0,
950,0,0,0,0,0,0,1,1,
960,0,0,0,0,0,0,1,1,
970,0,0,0,0,0,0,1,1,
980,0,0,0,0,1,1,0,0,
990,0,0,0,0,1,1,0,0,
1000,0,0,1,1,0,0,0,0,
1010,0,0,1,1,0,0,0,0,
1020,1,1,0,0,0,0,0,0,
1030,1,1,0,0,0,0,0,0,
1040,1,1,0,0,0,0,0,0,
1050,0,0,0,0,0,0,0,0},

{1500,
0,1,0,1,0,1,0,1,0,
100,1,0,0,1,0,1,1,0,
200,0,1,1,0,1,0,0,1,
300,1,0,0,1,0,1,1,0,
400,0,1,1,0,1,0,0,1,
500,0,1,0,1,0,1,0,1,
600,0,1,1,1,1,1,0,1,
700,1,1,0,1,0,1,1,1,
800,0,1,1,1,1,1,0,1,
900,1,1,0,1,0,1,1,1,
1000,1,1,1,1,1,1,1,1,
1100,1,1,1,0,1,0,1,1,
1200,1,0,1,1,1,1,1,0,
1300,1,1,1,0,1,0,1,1,
1400,1,0,1,1,1,1,1,0},

{1600,
0   ,0,1,0,0,0,0,0,0,
100 ,1,0,0,0,0,0,0,0,
200 ,1,1,0,1,0,0,0,0,
300 ,0,0,1,0,0,0,0,0,
400 ,0,0,1,1,0,1,0,0,
500 ,0,0,0,0,1,0,0,0,
600 ,0,0,0,0,1,1,0,1,
700 ,0,0,0,0,0,0,1,0,
800 ,0,0,0,0,0,0,1,1,
900 ,0,0,0,0,0,0,1,0,
1000,0,0,0,0,1,1,0,1,
1100,0,0,0,0,1,0,0,0,
1200,0,0,1,1,0,1,0,0,
1300,0,0,1,0,0,0,0,0,
1400,1,1,0,1,0,0,0,0,
1500,1,0,0,0,0,0,0,0
},

/*
{1100,
0,   0,0,0,0,0,0,1,1,
100, 0,1,0,0,0,0,1,1,
200, 0,0,0,0,0,0,1,1,
300, 0,0,0,0,0,0,1,0,
400, 0,0,0,0,1,1,0,1,
500, 0,0,0,0,1,0,0,0,
600, 0,0,1,1,0,1,0,0,
700, 0,0,1,0,0,0,0,0,
800, 1,1,0,1,0,0,0,0,
900, 1,0,0,0,0,0,0,0,
1000,0,1,0,0,0,0,0,0},
*/
{3350,
0,   1,0,0,0,0,0,0,0,
50,     0,0,1,0,0,0,0,0,
100,     0,0,0,0,1,0,0,0,
150,     0,0,0,0,0,0,1,0,
200,     1,0,0,0,0,0,1,0,
250,     0,0,1,0,0,0,1,0,
300,     0,0,0,0,1,0,1,0,
350,     1,0,0,0,1,0,1,0,
400,     0,0,1,0,1,0,1,0,
450,     1,0,1,0,1,0,1,0,
500,     1,0,1,0,1,0,1,0,
550,     0,1,1,0,1,0,1,0,
600,     1,0,0,1,1,0,1,0,
650,     1,0,1,0,0,1,1,0,
700,     1,0,1,0,1,0,0,1,
750,     0,1,1,0,1,0,0,1,
800,     1,0,0,1,1,0,0,1,
850,     1,0,1,0,0,1,0,1,
900,     0,1,1,0,0,1,0,1,
1000,     1,0,0,1,0,1,0,1,
1050,     0,1,0,1,0,1,0,1,
1100,     0,1,0,1,0,1,0,1,
1150,     1,1,0,1,0,1,0,1,
1200,     0,1,1,1,0,1,0,1,
1250,     0,1,0,1,1,1,0,1,
1300,     0,1,0,1,0,1,1,1,
1350,     1,1,0,1,0,1,1,1,
1400,     0,1,1,1,0,1,1,1,
1450,     0,1,0,1,1,1,1,1,
1500,     1,1,0,1,1,1,1,1,
1550,     0,1,1,1,1,1,1,1,
1600,     1,1,1,1,1,1,1,1,
1650,     1,1,1,1,1,1,1,1,
1700,     1,1,1,1,1,1,0,1,
1750,     1,1,1,1,0,1,1,1,
1800,     1,1,0,1,1,1,1,1,
1850,     0,1,1,1,1,1,1,1,
1900,     0,1,1,1,1,1,0,1,
1950,     0,1,1,1,0,1,1,1,
2000,     0,1,0,1,1,1,1,1,
2050,     0,1,0,1,1,1,0,1,
2100,     0,1,0,1,0,1,1,1,
2150,     0,1,0,1,0,1,0,1,
2200,     0,1,0,1,0,1,0,1,
2250,     0,1,0,1,0,1,1,0,
2300,     0,1,0,1,1,0,0,1,
2350,     0,1,1,0,0,1,0,1,
2400,     1,0,0,1,0,1,0,1,
2450,     1,0,0,1,0,1,1,0,
2500,     1,0,0,1,1,0,0,1,
2550,     1,0,1,0,0,1,0,1,
2600,     1,0,1,0,0,1,1,0,
2650,     1,0,1,0,1,0,0,1,
2700,     1,0,1,0,1,0,1,0,
2750,     1,0,1,0,1,0,1,0,
2800,     1,0,1,0,1,0,0,0,
2850,     1,0,1,0,0,0,1,0,
2900,     1,0,0,0,1,0,1,0,
2950,     0,0,1,0,1,0,1,0,
3000,     0,0,1,0,1,0,0,0,
3050,     0,0,1,0,0,0,1,0,
3100,     0,0,0,0,1,0,1,0,
3150,     0,0,0,0,1,0,0,0,
3200,     0,0,0,0,0,0,1,0,
3250,     0,0,0,0,0,0,0,0,
3300,     0,0,0,0,0,0,0,0}
};
 
                        
long redpercent=30;                         //The "flame" is random and this controls how weighted one color is over the other
long greenpercent=70;                       //green+red=orange w/LEDs, more Red in this mix looks orangish more of the time IMO
long centerpercent=50;                      //The center is averaged from the outside two LEDs, this controls that mix - btw, red & green LEDs are backwards on flame, fix it if I remember later

int  flameloop=0;                           //used for flame routine, IE how often to update flame state
bool flame_already_off=false;               //when mantle LEDs are off, so it only turns them off once 


int  endloop=0;                             //end of loop read from routine
int  mainloop=0;                            //counter used by the Mantle routine for routine loop counter
int  LED_CTR=0;                             //index for data
bool man_already_off=false;                 //when mantle LEDs are off, so it only turns them off once

bool LEDSON=false;                     //Used to toggle all LEDs on/off

bool LED_LEFTG_STATE=false;                 //keeps track of LED state(s)
bool LED_LEFTR_STATE=false;
bool LED_RIGHTG_STATE=false;
bool LED_RIGHTR_STATE=false;
bool LED_CENTG_STATE=false;
bool LED_CENTR_STATE=false;
bool LED_MR1_STATE=false;
bool LED_MR2_STATE=false;
bool LED_MR3_STATE=false;
bool LED_MR4_STATE=false;
bool LED_MG1_STATE=false;
bool LED_MG2_STATE=false;
bool LED_MG3_STATE=false;
bool LED_MG4_STATE=false;

//End vars

STM32Timer ITimer(TIM3);                    //Timer 3 is free, SID uses one and two
STM32_ISR_Timer ISR_Timer;   

void TimerHandler() {ISR_Timer.run();}      //starts the timer 

void LED_MR1_T()    {HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);}     //toggles each LED fast
void LED_MR2_T()    {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);}
void LED_MR3_T()    {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_6);}
void LED_MR4_T()    {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);}
void LED_MG1_T()    {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);}
void LED_MG2_T()    {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);}
void LED_MG3_T()    {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);}
void LED_MG4_T()    {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_8);}
void LED_LEFTG_T()  {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);}
void LED_LEFTR_T()  {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);}
void LED_CENTG_T()  {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);}
void LED_CENTR_T()  {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);}
void LED_RIGHTG_T() {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);}
void LED_RIGHTR_T() {HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);}

void pinInit() {           //enables outpus for LEDs. pinMode was oddly failing to set some of the Output pins correctly, this works all of the time
 GPIO_InitTypeDef GPIO_InitStruct; 
 __GPIOA_CLK_ENABLE(); 
 __GPIOB_CLK_ENABLE(); 
 GPIO_InitStruct.Pin = GPIO_PIN_15; 
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 
 GPIO_InitStruct.Speed = GPIO_SPEED_LOW; 
 HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 

 GPIO_InitStruct.Pin = (GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_9 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_14 | GPIO_PIN_10 | GPIO_PIN_13 | GPIO_PIN_12 | GPIO_PIN_1 | GPIO_PIN_0); 
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; 
 GPIO_InitStruct.Speed = GPIO_SPEED_LOW; 
 HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); 
}

bool weightedrand(long percent) {                        //return a 0 to 100 based on a percentage weighted
 long randomnum=random(1,100);                           //used by flame routine
 if (randomnum<percent) {return true;} else {return false;}
}

void Flame_Update() { 
 if (!flameloop) {                                       //is it time to update flame?
  if (weightedrand(redpercent)!=LED_LEFTR_STATE) {       //A basic a way to make a random flicker. I pull a random number  //Red LED 2
   LED_LEFTR_STATE=!LED_LEFTR_STATE;LED_LEFTR_T();       //between 1 & 100, and weight it by a percantage.  Currently red hits 70%
  }                                                      //and green only hits 30%.  Looks roughly fireish to me. :-)
  if (weightedrand(greenpercent)!=LED_LEFTG_STATE) {     //Green LED 2
   LED_LEFTG_STATE=!LED_LEFTG_STATE;LED_LEFTG_T();
  }
  if (weightedrand(redpercent)!=LED_RIGHTR_STATE) {      //Red LED 4
   LED_RIGHTR_STATE=!LED_RIGHTR_STATE;LED_RIGHTR_T();
  }
  if (weightedrand(greenpercent)!=LED_RIGHTG_STATE) {    //Green LED 4
   LED_RIGHTG_STATE=!LED_RIGHTG_STATE;LED_RIGHTG_T();
  }
  bool redresult=LED_CENTR_STATE;                        //The center will be off for green or red if both were off on left & right.
  bool greenresult=LED_CENTG_STATE;                      //If only one was on, it tosses a coin currently for the center.
  if ((LED_LEFTR_STATE==0) && (LED_RIGHTR_STATE==0)) redresult=false;  //This sort of makes the center follow the left & right behavior.
  if ((LED_LEFTR_STATE==1) || (LED_RIGHTR_STATE==1)) redresult=weightedrand(centerpercent);
  if ((LED_LEFTR_STATE==1) && (LED_RIGHTR_STATE==1)) redresult=true; 

  if ((LED_LEFTG_STATE==0) && (LED_RIGHTG_STATE==0)) greenresult=false;
  if ((LED_LEFTG_STATE==1) || (LED_RIGHTG_STATE==1)) greenresult=weightedrand(greenpercent);
  if ((LED_LEFTG_STATE==1) && (LED_RIGHTG_STATE==1)) greenresult=true; 
  
  if (redresult!=LED_CENTR_STATE) {         //Red LED 3
   LED_CENTR_STATE=!LED_CENTR_STATE;LED_CENTR_T();     
  }
  if (greenresult!=LED_CENTG_STATE) {       //Red Green 3
   LED_CENTG_STATE=!LED_CENTG_STATE;LED_CENTG_T();     
  }
 }
 if (++flameloop>=updatespeed) flameloop=0;   //control update speed
}
                      
void Mantle_Update() {
 int ind=patternsel-1;                                 //get array index from currently selected pattern
 if (!endloop) {endloop=LED_DATA[ind][LED_CTR++];}     //read loop index on first run
 int comp=LED_DATA[ind][LED_CTR];                      
 if(comp==mainloop) {                                  //see if the LED state needs to change
  if (LED_DATA[ind][++LED_CTR]!=LED_MR1_STATE) {       //check red LED 1 status, and see if it needs to change
   LED_MR1_STATE=!LED_MR1_STATE;LED_MR1_T();           //Toggle State flag & LED
  }
  if (LED_DATA[ind][++LED_CTR]!=LED_MG1_STATE) {       //Green LED 1
   LED_MG1_STATE=!LED_MG1_STATE;LED_MG1_T();     
  }
  if (LED_DATA[ind][++LED_CTR]!=LED_MR2_STATE) {       //Red LED 2
   LED_MR2_STATE=!LED_MR2_STATE;LED_MR2_T();     
  }
  if (LED_DATA[ind][++LED_CTR]!=LED_MG2_STATE) {       //Green LED 2
   LED_MG2_STATE=!LED_MG2_STATE;LED_MG2_T();     
  }
  if (LED_DATA[ind][++LED_CTR]!=LED_MR3_STATE) {       //Red LED 3
   LED_MR3_STATE=!LED_MR3_STATE;LED_MR3_T();     
  }
   
  if (LED_DATA[ind][++LED_CTR]!=LED_MG3_STATE) {       //Green LED 3
   LED_MG3_STATE=!LED_MG3_STATE;LED_MG3_T();     
  }
  if (LED_DATA[ind][++LED_CTR]!=LED_MR4_STATE) {       //Red LED 4
   LED_MR4_STATE=!LED_MR4_STATE;LED_MR4_T();     
  }
  if (LED_DATA[ind][++LED_CTR]!=LED_MG4_STATE) {       //Green LED 4
   LED_MG4_STATE=!LED_MG4_STATE;LED_MG4_T();     
  }
  LED_CTR++;
 }
 if (++mainloop==endloop) {                            //reset
  mainloop=0;
  endloop=0;
  LED_CTR=0;
 }
}  

void flame_out() {                                                   //turns off flame LED
 if (LED_LEFTR_STATE)  {LED_LEFTR_T();LED_LEFTR_STATE=0;}
 if (LED_RIGHTR_STATE) {LED_RIGHTR_T();LED_RIGHTR_STATE=0;}
 if (LED_LEFTG_STATE)  {LED_LEFTG_T();LED_LEFTG_STATE=0;}
 if (LED_RIGHTG_STATE) {LED_RIGHTG_T();LED_RIGHTG_STATE=0;}
 if (LED_CENTR_STATE)  {LED_CENTR_T();LED_CENTR_STATE=0;}
 if (LED_CENTG_STATE)  {LED_CENTG_T();LED_CENTG_STATE=0;} 
}

void mantle_out() {                                                  //turns off mantle LED
  if (LED_MR1_STATE)  {LED_MR1_T();LED_MR1_STATE=0;}
  if (LED_MG1_STATE)  {LED_MG1_T();LED_MG1_STATE=0;}
  if (LED_MR2_STATE)  {LED_MR2_T();LED_MR2_STATE=0;}
  if (LED_MG2_STATE)  {LED_MG2_T();LED_MG2_STATE=0;}
  if (LED_MR3_STATE)  {LED_MR3_T();LED_MR3_STATE=0;}
  if (LED_MG3_STATE)  {LED_MG3_T();LED_MG3_STATE=0;}
  if (LED_MR4_STATE)  {LED_MR4_T();LED_MR4_STATE=0;}
  if (LED_MG4_STATE)  {LED_MG4_T();LED_MG4_STATE=0;}
}

void Process_LEDs()                                                  //Check to see if updates needed, and perform if so
{ 
 if (patternsel) {Mantle_Update();man_already_off=false;}            //mantle update, if on
 else if (!man_already_off) {mantle_out();man_already_off=true;}     //if off blank out leds once
 
 if (updatespeed) {Flame_Update();flame_already_off=false;}          //flame update, if on
 else if (!flame_already_off) {flame_out();flame_already_off=true;}  //if off blank out leds once
}
