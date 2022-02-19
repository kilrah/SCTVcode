
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
char CenStr[]  = "00";
char YrsStr[]  = "00";
char MonStr[]  = "00";
char DayStr[]  = "00\n";
char HrsStr[]  = "00";
char MinStr[]  = "00";
char SecStr[]  = "00";
char MSecStr[] = "000";

char LastCenStr[]  = "00";
char LastYrsStr[]  = "00";
char LastMonStr[]  = "00";
char LastDayStr[]  = "00\n";
char LastHrsStr[]  = "00";
char LastMinStr[]  = "00";
char LastSecStr[]  = "00";
char LastMSecStr[] = "000";

// Some fixed strings
char BlankLn[] = "\n";
char ColStr[]  = ":";
char PeriodStr[] = ".";
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
  {text,12,0,0,0,0,0,scopeClock,0,0},
  {text,8,0,0,0,0,0,fromStr,   0,0},
  {text,12,0,0,0,0,0,cathCorn,  0,0},
  {text,10,0,0,0,0,0,BlankLn,   0,0},
  {text,6,0,0,0,0,0,versionNo, 0,0},
  {text,6,0,0,0,0,0,copyR, 0,0},
  {listend,0,0,0,0,0,0,BlankLn,0,0}
};

face * registerSplash() {
  face* f = (face*) malloc(sizeof(face));

  f->text = splashList;
  f->title = 0;
  f->init = 0;
  f->uninit = 0;
  f->draw = 0;
  f->uses_knobs = 0;

  return f;
}

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
  {text,10,0,0,0,0,0,romanI,      490,  760},    //  1 o'clock
  {text,10,0,0,0,0,0,romanII,     820,  400},    //  2 o'clock
  {text,10,0,0,0,0,0,romanIII,    900, -100},    //  3 o'clock
  {text,10,0,0,0,0,0,romanIIII,   740, -590},    //  4 o'clock
  {text,10,0,0,0,0,0,romanV,      400, -960},    //  5 o'clock
  {text,10,0,0,0,0,0,romanVI,    -100,-1080},    //  6 o'clock
  {text,10,0,0,0,0,0,romanVII,   -600, -960},    //  7 o'clock
  {text,10,0,0,0,0,0,romanVIII, -1000, -600},    //  7 o'clock
  {text,10,0,0,0,0,0,romanIX,   -1040, -100},    //  9 o'clock
  {text,10,0,0,0,0,0,romanX,     -940,  400},    // 10 o'clock
  {text,10,0,0,0,0,0,romanXI,    -600,  760},    // 11 o'clock
  {text,10,0,0,0,0,0,romanXII,   -160,  880},    // 12 o'clock
  {listend,0,0,0,0,0,0,BlankLn,0,0}
};

face * registerRomanClock() {
  face* f = (face*) malloc(sizeof(face));

  f->text =  faceList;

  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0, 0, 0, (char*)"Roman\n",                 -300,  -600};
  f->title[1] = {listend, 0, 0, 0, 0, 0, 0, BlankLn, 0, 0};

  f->init = 0;
  f->uninit = 0;
  f->draw = DrawClk;
  f->uses_knobs = 0;
  
  return f;
}

// DrawClk draws the three clock hands. They are drawn in fine
// increments of 1.5 degrees per step. The steps are calculated
// incorporating the smaller time units for smoother movement.
// The angle is (0=N, 60=E, 120=S, 180=W)
void DrawClk() {
  drawACircle(0, 0, 180);   // 
//  DoHand(250, (Ticks / HalfSec) << 1 + (Secs << 2));  // no Ticks right now, so no smooth sweep.
  // doingHand = true;
  drawRadialLine(200, 2500, 240, Secs<<2);

  setBrightness(102);
  drawRadialLine(200, 2000, 240, (Secs / 15) + (Mins << 2));
  drawRadialLine(200, 1500, 240, (Hrs % 12) * 20 + Mins / 3);
  setBrightness(BRIGHTNESS_DEFAULT);

  // doingHand = false;
}

