// --------- Clock code ---------------------------

// name the months of the year
const char janStr[] = "Jan";
const char febStr[] = "Feb";
const char marStr[] = "March";
const char aprStr[] = "April";
const char mayStr[] = "May";
const char junStr[] = "June";
const char julStr[] = "July";
const char augStr[] = "Aug";
const char sepStr[] = "Sept";
const char octStr[] = "Oct";
const char novStr[] = "Nov";
const char decStr[] = "Dec";

const char* const JanStr[] = {janStr, febStr, marStr, aprStr, mayStr, junStr, 
                              julStr, augStr, sepStr, octStr, novStr, decStr};

// Weekday strings
const char sunStr[] = "Sunday\n";
const char monStr[] = "Monday\n";
const char tueStr[] = "Tuesday\n";
const char wedStr[] = "Wednesday\n";
const char thuStr[] = "Thursday\n";
const char friStr[] = "Friday\n";
const char satStr[] = "Saturday\n";

const char* const SunStr[] = {sunStr, monStr, tueStr, wedStr, thuStr, friStr, satStr};

// Other time related strings
char WDayStr[16];    // weekday string with NL
char MonthStr[12];   // month abbreviation with built-in NL
char HrSelStr[8];    // 12 or 24 for time format

// Time zone strings allow selection of +/-hh:mm in 15 min increments
char ZoneStr[] = "-07";
char ZMinStr[] = "00";
char DSTStr[] = "Off\n";
char HzStr[] = "00";

// Time strings - These are updated by makeTimeStrings()
char CenStr[] = "00";
char YrsStr[] = "00";
char MonStr[] = "00";
char DayStr[] = "00\n";
char HrsStr[] = "00";
char MinStr[] = "00";
char SecStr[] = "00\n";

// Some fixed strings
char BlankLn[] = "\n";
char ColStr[]  = ":";
char DashStr[] = "-";
char SlaStr[]  = "/";
char SpaStr[]  = " ";
char DoneStr[] = "Exit menu\n"; // done with this menu
char OnStr[]   = "On \n";  // for on/off options like DST
char OffStr[]  = "Off\n";  // both are 5 bytes for easy copying

// The splash screen draw list
char scopeClock[] = "The Scope Clock\n";
char fromStr[]    = "from\n";
char cathCorn[]   = "Cathode Corner\n";
char copyR[]   = "(C)2021 David Forbes\n";
struct item splashList[] = {
  {text,12,0,0,scopeClock,0,0},
  {text,8,0,0,fromStr,   0,0},
  {text,12,0,0,cathCorn,  0,0},
  {text,10,0,0,BlankLn,   0,0},
  {text,6,0,0,versionNo, 0,0},
  {text,6,0,0,copyR, 0,0},
  {listend,0,0,0,BlankLn,0,0}
};

// ----------------------------- Analog clock drawing -------------------

// The Face draw list has circles for minor marks and Roman
// numerals for the compass points. A circle in the center too.
// The hands are drawn by DrawClk
// The positions of the numerals are trial-and-error.

char romanI[]    = "I";
char romanII[]   = "II";
char romanIII[]  = "III";
char romanIIII[] = "IIII";
char romanV[]    = "V";
char romanVI[]   = "VI";
char romanVII[]  = "VII";
char romanVIII[] = "VIII";
char romanIX[]   = "IX";
char romanX[]    = "X";
char romanXI[]   = "XI";
char romanXII[]  = "XII";
struct item faceList[] = {
  {text,10,0,0,romanI,      490,  760},    //  1 o'clock
  {text,10,0,0,romanII,     820,  400},    //  2 o'clock
  {text,10,0,0,romanIII,    900, -100},    //  3 o'clock
  {text,10,0,0,romanIIII,   740, -590},    //  4 o'clock
  {text,10,0,0,romanV,      400, -960},    //  5 o'clock
  {text,10,0,0,romanVI,    -100,-1080},    //  6 o'clock
  {text,10,0,0,romanVII,   -600, -960},    //  7 o'clock
  {text,10,0,0,romanVIII, -1000, -600},    //  7 o'clock
  {text,10,0,0,romanIX,   -1040, -100},    //  9 o'clock
  {text,10,0,0,romanX,     -940,  400},    // 10 o'clock
  {text,10,0,0,romanXI,    -600,  760},    // 11 o'clock
  {text,10,0,0,romanXII,   -160,  880},    // 12 o'clock
  {listend,0,0,0,BlankLn,0,0}
};

