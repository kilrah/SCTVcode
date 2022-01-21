// ------------------------ Menus --------------------------

// Parameters that are modified in menus
const int ModCen   = 1;
const int ModYrs   = 2;
const int ModMon   = 3;
const int ModDay   = 4;
const int ModHrs   = 5;
const int ModMin   = 6;
const int ModSec   = 7;
const int ModZone  = 8;
const int ModZmin  = 9;
const int ModHrSel = 10;
const int ModDST   = 11;
const int ModHz    = 12;
// const int ModMenu  = 13;
const int ModClk   = 14;

// Menu fields that get worked on
const int TimMCod = 15;
const int LocMCod = 16;
const int MainCod = 19;
const int TimDCod = 20;
const int MainDCod = 21;

// The main menu
char setTimDat[] = "Set Time & Date\n";
char setLocale[] = "Set Locale\n";
char setFLW[] = "Set FLW\n";
struct item mainMenu[] = {
  {menu, 10, MainDCod, 0, DoneStr,  0, 0},
  {menu, 10, TimMCod, 0, setTimDat , 0, 0},
  {menu, 10, LocMCod, 0, setLocale, 0, 0},
  //{menu,10,FlwMCod,0,setFLW,    0,0},   // not used yet
  {listend, 0, 0, 0, BlankLn, 0, 0}
};

// The time setting menu
struct item timeMenu[] = {
  {menu , 10, TimDCod, 0, DoneStr, 0, 0},
  {field, 10, ModHrs, 0, HrsStr,  0, 0},
  {text , 10, 0,      0, ColStr,  0, 0},
  {field, 10, ModMin, 0, MinStr,  0, 0},
  {text , 10, 0,      0, ColStr,  0, 0},
  {field, 10, ModSec, 0, SecStr,  0, 0},
  {field, 10, ModCen, 0, CenStr,  0, 0}, // just for completeness
  {field, 10, ModYrs, 0, YrsStr,  0, 0},
  {text , 10, 0,      0, DashStr, 0, 0},
  {field, 10, ModMon, 0, MonthStr, 0, 0},
  {text , 10, 0,      0, DashStr, 0, 0},
  {field, 10, ModDay, 0, DayStr,  0, 0},
  {listend, 0, 0, 0, BlankLn, 0, 0}
};

// The locale setting menu does DST, time zone, 12/24 hour select
char zoneGMT[] = "Zone: GMT";
char hourMode[] = " hour mode\n";
char DSTlin[] = "DST ";
char Hzlin1[] = "Mains: ";
char Hzlin2[] = " Hertz\n";
struct item locMenu[] = {
  //  {text ,10,0,       BlankLn, 0,0},
  {menu , 10, MainCod, 0, DoneStr, 0, 0},
  {text , 10, 0,       0, zoneGMT, 0, 0}, // Start of time zone text
  {field, 10, ModZone, 0, ZoneStr, 0, 0}, // timezone sign and hours
  {text , 10, 0,       0, ColStr,  0, 0},
  {field, 10, ModZmin, 0, ZMinStr, 0, 0}, // timezone minutes
  {text , 10, 0,       0, BlankLn, 0, 0},
  {field, 10, ModHrSel, 0, HrSelStr, 0, 0}, // 12 or 24
  {text , 10, 0,       0, hourMode, 0, 0}, // hour mode
  {text , 10, 0,       0, DSTlin,   0, 0}, // Daylight string
  {field, 10, ModDST,  0, DSTStr,   0, 0}, // gets "on" or "off"
  {text , 10, 0,       0, Hzlin1,   0, 0}, // Hertz string
  {field, 10, ModHz,   0, HzStr,    0, 0}, // gets "50" or "60"
  {text , 10, 0,       0, Hzlin2,   0, 0}, // Hertz string
  {listend, 0, 0, 0, BlankLn, 0, 0}
};


// --------------------------- Clock options -------------------------

// This is the clock display option list

// list of clock face draw lists
item * ClkList[] = {
  faceList,             // 0  - analog clock face
  clock2List,           // 1  - another analog clock face
  clock3List,           // 2  - an analog clock face with a 3d cube in it for some reason
  0,                    // 3  - spaceclock
  time4nList,           // 4  - 4 digit digital clock
  time6nList,           // 5  - 6 digit digital clock
  time4dList,           // 6  - 4 digit digital clock with date
  time6dList,           // 7  - 6 digit digital clock with date
  haikuList,            // 8  - some poetry at random
  pongList,             // 9  - play Pong, special code is run for this
  tetrisList,           // 10 - play Tetris
  0,                    // 11 - 3d cube
  0,                    // 12 - stars
  0,                    // 13 - spiral
  0,                    // 14 - spiral2
  0,                    // 15 - Calabration - circles
  0,                    // 16 - Calibration - square
  calibrateFontList,    // 17 -
  calibrateBrightnessList, // 18 - Calibration - brightness
  0,                    // 18 - tempest clock - TBD
  splashList,           // 19 - splash screen vanishes when knob touched
  //   flwList,     // four letter words at random
  //   timefList,   // 6 digit digital clock with full date, day
  0
};