// -- a basic clock with lots of tic marks
void baseClock() {
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
    if(i == Secs)                                                  // Bright if it is the current second
      setBrightness(101);
    else
      setBrightness(80);
      
    if(i%15 == 0)
      drawRadialLine(largeTickInside, largeTickOutside, 60, i);
    else if(i%5 == 0)
      drawRadialLine(midTickInside, midTickOutside, 60, i);
    else {
      if(i != Secs)                                                // Dim if it is not the current second
        setBrightness(50);

      drawRadialLine(smallTickInside, smallTickOutside, 60, i);
    }

    setBrightness(BRIGHTNESS_DEFAULT);
  }

  setBrightness(101);

  drawACircle(0, 0, centerCircle);                                                                // Center circle outline

  drawRadialLine(centerCircle+15, 2000, 240, (Secs / 15) + (Mins << 2));                          // Hours
  drawRadialLine(centerCircle+15, 1500, 240, (Hrs % 12) * 20 + Mins / 3);                         // Minutes
  drawRadialLine(centerCircle+15, 1940, 1440, (float)1440/framesPerMin*(millis()-millisMinOld));  // Seconds - smoooooooooooooth.

  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 70);             // second hand circle outline

  setBrightness(30);
  
  drawACircle(0, 0, 40);  // Center circle fill
  drawACircle(0, 0, 20);  // Center circle fill

  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 50);             // second hand circle fill
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 30);             // second hand circle fill
  drawRadialCircle(2000, 1440, (float)1440/framesPerMin*(millis()-millisMinOld), 10);             // second hand circle fill

  setBrightness(BRIGHTNESS_DEFAULT);

  drawRadialLine(2090, 2200, 1440, (float)1440/framesPerMin*(millis()-millisMinOld));             // End of second hand - dimmer to appear thinner.
}


// ------------------------ another analog clock -----------------------------

struct item clock2List[] = {
  {text,40,0,0,0,0,0, BlankLn, 0,0},
  {text,10,0,0,0,0,0, HrsStr,  0,0},   // hours
  {text,10,0,0,0,0,0, ColStr,  0,0},   // colon
  {text,10,0,0,0,0,0, MinStr,  0,0},   // mins
  {text,10,0,0,0,0,0, ColStr,  0,0},   // colon
  {text,10,0,0,0,0,0, SecStr,  0,0},   // secs
  {text,10,0,0,0,0,0, BlankLn,  0,0},   // secs
  {text,7,0,0,0,0,0, WDayStr, 0,0},   // day of week
  {listend,0,0,0,0,0,0, BlankLn,0,0}
};

face * register2Clock() {
  face* f = (face*) malloc(sizeof(face));

  f->text =  clock2List;

  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Ticks\n", -250, -1000};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};

  f->init = 0;
  f->uninit = 0;
  f->draw = clock2Draw;
  f->uses_knobs = 0;

  return f;
}

void clock2Draw() {
  baseClock();
  setBrightness(70);  // hack: This ends up dimming the text.
}

// ------------------------ another analog clock -----------------------------

struct item cubeClockList[] = {
  {text,40,0,0,0,0,0, BlankLn, 0,0},
  {text,10,0,1,0,0,0, HrsStr,  0,0},   // hours
  {text,10,0,1,0,0,0, ColStr,  0,0},   // colon
  {text,10,0,1,0,0,0, MinStr,  0,0},   // mins
  {text,10,0,1,0,0,0, ColStr,  0,0},   // colon
  {text,10,0,1,0,0,0, SecStr,  0,0},   // secs
  {text,10,0,1,0,0,0, BlankLn,  0,0},   // secs
  {text,7,0,1,0,0,0, WDayStr, 0,0},   // day of week
  {listend,0,0,0,0,0,0, BlankLn,0,0}
};

face * registerCubeClock() {
  face* f = (face*) malloc(sizeof(face));

  f->text =  cubeClockList;

  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Cube Clock\n", -500,  -1000};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};

  f->init = resetCubeClock;
  f->uninit = 0;
  f->draw = doCubeClock;
  f->uses_knobs = 0;

  return f;
}

void resetCubeClock() {
  setCubeSize(0, 0, 75, 25, 32, 20, 0, 600);
}

void doCubeClock() {
  baseClock();

  doCube();

  setBrightness(70);  // hack: This ends up dimming the text.
}

// ------------------------ space clock -----------------------------

face * registerSpaceClock() {
  face* f = (face*) malloc(sizeof(face));

  f->text = 0;

  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Space Clock\n", -600, -1000};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};

  f->init = resetSpaceClock;
  f->uninit = 0;
  f->draw = doSpaceClock;
  f->uses_knobs = 0;

  return f;
}

void resetSpaceClock() {
  init_stars();
  set_star_count(256);
}

void doSpaceClock() {
  baseClock();

  doStars();
}

// ------------------------ digital clocks -----------------------------------

/*
 * Wednesday
 * 17:11:33
 * Jan 26
 * 2022
 */