// DrawClk draws the three clock hands. They are drawn in fine
// increments of 1.5 degrees per step. The steps are calculated
// incorporating the smaller time units for smoother movement.
// The angle is (0=N, 60=E, 120=S, 180=W)
void DrawClk() {
  drawACircle(0, 0, 180);   // 
//  DoHand(250, (Ticks / HalfSec) << 1 + (Secs << 2));  // no Ticks right now, so no smooth sweep.
  // doingHand = true;
  drawRadialLine(200, 2500, 240, Secs<<2);
  drawRadialLine(200, 2000, 240, (Secs / 15) + (Mins << 2));
  drawRadialLine(200, 1500, 240, (Hrs % 12) * 20 + Mins / 3);
  drawRadialLine(200, 2000, 240, (Secs / 15) + (Mins << 2));   // make the hour and minute hands bright by doubling up
  drawRadialLine(200, 1500, 240, (Hrs % 12) * 20 + Mins / 3);
  // doingHand = false;
}

// ------------------------ another analog clock -----------------------------

struct item clock2List[] = {
  {text,40,0,0,BlankLn, 0,0},
  {text,10,0,0,HrsStr,  0,0},   // hours
  {text,10,0,0,ColStr,  0,0},   // colon
  {text,10,0,0,MinStr,  0,0},   // mins
  {text,10,0,0,ColStr,  0,0},   // colon
  {text,10,0,0,SecStr,  0,0},   // secs
  {text,7,0,0,WDayStr, 0,0},   // day of week
  {listend,0,0,0,BlankLn,0,0}
};

void clock2Draw() {
  int largeTickInside = 2500;
  int largeTickOutside = 3000;
  int midTickInside = 2500;
  int midTickOutside = 2700;
  int smallTickInside = 2500;
  int smallTickOutside = 2600;
  int centerCircle = 60;

  // The RTC only gives us second-resolution time.  This goofyness sort of syncronizes the millis() counter with the RTC to allow smooth second-hand motion.
  // The sycnronization isn't great until we get to the top of the minute...
  int framesPerSec=1000;
  int framesPerMin=60000;
  static int currentMinute = -1;
  static int millisMinOld = 0;

  if(currentMinute != Mins) {
    millisMinOld = millis() - (Secs * framesPerSec);               // Fudge the second hand when we start up...
    currentMinute = Mins;
  }

  for(int i = 0; i < 60; i++) {                                    // Draw the tick marks.
    if(i%15 == 0)
      drawRadialLine(largeTickInside, largeTickOutside, 60, i);
    else if(i%5 == 0)
      drawRadialLine(midTickInside, midTickOutside, 60, i);
    else if(i <= Secs)
      drawRadialLine(smallTickInside, smallTickOutside, 240, i << 2);     
  }

  for(int i = 0; i<=3; i++)  // highlight the current second.
    if(Secs%15 == 0)
      drawRadialLine(largeTickInside, largeTickOutside, 240, Secs << 2);
    else if(Secs%5 == 0)
      drawRadialLine(midTickInside, midTickOutside, 240, Secs << 2);
    else
      drawRadialLine(smallTickInside, smallTickOutside, 240, Secs << 2);

  drawACircle(0, 0, centerCircle);
  drawACircle(0, 0, 40);
  drawACircle(0, 0, 20);

  drawRadialLine(centerCircle+15, 1940, 1440, (float)1440/framesPerMin*(millis()-millisMinOld));  // smoooooooooooooth.
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 70);
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 50);
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 30);
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 10);
  drawRadialLine(2080, 2200, 1440, (float)1440/framesPerMin*(millis()-millisMinOld));

  drawRadialLine(centerCircle+15, 2000, 240, (Secs / 15) + (Mins << 2));
  drawRadialLine(centerCircle+15, 2000, 240, (Secs / 15) + (Mins << 2));

  drawRadialLine(centerCircle+15, 1500, 240, (Hrs % 12) * 20 + Mins / 3);
  drawRadialLine(centerCircle+15, 1500, 240, (Hrs % 12) * 20 + Mins / 3);
}