struct item clockTitles[][2] = {  //  Title string       X     Y    - If X is 0 then the string will be in the center of the display
  { {text, 10, 0, 0, (char*)"Roman\n",                 -300, -600}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 0
  { {text, 10, 0, 0, (char*)"Ticks\n",                 -250, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 1
  { {text, 10, 0, 0, (char*)"Cube Clock\n",            -500, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 2
  { {text, 10, 0, 0, (char*)"Space Clock\n",           -600, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 3
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 4
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 5
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 6
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 7
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 8
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 9
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 10
  { {text, 10, 0, 0, (char*)"3D Cube\n",               0, 0}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 11
  { {text, 10, 0, 0, (char*)"Starfield\n",             0, 0}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 12
  { {text, 10, 0, 0, (char*)"Memory Spiral - Bits\n",  0, 0}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 13
  { {text, 10, 0, 0, (char*)"Memory Spiral - Bytes\n", 0, 0}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 14
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 15
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 16
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 17
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 18
  { {text, 10, 0, 0, (char*)"\n",                      1, -1000}, {listend, 0, 0, 0, BlankLn, 0, 0} }, // 19
};

int clockTitlePosY[] = {
  0,  // 0
  0,  // 1
  0,  // 2
  0,  // 3
  0,  // 4
  0,  // 5
  0,  // 6
  0,  // 7
  0,  // 8
  0,  // 9
  0,  // 10
  0,  // 11
  0,  // 12
  0,  // 13
  0,  // 14
  0,  // 15
  0,  // 16
  0,  // 17
  0,
  0,  // 18
  0,  // 19
  0
};

// list of function pointers for each face that needs to initialize things when it is selected
void (*customInitList[])(void) = {
  0,                // 0
  0,                // 1
  0,                // 2
  reset_spaceclock, // 3
  0,                // 4
  0,                // 5
  0,                // 6
  0,                // 7
  0,                // 8
  reset_pong,       // 9
  reset_tetris,     // 10
  reset_cube,       // 11
  reset_stars,      // 12
  0,                // 13
  0,                // 14
  0,                // 15
  0,                // 16
  0,                // 17
  0,
  0,                // 18
  0,                // 19
  0
};

// list of function pointers for each face that needs to draw its own stuff
void (*customDrawList[])(void) = {
  DrawClk,            // 0
  clock2Draw,         // 1
  clock3Draw,         // 2
  spaceclockDraw,     // 3
  0,                  // 4
  0,                  // 5
  0,                  // 6
  0,                  // 7
  0,                  // 8
  doPong,             // 9
  drawTetris,         // 10
  doCube,             // 11
  doStars,            // 12
  doSpiral,           // 13
  doSpiral2,          // 14
  doCalibrateCircle,  // 15
  doCalibrateSquare,  // 16
  doCalibrateFont,    // 17
  doCalibrateBrightness, // 18
  doTempest,          // 18
  0,                  // 19
  0
};

// list of bools signifying whether a face makes direct use of the position pots or not.  (usually games)
bool customKnobsList[] = {
  0,  // 0
  0,  // 1
  0,  // 2
  0,  // 3
  0,  // 4
  0,  // 5
  0,  // 6
  0,  // 7
  0,  // 8
  1,  // 9
  1,  // 10
  0,  // 11
  0,  // 12
  0,  // 13
  0,  // 14
  0,  // 15
  0,  // 16
  0,  // 17
  0,  // 18
  0,
  0,  // 19
  0
};

const int NClks = sizeof(ClkList) / sizeof(ClkList[0]) - 2;  // number of clock faces to choose from (splash doesn't count)

// -------------------------- Menu navigation -----------------------

// Do the thing asked for in a menu item
void DoMenuFunc(int func) {
  switch (func) {
    case TimMCod:
      whichList = timeMenu;
      HotItem = 1;
      break;
    case LocMCod:
      whichList = locMenu;
      HotItem = 1;
      break;
    case MainCod:
      whichList = mainMenu;
      HotItem = 1;
      break;
    case TimDCod:  // exit the time setting menu
      //      SetRand();                // make FLW fresh
      whichList = mainMenu;
      HotItem = 1;
      break;
    case MainDCod:
      whichList = ClkList[theClock];     // point to the clock drawlist we are displaying now
      HotItem = 0;
      InMenu = false;
      break;
    default:   // don't do anything!
      break;
  }
}


// Do a field modification, rolling over to other end on limits
// These are chars for now, which are unsigned, so the subtractions are weird.
// These maybe ought to be ints.
void DoModFunc(int func) {
  switch (func) {
    case ModCen:
      Century = Century + EncDir;
      if (Century > 99) Century -= 100;
      if (Century < 0)   Century += 100;
      writeRTClocale();   // save the updated time into the DS3232
      break;

    case ModYrs:
      Years = Years + EncDir;
      if (Years > 99) Years -= 100;
      if (Years < 0)  Years += 100;
      writeRTCtime();   // save the updated time into the DS3232
      break;

    case ModMon:
      Mons = Mons + EncDir;
      if (Mons > 12) Mons -= 12;
      if (Mons < 1)  Mons += 12;
      writeRTCtime();   // save the updated time into the DS3232
      break;

    case ModDay:
      Days = Days + EncDir;
      if (Days > 31) Days -= 31;
      if (Days < 1)  Days += 31;
      writeRTCtime();   // save the updated time into the DS3232
      break;

    case ModHrs:
      Hrs = Hrs + EncDir;
      if (Hrs > 23) Hrs -= 24;
      if (Hrs < 0)  Hrs += 24;
      writeRTCtime();   // save the updated time into the DS3232
      break;

    case ModMin:
      Mins = Mins + EncDir;
      if (Mins > 59) Mins -= 60;
      if (Mins < 0)  Mins += 60;
      writeRTCtime();   // save the updated time into the DS3232
      break;

    case ModSec:
      Secs = Secs + EncDir;
      if (Secs > 59) Secs -= 60;
      if (Secs < 0)  Secs += 60;
      writeRTCtime();   // save the updated time into the DS3232
      break;

    case ModZone:
      Zone = Zone + EncDir;
      if (Zone > 11) Zone -= 24;   // time zones from GMT-12 to GMT+11
      if (Zone < -12) Zone += 24;
      writeRTClocale();   // save the updated time into the DS3232
      break;

    case ModZmin:
      ZMins = ZMins + EncDir;
      if (ZMins > 45) ZMins -= 60;    // time zone minutes change by 15 minutes
      if (ZMins < 0) ZMins += 60;
      writeRTClocale();   // save the updated time into the DS3232
      break;

    case ModHrSel:
      if (Hr12 == 0) Hr12 = 1;        // toggle 12 hour vs 24 hour mode
      else Hr12 = 0;
      writeRTClocale();   // save the updated time into the DS3232
      break;

    case ModDST:
      if (DST == 0) DST = 1;        // toggle daylight savings enable
      else DST = 0;
      writeRTClocale();   // save the updated time into the DS3232
      break;

    case ModHz:
      if (Hertz == 50)    // switch between 50 and 60 Hz display rate
      {
        Hertz = 60;
        JifTick = 5;
        HalfSec = 30;
      }
      else
      {
        Hertz = 50;
        JifTick = 6;
        HalfSec = 25;
      }
      writeRTClocale();   // save the updated time into the DS3232
      break;
    default:   // don't do anything!
      break;
  }
}

// DoMenus acts on the encoder to change which menu we're in or
// adjust a parameter setting. It uses the information placed in
// the menu variables by DoAList.
// It changes TheList and HotItem and the flag InParam.
// When it needs to process a parameter or menu item, it calls MenuCod.

// Logic:
// If in a parameter field, enter parameter-changing mode by pushing button
// If changing parameter and button pushed, goto next field
// If in a menu item and encoder moves, move up or down to next item
// If in a menu item and button pushed, execute its menu code
// If not in a menu at all and encoder moves, change display mode

// move to next or previous highlighted item in menu
void ModMenu() {
  HotItem = HotItem + EncDir;
  if (HotItem > NItems) HotItem -= NItems;  // select next menu item
  if (HotItem < 1) HotItem += NItems;
}

// Navigate the menus via encoder commands
void DoMenus()
{
  if (InField)   // processing a parameter field
  {
    if (EncDir)  // knob turned,
    {
      if (InParam)
        DoModFunc(MenuCod);  // modify parameter value for this field
      else
        ModMenu();   // move to next field
    }
    else if (pushed) //button pushed in parameter field
    {
      if (InParam)   // while editing parameter, move to next parameter
      {
        HotItem++;
        if (HotItem > NItems) HotItem -= NItems;  // select next menu item
      }
      else
        InParam = true;  // enter parameter-changing mode, blinks field
    }    // EncDir
  }
  else  // not InField, check for menu navigation
  {
    if (InMenu)
    {
      if (pushed) // select a menu if button pushed
        DoMenuFunc(MenuCod);
      else
      {
        if (EncDir)  // move to next/previous selection when knob turned
          ModMenu();
      }
    }
  }
}