// total time/date/day digital clock draw list
struct item timefList[]  = {
  {text,20,0,0,100,0,0, HrsStr,  0,0},   // hours
  {text,20,0,0,70,0,0, ColStr,  0,0},   // colon
  {text,20,0,0,100,0,0, MinStr,  0,0},   // mins
  {text,20,0,0,70,0,0, ColStr,  0,0},   // colon
  {text,20,0,0,100,0,0, SecStr,  0,0},   // secs
  {text,20,0,0,0,0,0, BlankLn,  0,0},
  {text,20,0,0,0,0,0, WDayStr, 0,0},   // day of week
  {text,20,0,0,0,0,0, MonthStr,0,0},   // month
  {text,20,0,0,0,0,0, SpaStr,  0,0},
  {text,20,0,0,0,0,0, DayStr,  0,0},   // day
  {text,20,0,0,0,0,0, CenStr,  0,0},   // the full year
  {text,20,0,0,0,0,0, YrsStr,  0,0},
  {text,10,0,0,0,0,0, BlankLn, 0,0},
  {listend,0,0,0,0,0,0, BlankLn, 0,0}
};

face * registerDigital1() {
  face* f = (face*) malloc(sizeof(face));

  f->text = timefList;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 1\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = 0;
  f->uninit = 0;
  f->draw = 0;
  f->uses_knobs = 0;

  return f;
}

// 6 digit digital clock with date draw list
struct item time6dList[] = {
  {text,16,0,0,0,0,0,MonthStr,0,0},  // months
  {text,16,0,0,0,0,0,SpaStr,  0,0},  // space
  {text,16,0,0,0,0,0,DayStr,  0,0},  // days
  {text,40,0,0,0,0,0,HrsStr,  0,0},  // hours
  {text,40,0,0,70,0,0,ColStr,  0,0},  // colon
  {text,40,0,0,100,0,0,MinStr,  0,0},  // mins
  {text,40,0,0,0,0,0,BlankLn, 0,0},  // next line
  {text,30,0,0,0,0,0,SecStr,  0,0},  // secs
  {text,20,0,0,0,0,0, BlankLn, 0,0},
  {listend,0,0,0,0,0,0,BlankLn, 0,0}
};

face * registerDigital2() {
  face* f = (face*) malloc(sizeof(face));

  f->text = time6dList;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 2\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = 0;
  f->uninit = 0;
  f->draw = 0;
  f->uses_knobs = 0;

  return f;
}

// 4 digit digital clock with date draw list
struct item time4dList[] = {
  {text,16,0,0,0,0,0,WDayStr, 0,0},  // weekday
  {text,40,0,0,0,0,0,HrsStr,  0,0},  // hours
  {text,40,0,0,70,0,0,ColStr,  0,0},  // colon
  {text,40,0,0,100,0,0,MinStr,  0,0},  // mins
  {text,40,0,0,0,0,0,BlankLn, 0,0},  // next line
  {text,16,0,0,0,0,0,MonthStr,0,0},  // months
  {text,16,0,0,0,0,0,SpaStr,  0,0},  // space
  {text,16,0,0,0,0,0,DayStr,  0,0},  // days
  {listend,0,0,0,0,0,0,BlankLn,0,0}
};


face * registerDigital3() {
  face* f = (face*) malloc(sizeof(face));

  f->text = time4dList;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 3\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = 0;
  f->uninit = 0;
  f->draw = 0;
  f->uses_knobs = 0;

  return f;
}

// 6 digit digital clock draw list
struct item time6nList[] = {
  {text,10,0,0,0,0,0,BlankLn,  0,0},  // make hh:mm line lower for better centered appearance
  {text,40,0,0,0,0,0,HrsStr,   0,0},  // hours
  {text,40,0,0,70,0,0,ColStr,  0,0},  // colon
  {text,40,0,0,100,0,0,MinStr, 0,0},  // mins
  {text,40,0,0,0,0,0,BlankLn,  0,0},  // next line
  {text,30,0,0,0,0,0,SecStr,   0,0},  // secs
  {text,20,0,0,0,0,0,BlankLn,  0,0},
  {listend,0,0,0,0,0,0,BlankLn,0,0}
};

face * registerDigital4() {
  face* f = (face*) malloc(sizeof(face));

  f->text = time6nList;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 4\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = 0;
  f->uninit = 0;
  f->draw = 0;
  f->uses_knobs = 0;

  return f;
}

/****************************** Digital 5
 * 
 * 15:27
 * 
 * 33.123
 * 
 * Uses FastDraw for the extra strokes.
 */