// ------------------------ another analog clock -----------------------------

struct item clock3List[] = {
  {text,40,0,0,BlankLn, 0,0},
  {text,10,0,1,HrsStr,  0,0},   // hours
  {text,10,0,1,ColStr,  0,0},   // colon
  {text,10,0,1,MinStr,  0,0},   // mins
  {text,10,0,1,ColStr,  0,0},   // colon
  {text,10,0,1,SecStr,  0,0},   // secs
  {text,7,0,1,WDayStr, 0,0},   // day of week
  {listend,0,0,0,BlankLn,0,0}
};

void clock3Draw() {
  int largeTickInside = 2500;
  int largeTickOutside = 3000;
  int midTickInside = 2500;
  int midTickOutside = 2700;
  int smallTickInside = 2500;
  int smallTickOutside = 2600;
  int centerCircle = 60;

  // The RTC only gives us second-resolution time.  This goofyness sort of syncronizes the millis() counter with the RTC to allow smooth second-hand motion.
  // The sycnronization isn't great until we get to the top of the minute...
  int framesPerSec=1000;
  int framesPerMin=60000;
  static int currentMinute = -1;
  static int millisMinOld = 0;

  if(currentMinute != Mins) {
    millisMinOld = millis() - (Secs * framesPerSec);               // Fudge the second hand when we start up...
    currentMinute = Mins;
  }

  for(int i = 60; i > 0; i--) {                                    // Draw the tick marks.
    if(i%15 == 0)
      drawRadialLine(largeTickInside, largeTickOutside, 60, i);
    else if(i%5 == 0)
      drawRadialLine(midTickInside, midTickOutside, 60, i);
    else if(i <= Secs)
      drawRadialLine(smallTickInside, smallTickOutside, 240, i << 2);
  }

  for(int i = 0; i<=3; i++)  // highlight the current second.
    if(Secs%15 == 0)
      drawRadialLine(largeTickInside, largeTickOutside, 240, Secs << 2);
    else if(Secs%5 == 0)
      drawRadialLine(midTickInside, midTickOutside, 240, Secs << 2);
    else
      drawRadialLine(smallTickInside, smallTickOutside, 240, Secs << 2);

  drawACircle(0, 0, centerCircle);
  drawACircle(0, 0, 40);
  drawACircle(0, 0, 20);

  drawRadialLine(centerCircle+15, 1940, 1440, (float)1440/framesPerMin*(millis()-millisMinOld));  // smoooooooooooooth.
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 70);
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 50);
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 30);
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 10);
  drawRadialLine(2080, 2200, 1440, (float)1440/framesPerMin*(millis()-millisMinOld));

  drawRadialLine(centerCircle+15, 2000, 240, (Secs / 15) + (Mins << 2));
  drawRadialLine(centerCircle+15, 2000, 240, (Secs / 15) + (Mins << 2));
  drawRadialLine(centerCircle+15, 1500, 240, (Hrs % 12) * 20 + Mins / 3);
  drawRadialLine(centerCircle+15, 1500, 240, (Hrs % 12) * 20 + Mins / 3);

  setCubeSize(0, 0, 75, 25, 32, 20, 0, 600);

  doCube();
}

// ------------------------ another analog clock -----------------------------

void reset_spaceclock() {
  reset_stars();
  set_star_count(256);
}

