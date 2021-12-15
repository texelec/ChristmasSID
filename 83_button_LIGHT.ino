//LED Code Added by Kevin Williams for Christmas SID
// 0=idle, 1,2,3,4...=short clicks,  -1=is_pressed

//Button press                       BUTTON_LIGHT 

//        1                          Toggle Mantle Mode                 
//        2                          Toggle Flame Speed
//        3                          All Off / All On                      

uint32_t BT_time_start_LIGHT;
uint32_t BT_time_end_LIGHT;
uint32_t BT_previous_time_LIGHT;
uint32_t BT_curent_time_LIGHT;
int16_t state_LIGHT = HIGH;
int16_t prevstate_LIGHT = HIGH;
int16_t clickCount_LIGHT = 0;
int buttonValue_LIGHT = 0;

uint32_t BT_debounce_time_LIGHT = 100;
uint32_t BT_short_click_time_LIGHT = 650;
uint32_t BT_is_pressed_time_LIGHT = 1500;
uint32_t BT_short_click_lag_time_LIGHT = 333;

int GetButtonStatus_LIGHT() {

#ifdef BUTTON_LIGHT

  state_LIGHT = digitalRead(BUTTON_LIGHT);
  BT_curent_time_LIGHT = millis();

  if (state_LIGHT != prevstate_LIGHT) { // debounce
    if ( (BT_curent_time_LIGHT - BT_previous_time_LIGHT) > BT_debounce_time_LIGHT) {
      BT_previous_time_LIGHT = BT_curent_time_LIGHT;
    }
    else {
      state_LIGHT = prevstate_LIGHT;
    }
  }

  if ( prevstate_LIGHT == HIGH && state_LIGHT == HIGH   ) {

    if (  ((BT_curent_time_LIGHT - BT_time_end_LIGHT) > BT_short_click_lag_time_LIGHT )  ) { // button is "sensed" after timing out, so it have little "lag"
      buttonValue_LIGHT = clickCount_LIGHT;
      clickCount_LIGHT = 0; // reset clickCount_LIGHT if short click timed out
    }
  }

  if ( prevstate_LIGHT == HIGH  && state_LIGHT == LOW) { // button just pressed, just memorize time of a event
    BT_time_start_LIGHT = BT_curent_time_LIGHT;
    prevstate_LIGHT = state_LIGHT;
  }

  if (prevstate_LIGHT == LOW && state_LIGHT == LOW   ) {
    prevstate_LIGHT = state_LIGHT;
    if (BT_curent_time_LIGHT > (BT_time_start_LIGHT + BT_is_pressed_time_LIGHT)) {
      clickCount_LIGHT = 0; //
      buttonValue_LIGHT =  -1; // is_pressed
    }
  }

  if ( prevstate_LIGHT == LOW  && state_LIGHT == HIGH ) { // button released
    BT_time_end_LIGHT = BT_curent_time_LIGHT;
    prevstate_LIGHT = state_LIGHT;
    if (  ((BT_time_end_LIGHT - BT_time_start_LIGHT) < BT_short_click_time_LIGHT)  ) {
      clickCount_LIGHT++;
      buttonValue_LIGHT = 0; //                                                            will keep counting clicks
    }

    if (((BT_time_end_LIGHT - BT_time_start_LIGHT)  > BT_is_pressed_time_LIGHT) ) {
      clickCount_LIGHT = 0;
      buttonValue_LIGHT = 0; //                                                             it was is_pressed so far, ignore release
    }
  }

#endif // return 0 if there is no button defined

  return buttonValue_LIGHT;
}

void checkButton_LIGHT() {
  switch (GetButtonStatus_LIGHT()) {
    case 0:
      break;
    case -1:  //long press
      break;
    case 1:  // 1 short click - selects next pattern, and off as the last option
      endloop=0;             //counter used by the Mantle routine for routine loop counter
      mainloop=0;            //counter used by the Mantle routine for routine loop counter
      LED_CTR=0;             //index for data
      if (++patternsel > maxpat) {patternsel=0;}   //turn off pattern if already at last one
      break;
    case 2:  // two clicks
      switch (updatespeed) {
       case  0: updatespeed=1;break;    //toggles between three flame update speed settings, or off
       case  1: updatespeed=5;break;
       case  5: updatespeed=12;break;
       case 12: updatespeed=0;break;
       default: break;
      }
      break;
    case 3:  // three clicks           //disable/enable all LEDs
     switch (LEDSON) {                     
      case false: 
       updatespeed=0;      //disable flame
       patternsel=0;       //disable mantle
       LEDSON=true;
       break;
      case true:
       patternsel=1;
       updatespeed=1;
       endloop=0;
       mainloop=0;
       LED_CTR=0;
       LEDSON=false; 
       break;
      default:
       break;
    }
  }
}