// 4 digit digital clock draw list
struct item digital5List[] = {
  {text,   10,0,0,  0,0,0,BlankLn,  0,0},
  {text,   40,0,3,  0,4,9,HrsStr,   0,0},  // hours
  {text,   40,0,3, 60,0,0,ColStr,   0,0},  // colon
  {text,   40,0,3,100,4,9,MinStr,   0,0},  // mins
  {text,   40,0,0,  0,0,0,BlankLn,  0,0}, // next line
  {text,   10,0,0,  0,0,0,BlankLn,  0,0},
  {text,   10,0,3,  0,0,0,SecStr,   0,0},  // secs
  {text,   10,0,3,  0,0,0,SpaStr,0,0},  // .
  {text,   10,0,3,  0,0,0,MSecStr,  0,0},  // msecs
  {text,    0,0,0,  0,0,0,BlankLn,  0,0},
  {listend, 0,0,0,  0,0,0,BlankLn,  0,0}
};

face * registerDigital5() {
  face* f = (face*) malloc(sizeof(face));

  f->text = digital5List;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 5\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = initDigital5;
  f->uninit = deinitDigital5;
  f->draw = doDigital5;
  f->uses_knobs = 0;

  return f;
}

void initDigital5() {
  FastDraw=1;
}

void deinitDigital5() {
  FastDraw=0;
}

void doDigital5() {
  if(MSecs > 500) {
    digital5List[2].brightness = 1;
  } else {
    digital5List[2].brightness = 60;
  }
}

/****************************** Digital 6
 * 
 * 15:27
 * 
 * 33.123
 * 
 * Uses FastDraw for the extra strokes.
 */

// 4 digit digital clock draw list
struct item digital6List[] = {
  {text,   10,0,0,  0,0,0,BlankLn,  0,0},
  {text,   40,0,0,  0,4,9,HrsStr,   0,0},  // hours
  {text,   40,0,0, 60,0,0,ColStr,   0,0},  // colon
  {text,   40,0,0,100,4,9,MinStr,   0,0},  // mins
  {text,   40,0,0,  0,0,0,BlankLn,  0,0}, // next line
  {text,   10,0,0,  0,0,0,BlankLn,  0,0},
  {text,   10,0,0,  0,0,0,SecStr,   0,0},  // secs
  {text,   10,0,0,  0,0,0,PeriodStr,0,0},  // .
  {text,   10,0,0,  0,0,0,MSecStr,  0,0},  // msecs
  {text,    0,0,0,  0,0,0,BlankLn,  0,0},
  {listend, 0,0,0,  0,0,0,BlankLn,  0,0}
};

face * registerDigital6() {
  face* f = (face*) malloc(sizeof(face));

  f->text = digital6List;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 6\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = initDigital6;
  f->uninit = deinitDigital6;
  f->draw = doDigital6;
  f->uses_knobs = 0;

  return f;
}

void initDigital6() {
  FastDraw=1;
}

void deinitDigital6() {
  FastDraw=0;
}

void doDigital6() {
  if(MSecs > 500) {
    digital6List[2].brightness = 1;
  } else {
    digital6List[2].brightness = 60;
  }
}

/****************************** Digital 7
 * 
 */
// 4 digit digital clock draw list
struct item time4ndsList[] = {
  {text,40,0,0,0,0,0,HrsStr,  0,0},  // hours
  {text,40,0,0,70,0,0,ColStr,  0,0},  // colon
  {text,40,0,0,100,0,0,MinStr,  0,0},  // mins
  {text,40,0,0,0,0,0,BlankLn, 0,0}, // next line
  {listend,0,0,0,0,0,0,BlankLn,0,0}
};

face * registerDigital7() {
  face* f = (face*) malloc(sizeof(face));

  f->text = time4ndsList;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 7\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = 0;
  f->uninit = 0;
  f->draw = 0;
  f->uses_knobs = 0;

  return f;
}

/****************************** Digital 8
 * 
 * 15:27
 * 
 * 33.123
 * 
 * Uses FastDraw for the extra strokes.
 */

// 4 digit digital clock draw list
struct item digital8List[] = {
  {text,   35,0,0,  0,3,9,HrsStr,  0,0},  // hours
  {text,   35,0,0, 60,0,0,ColStr,  0,0},  // colon
  {text,   35,0,0,100,3,9,MinStr,  0,0},  // mins
  {text,   35,0,0,  0,0,0,BlankLn, 0,0}, // next line
  {text,   25,0,0,  0,1,9,SecStr,  0,0},  // secs
  {text,   25,0,0, 60,1,9,PeriodStr, 0,0},  // .
  {text,   25,0,0,100,1,9,MSecStr, 0,0},  // msecs
  {text,   25,0,0,  0,0,0,BlankLn, 0,0},
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

face * registerDigital8() {
  face* f = (face*) malloc(sizeof(face));

  f->text = digital8List;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 8\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = initDigital8;
  f->uninit = deinitDigital8;
  f->draw = doDigital8;
  f->uses_knobs = 0;

  return f;
}

void initDigital8() {
  FastDraw=1;
}

void deinitDigital8() {
  FastDraw=0;
}

void doDigital8() {
  if(MSecs > 500) {
    digital8List[1].brightness = 1;
  } else {
    digital8List[1].brightness = 60;
  }
}

/****************************** Digital 9
 * 
 */

int digitial9digits[5][6] = {
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0}
};