void spaceclockDraw() {
  int largeTickInside = 2500;
  int largeTickOutside = 3000;
  int midTickInside = 2500;
  int midTickOutside = 2700;
  int smallTickInside = 2500;
  int smallTickOutside = 2600;
  int centerCircle = 60;

  // The RTC only gives us second-resolution time.  This goofyness sort of syncronizes the millis() counter with the RTC to allow smooth second-hand motion.
  // The sycnronization isn't great until we get to the top of the minute...
  int framesPerSec=1000;
  int framesPerMin=60000;
  static int currentMinute = -1;
  static int millisMinOld = 0;

  if(currentMinute != Mins) {
    millisMinOld = millis() - (Secs * framesPerSec);               // Fudge the second hand when we start up...
    currentMinute = Mins;
  }

  for(int i = 60; i > 0; i--) {                                    // Draw the tick marks.
    if(i%15 == 0)
      drawRadialLine(largeTickInside, largeTickOutside, 60, i);
    else if(i%5 == 0)
      drawRadialLine(midTickInside, midTickOutside, 60, i);
    else if(i <= Secs)
      drawRadialLine(smallTickInside, smallTickOutside, 240, i << 2);
  }

  for(int i = 0; i<=3; i++)  // highlight the current second.
    if(Secs%15 == 0)
      drawRadialLine(largeTickInside, largeTickOutside, 240, Secs << 2);
    else if(Secs%5 == 0)
      drawRadialLine(midTickInside, midTickOutside, 240, Secs << 2);
    else
      drawRadialLine(smallTickInside, smallTickOutside, 240, Secs << 2);

  drawACircle(0, 0, centerCircle);
  drawACircle(0, 0, 40);
  drawACircle(0, 0, 20);

  drawRadialLine(centerCircle+15, 1940, 1440, (float)1440/framesPerMin*(millis()-millisMinOld));  // smoooooooooooooth.
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 70);
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 50);
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 30);
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 10);
  drawRadialLine(2080, 2200, 1440, (float)1440/framesPerMin*(millis()-millisMinOld));

  drawRadialLine(centerCircle+15, 2000, 240, (Secs / 15) + (Mins << 2));
  drawRadialLine(centerCircle+15, 2000, 240, (Secs / 15) + (Mins << 2));
  drawRadialLine(centerCircle+15, 1500, 240, (Hrs % 12) * 20 + Mins / 3);
  drawRadialLine(centerCircle+15, 1500, 240, (Hrs % 12) * 20 + Mins / 3);

  setCubeSize(0, 0, 75, 25, 32, 20, 0, 600);

  doStars();
}

// ------------------------ digital clocks -----------------------------------

// total time/date/day digital clock draw list
struct item timefList[]  = {
  {text,20,0,0,WDayStr, 0,0},   // day of week
  {text,20,0,0,HrsStr,  0,0},   // hours
  {text,20,0,0,ColStr,  0,0},   // colon
  {text,20,0,0,MinStr,  0,0},   // mins
  {text,20,0,0,ColStr,  0,0},   // colon
  {text,20,0,0,SecStr,  0,0},   // secs
  {text,20,0,0,MonthStr,0,0},   // month
  {text,20,0,0,SpaStr,  0,0},   
  {text,20,0,0,DayStr,  0,0},   // day
  {text,20,0,0,CenStr,  0,0},   // the full year
  {text,20,0,0,YrsStr,  0,0}, 
  {text,20,0,0,BlankLn, 0,0}, 
  {listend,0,0,0,BlankLn, 0,0}
};

// 6 digit digital clock with date draw list
struct item time6dList[] = {
  {text,16,0,0,MonthStr,0,0},  // months
  {text,16,0,0,SpaStr,  0,0},  // space
  {text,16,0,0,DayStr,  0,0},  // days
  {text,40,0,0,HrsStr,  0,0},  // hours
  {text,40,0,0,ColStr,  0,0},  // colon
  {text,40,0,0,MinStr,  0,0},  // mins
  {text,40,0,0,BlankLn, 0,0},  // next line
  {text,30,0,0,SecStr,  0,0},  // secs
  {listend,0,0,0,BlankLn, 0,0}
};


// 4 digit digital clock with date draw list
struct item time4dList[] = {
  {text,16,0,0,WDayStr, 0,0},  // weekday
  {text,40,0,0,HrsStr,  0,0},  // hours
  {text,40,0,0,ColStr,  0,0},  // colon
  {text,40,0,0,MinStr,  0,0},  // mins
  {text,40,0,0,BlankLn, 0,0},  // next line
  {text,16,0,0,MonthStr,0,0},  // months
  {text,16,0,0,SpaStr,  0,0},  // space
  {text,16,0,0,DayStr,  0,0},  // days
  {listend,0,0,0,BlankLn,0,0}
};


