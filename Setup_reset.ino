//WATCHDOG TIMER

void Setup_reset()
{
 //  Set watchdog timer (using avr/wdt.h library)
     cli();// disable all interrupts
     wdt_reset(); // reset the WDT timer /*
     /*WDTCSR configuration:
     WDIE = 0: Interrupt Enable
     WDE = 1   :Reset Enable
     WDP3 = 0  :Set the four prescaler bits for a 2 sec timeout
     WDP2 = 1
     WDP1 = 1 
     WDP0 = 1
      */
     // Enter Watchdog Configuration mode:
     //(1<<5) generated a byte with all zeros and one 1 at the 5th (counting from zero) bit from the right.
     //hence, for example, (1<<WDCE) generates "00010000", since WDCE=4 (see datasheet 10.9.2)
     WDTCSR |= (1<<WDCE) | (1<<WDE);
     // Set Watchdog settings:
     WDTCSR = (1<<WDIE) | (1<<WDE) | (1<<WDP3) | (0<<WDP2) | (0<<WDP1) | (1<<WDP0);
     sei();//enable interrupts

  //  Set time of next reset
      ResetTime_t = Time_next_t(1,0); //Set reset time to 01:00 the next day
      Display_Setup_reset_serial();
}

void Reset_watchdog_timer(void)
{
  if(ResetTime_t > now())
  {
    wdt_reset();
  }
  Display_Reset_watchdog_timer_serial();
 }

// MENU RESET

void Setup_menu_reset()
{
  MenuReset_t = now()+ MenuReset;
}