char digitial9digitsStr[5][6][2] = {
  {"0", "0", "0", "0", "0", "0"},
  {"0", "0", "0", "0", "0", "0"},
  {"0", "0", "0", "0", "0", "0"},
  {"0", "0", "0", "0", "0", "0"},
  {"0", "0", "0", "0", "0", "0"}
};

 // Rolling-clock digital thingy...

int digital9PrevHrs;
int digital9PrevMin;
int digital9PrevSec;

char digital9PrevHrsStr[]  = "00";
char digital9PrevMinStr[]  = "00";
char digital9PrevSecStr[]  = "00";

int digital9PrevPrevHrs;
int digital9PrevPrevMin;
int digital9PrevPrevSec;

char digital9PrevPrevHrsStr[]  = "00";
char digital9PrevPrevMinStr[]  = "00";
char digital9PrevPrevSecStr[]  = "00";

int digital9NextHrs;
int digital9NextMin;
int digital9NextSec;

char digital9NextHrsStr[]  = "00";
char digital9NextMinStr[]  = "00";
char digital9NextSecStr[]  = "00";

int digital9NextNextHrs;
int digital9NextNextMin;
int digital9NextNextSec;

char digital9NextNextHrsStr[]  = "00";
char digital9NextNextMinStr[]  = "00";
char digital9NextNextSecStr[]  = "00";

// 4 digit digital clock draw list
struct item digital9List[] = {

  {text,    25,0,0,100,0,0,HrsStr,  0,0},  // hours
  {text,    25,0,0, 70,0,0,ColStr,  0,0},  // colon
  {text,    25,0,0,100,0,0,MinStr,  0,0},  // mins
  {text,    25,0,0,  0,0,0,ColStr,  0,0},  // colon
  {text,    25,0,0,  0,0,0,SecStr,  0,0},  // secs  
  {text,    25,0,0,  0,0,0,BlankLn, 0,0}, // next line

  {listend,  0,0,0,  0,0,0,BlankLn,0,0}
};

struct item digital9ListOuter[] = {
  {text,    25,0,0, 60,0,0,digital9PrevPrevHrsStr,  0,0},  // hours
  {text,    25,0,0, 60,0,0,ColStr,          0,0},  // colon
  {text,    25,0,0, 60,0,0,digital9PrevPrevMinStr,  0,0},  // mins
  {text,    25,0,0, 60,0,0,ColStr,          0,0},  // colon
  {text,    25,0,0, 60,0,0,digital9PrevPrevSecStr,  0,0},  // secs  
  {text,    25,0,0, 60,0,0,BlankLn,         0,0}, // next line
  {text,    25,0,0, 60,0,0,digital9PrevHrsStr,      0,0},  // hours
  {text,    25,0,0, 60,0,0,ColStr,          0,0},  // colon
  {text,    25,0,0, 60,0,0,digital9PrevMinStr,      0,0},  // mins
  {text,    25,0,0, 60,0,0,ColStr,          0,0},  // colon
  {text,    25,0,0, 60,0,0,digital9PrevSecStr,      0,0},  // secs  
  {text,    25,0,0, 60,0,0,BlankLn,         0,0}, // next line
  {text,    25,0,0,  0,0,0,BlankLn, 0,0}, // next line - skip the middle
  {text,    25,0,0, 60,0,0,digital9NextHrsStr,      0,0},  // hours
  {text,    25,0,0, 60,0,0,ColStr,          0,0},  // colon
  {text,    25,0,0, 60,0,0,digital9NextMinStr,      0,0},  // mins
  {text,    25,0,0, 60,0,0,ColStr,          0,0},  // colon
  {text,    25,0,0, 60,0,0,digital9NextSecStr,      0,0},  // secs  
  {text,    25,0,0, 60,0,0,BlankLn,         0,0}, // next line
  {text,    25,0,0, 60,0,0,digital9NextNextHrsStr,  0,0},  // hours
  {text,    25,0,0, 60,0,0,ColStr,          0,0},  // colon
  {text,    25,0,0, 60,0,0,digital9NextNextMinStr,  0,0},  // mins
  {text,    25,0,0, 60,0,0,ColStr,          0,0},  // colon
  {text,    25,0,0, 60,0,0,digital9NextNextSecStr,  0,0},  // secs  
  {text,    25,0,0, 60,0,0,BlankLn,         0,0}, // next line
  {listend,  0,0,0,  0,0,0,BlankLn,0,0}
};