// 6 digit digital clock draw list
struct item time6nList[] = {
  {text,10,0,0,BlankLn, 0,0},  // make hh:mm line lower for better centered appearance
  {text,40,0,0,HrsStr,  0,0},  // hours
  {text,40,0,0,ColStr,  0,0},  // colon
  {text,40,0,0,MinStr,  0,0},  // mins
  {text,40,0,0,BlankLn, 0,0},  // next line
  {text,30,0,0,SecStr,  0,0},  // secs
  {listend,0,0,0,BlankLn,0,0}
};


// 4 digit digital clock draw list
struct item time4nList[] = {
  {text,40,0,0,HrsStr,  0,0},  // hours
  {text,40,0,0,ColStr,  0,0},  // colon
  {text,40,0,0,MinStr,  0,0},  // mins
  {text,40,0,0,BlankLn, 0,0}, // next line
  {listend,0,0,0,BlankLn,0,0}
};

// ----------------------- Time string generator -----------------------

// makeTimeStrings fills in the time and date strings in RAM with the
// current time in ASCII. The month and weekday strings are set also.
void makeTimeStrings() {
  int hours, zon;  // temp storage for manipulation
  if (Hr12) 
  {
    HrSelStr[0] = '1';
    HrSelStr[1] = '2';
  }
  else
  {
    HrSelStr[0] = '2';
    HrSelStr[1] = '4';
  }
  CenStr[0] = (Century / 10) | '0';
  CenStr[1] = (Century % 10) | '0';
  YrsStr[0] = (Years / 10) | '0';
  YrsStr[1] = (Years % 10) | '0';
  MonStr[0] = (Mons / 10) | '0';
  MonStr[1] = (Mons % 10) | '0';

  DayStr[0] = (Days / 10) | '0';
  DayStr[1] = (Days % 10) | '0';
  DayStr[2] = '\n';

  // make the day of month be one digit if leading zero
  if (DayStr[0] == '0')
  {
    DayStr[0] = DayStr[1];
    DayStr[1] = '\n';
    DayStr[2] = 0;
  }

  // read the weekday string from ROM
  strcpy(WDayStr, SunStr[WDay]); 

  // read the month string from ROM
  strcpy(MonthStr, JanStr[Mons - 1]);

  hours = Hrs;  // temp for doing 12 hour madness
  if (Hr12) 
  {
    if (hours == 0) hours = 12;
    if (hours > 12) hours -= 12;
  }
  HrsStr[0] = (hours / 10) | '0';
  HrsStr[1] = (hours % 10) | '0';
  if ((Hr12) && (HrsStr[0] == '0')) 
  {
    HrsStr[0] = HrsStr[1];
    HrsStr[1] = 0;  // one digit if < 10
  }
  MinStr[0] = (Mins / 10) | '0';
  MinStr[1] = (Mins % 10) | '0';
  SecStr[0] = (Secs / 10) | '0';
  SecStr[1] = (Secs % 10) | '0';
  HzStr[0] = (Hertz / 10) | '0';
  if (DST) 
  {
    DSTStr[1] = 'n';   // DST on
    DSTStr[2] = ' ';
  }
  else 
  {
    DSTStr[1] = 'f';
    DSTStr[2] = 'f';
  }
  zon = Zone;   // temp copy of timezone to monge
  if (zon >= 0) ZoneStr[0] = '+';
  else {
    ZoneStr[0] = '-';
    zon = 0 - zon;      // make it positive for display
  }
  ZoneStr[1] = (zon / 10) | '0';
  ZoneStr[2] = (zon % 10) | '0';
  if (ZoneStr[0] == '0') 
  {
    ZoneStr[0] = ZoneStr[1];
    ZoneStr[1] = '\n';  // one digit if < 10
  }
  ZMinStr[0] = (ZMins / 10) | '0';
  ZMinStr[1] = (ZMins % 10) | '0';
}