struct item digital9col6[] = {
  {text,    25,0,0, 60,0,0,digital9PrevPrevSecStr,  0,0},  // secs  
  {text,    25,0,0, 60,0,0,BlankLn,         0,0}, // next line
  {text,    25,0,0, 60,0,0,digital9PrevSecStr,      0,0},  // secs  
  {text,    25,0,0, 60,0,0,BlankLn,         0,0}, // next line
  {text,    25,0,0,  0,0,0,BlankLn, 0,0}, // next line - skip the middle
  {text,    25,0,0, 60,0,0,digital9NextSecStr,      0,0},  // secs  
  {text,    25,0,0, 60,0,0,BlankLn,         0,0}, // next line
  {text,    25,0,0, 60,0,0,digital9NextNextSecStr,  0,0},  // secs  
  {text,    25,0,0, 60,0,0,BlankLn,         0,0}, // next line
  {listend,  0,0,0,  0,0,0,BlankLn,0,0}
};

face * registerDigital9() {
  face* f = (face*) malloc(sizeof(face));

  f->text = digital9List;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 9\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = 0;
  f->uninit = 0;
  f->draw = doDigital9;
  f->uses_knobs = 0;

  return f;
}

void doDigital9() {
/* digitial9digits
// 0  1  2  3  4  5 
  {0, 0, 0, 0, 0, 0}, // 0 prevprev
  {0, 0, 0, 0, 0, 0}, // 1 prev
  {0, 0, 0, 0, 0, 0}, // 2 now
  {0, 0, 0, 0, 0, 0}, // 3 next
  {0, 0, 0, 0, 0, 0}  // 4 nextnext
 */

  digitial9digits[0][0] = Hrs / 10 - 2;
  digitial9digits[0][1] = Hrs % 10 - 2;
  digitial9digits[0][2] = Mins / 10 - 2;
  digitial9digits[0][3] = Mins % 10 - 2;
  digitial9digits[0][4] = Secs / 10 - 2;
  digitial9digits[0][5] = Secs % 10 - 2;

  // propagate down through the array
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 6; j++) {
      if(i < 4) digitial9digits[i+1][j] = digitial9digits[i][j] + 1;

      if(j == 0) digitial9digits[i][j] = abs(digitial9digits[i][j] % 2);
      if(j == 1) digitial9digits[i][j] = abs(digitial9digits[i][j] % 10);
      if(j == 2) digitial9digits[i][j] = abs(digitial9digits[i][j] % 7);
      if(j == 3) digitial9digits[i][j] = abs(digitial9digits[i][j] % 10);
      if(j == 4) digitial9digits[i][j] = abs(digitial9digits[i][j] % 7);
      if(j == 5) digitial9digits[i][j] = abs(digitial9digits[i][j] % 10);
    }
  }
/*
  for(int i = 0; i < 5; i++) {
    Serial.printf("%d: %d %d %d %d %d %d\n", i, digitial9digits[i][0], digitial9digits[i][1], digitial9digits[i][2], digitial9digits[i][3], digitial9digits[i][4], digitial9digits[i][5]);
  }

  Serial.printf("\n");
*/

  Serial.printf("%02d:%02d:%02d\n", Hrs, Mins, Secs);
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 6; j++) {
      digitial9digitsStr[i][j][0] = digitial9digits[i][j] | '0' ;
    }
  }


  for(int i = 0; i < 5; i++) {
    Serial.printf("%d: %s %s %s %s %s %s\n", i, digitial9digitsStr[i][0], digitial9digitsStr[i][1], digitial9digitsStr[i][2], digitial9digitsStr[i][3], digitial9digitsStr[i][4], digitial9digitsStr[i][5]);
  }

  Serial.printf("\n--\n");
  
  digital9PrevHrs = Hrs - 1;
  if(digital9PrevHrs == -1)
    digital9PrevHrs = 23;
  digital9PrevPrevHrs = digital9PrevHrs - 1;
  if(digital9PrevPrevHrs == -1)
    digital9PrevPrevHrs = 23;

  digital9PrevMin = Mins - 1;
  if(digital9PrevMin == -1)
    digital9PrevMin = 23;
  digital9PrevPrevMin = digital9PrevMin - 1;
  if(digital9PrevPrevMin == -1)
    digital9PrevPrevMin = 23;

  digital9PrevSec = Secs - 1;
  if(digital9PrevSec == -1)
    digital9PrevSec = 59;
  digital9PrevPrevSec = digital9PrevSec - 1;
  if(digital9PrevPrevSec == -1)
    digital9PrevPrevSec = 59;

  digital9NextHrs = Hrs + 1;
  if(digital9NextHrs == 13)
    digital9NextHrs = 0;
  digital9NextNextHrs = digital9NextHrs + 1;
  if(digital9NextNextHrs == 13)
    digital9NextNextHrs = 0;

  digital9NextMin = Mins + 1;
  if(digital9NextMin == 13)
    digital9NextMin = 0;
  digital9NextNextMin = digital9NextMin + 1;
  if(digital9NextNextMin == 13)
    digital9NextNextMin = 0;

  digital9NextSec = Secs + 1;
  if(digital9NextSec == 60)
    digital9NextSec = 0;
  digital9NextNextSec = digital9NextSec + 1;
  if(digital9NextNextSec == 60)
    digital9NextNextSec = 0;

  digital9PrevHrsStr[0] = (digital9PrevHrs / 10) | '0';
  digital9PrevHrsStr[1] = (digital9PrevHrs % 10) | '0';
  digital9PrevPrevHrsStr[0] = (digital9PrevPrevHrs / 10) | '0';
  digital9PrevPrevHrsStr[1] = (digital9PrevPrevHrs % 10) | '0';

  digital9NextHrsStr[0] = (digital9NextHrs / 10) | '0';
  digital9NextHrsStr[1] = (digital9NextHrs % 10) | '0';
  digital9NextNextHrsStr[0] = (digital9NextNextHrs / 10) | '0';
  digital9NextNextHrsStr[1] = (digital9NextNextHrs % 10) | '0';

  digital9PrevMinStr[0] = (digital9PrevMin / 10) | '0';
  digital9PrevMinStr[1] = (digital9PrevMin % 10) | '0';
  digital9PrevPrevMinStr[0] = (digital9PrevPrevMin / 10) | '0';
  digital9PrevPrevMinStr[1] = (digital9PrevPrevMin % 10) | '0';

  digital9NextMinStr[0] = (digital9NextMin / 10) | '0';
  digital9NextMinStr[1] = (digital9NextMin % 10) | '0';
  digital9NextNextMinStr[0] = (digital9NextNextMin / 10) | '0';
  digital9NextNextMinStr[1] = (digital9NextNextMin % 10) | '0';
  
  digital9PrevSecStr[0] = (digital9PrevSec / 10) | '0';
  digital9PrevSecStr[1] = (digital9PrevSec % 10) | '0';
  digital9PrevPrevSecStr[0] = (digital9PrevPrevSec / 10) | '0';
  digital9PrevPrevSecStr[1] = (digital9PrevPrevSec % 10) | '0';

  digital9NextSecStr[0] = (digital9NextSec / 10) | '0';
  digital9NextSecStr[1] = (digital9NextSec % 10) | '0';
  digital9NextNextSecStr[0] = (digital9NextNextSec / 10) | '0';
  digital9NextNextSecStr[1] = (digital9NextNextSec % 10) | '0';

  FastDraw = 1;
  copyList(digital9ListOuter);
  Center(TheList);                // fill in the positions of each string in our copy
  DoAList(TheList);               // draw it on the screen
  FastDraw = 0;
}

/****************************** Digital 10
 * 
 */
// 4 digit digital clock draw list
struct item digital10List[] = {
// type, scale, func, font, brightness, shadow, shadow spacing, string, x, y
  {text,27,0,0,100,0,0,HrsStr, 0,0}, // 0 - hours
  {text,27,0,0,70,0,0,ColStr,  0,0}, // 1 - colon
  {text,27,0,0,100,0,0,MinStr, 0,0}, // 2 - mins
  {text,27,0,0,70,0,0,ColStr,  0,0}, // 3 - colon
  {text,27,0,0,100,0,0,SecStr, 0,0}, // 4 - sec
  {text,27,0,0,0,0,0,BlankLn,  0,0}, // next line
  {listend,0,0,0,0,0,0,BlankLn,0,0}
};

face * registerDigital10() {
  face* f = (face*) malloc(sizeof(face));

  f->text = digital10List;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Digital 10\n", -400, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = 0;
  f->uninit = 0;
  f->draw = doDigital10;
  f->uses_knobs = 0;

  return f;
}

void doDigital10() {
  digital10List[4].brightness = 100 - (MSecs / 10);
  digital10List[4].string = LastSecStr;

  copyList(digital10List);
  Center(TheList);                // fill in the positions of each string in our copy
  DoAList(TheList);               // draw it on the screen

  digital10List[4].brightness = MSecs / 10;
  digital10List[4].string = SecStr;

}

/****************************** Nixie
 * 
 * 15:27
 * 
 * Uses FastDraw for the extra strokes.
 */

int clock9bright = 40;

// 4 digit digital clock draw list
struct item nixieList[] = {
  {text,   35,0,0,100,1,9,HrsStr,  0,0},  // hours
  {text,   35,0,0, 60,0,0,SpaStr,  0,0},  // 1 - colon
  {text,   35,0,0,100,1,9,MinStr,  0,0},  // mins
  {text,   35,0,0,100,0,0,BlankLn, 0,0},
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList0[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"00 00\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList1[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"11 11\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList2[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"22 22\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList3[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"33 33\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList4[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"44 44\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList5[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"55 55\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList6[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"66 66\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList7[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"77 77\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList8[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"88 88\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

struct item nixieList9[] = {
  {text,   35,0,0, clock9bright,0,0,(char *)"99 99\n",  0,0},  // hours
  {listend, 0,0,0,  0,0,0,BlankLn, 0,0}
};

face * registerNixie() {
  face* f = (face*) malloc(sizeof(face));

  f->text = nixieList;
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Nixie\n", -300, -1200};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};
  f->init = initNixie;
  f->uninit = deinitNixie;
  f->draw = doNixie;
  f->uses_knobs = 0;

  return f;
}

void initNixie() {
  FastDraw=1;
}

void deinitNixie() {
  FastDraw=0;
  setBrightness(100);
}

void doNixie() {
  int frame_flicker = 2;

  if(frame%frame_flicker == 0) {
    copyList(nixieList0);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
    copyList(nixieList1);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
    copyList(nixieList2);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
    copyList(nixieList3);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
    copyList(nixieList4);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
  } else if(frame%frame_flicker == 1) {
    copyList(nixieList5);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
    copyList(nixieList6);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
    copyList(nixieList7);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
    copyList(nixieList8);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
    copyList(nixieList9);
    Center(TheList);                // fill in the positions of each string in our copy
    DoAList(TheList);               // draw it on the screen
  }
}

/****************************** Studio
 * 
 * Feb 3
 * 13:35
 *  59
 */

struct item studioList[] = {
  {text,16,0,0,0,0,0,MonthStr,0,0},  // months
  {text,16,0,0,0,0,0,SpaStr,  0,0},  // space
  {text,16,0,0,0,0,0,DayStr,  0,0},  // days
  {text,40,0,0,0,0,0,HrsStr,  0,0},  // hours
  {text,40,0,0,70,0,0,ColStr,  0,0},  // colon
  {text,40,0,0,100,0,0,MinStr,  0,0},  // mins
  {text,40,0,0,0,0,0,BlankLn, 0,0},  // next line
  {text,30,0,0,0,0,0,SecStr,  0,0},  // secs
  {text,20,0,0,0,0,0, BlankLn, 0,0},
  {listend,0,0,0,0,0,0,BlankLn, 0,0}
};
 
face * registerStudioClock() {
  face* f = (face*) malloc(sizeof(face));

  f->text = studioList;
  
  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, 0,(char*)"Studio\n", -350, -1300};
  f->title[1] = {listend, 0, 0, 0, 0,0, 0,BlankLn, 0, 0};

  f->init = 0;
  f->uninit = 0;
  f->draw = doSecFractionDots;
  f->uses_knobs = 0;

  return f;
}

void doSecFractionDots()
{
  static elapsedMillis currentMillis;
  static int lastSecond;

  // Always "draw" all dots to keep frame time consistent, just "mute" those after current time
  setBrightness(BRIGHTNESS_DEFAULT);

  for (uint32_t i = 0; i <= 100; i++) {
    if(i > currentMillis/10)
      setBrightness(0);

    drawRadialCircle(2700, 100, i, 30); 
  }

  if(lastSecond != Secs) {
    currentMillis = 0;
    lastSecond = Secs;
  }
  
  // Set brightness for text
  setBrightness(BRIGHTNESS_DEFAULT);
}

// ----------------------- Time string generator -----------------------

// makeTimeStrings fills in the time and date strings in RAM with the
// current time in ASCII. The month and weekday strings are set also.
void makeTimeStrings() {
  int hours, zon;  // temp storage for manipulation

//  Serial.printf("%s %s %s %s\n", LastMSecStr, MSecStr, LastSecStr, SecStr);

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

  snprintf(MSecStr, 4, "%3.3d", MSecs);

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
