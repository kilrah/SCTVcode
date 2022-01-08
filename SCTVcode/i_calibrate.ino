void doCalibrateCircle() {
  for (int i = 100; i < 3000; i += 200) {
    drawACircle(0, 0, i);
  }
}

void doCalibrateSquare() {
// xs ys xe ye 
  drawALine(-1250, 1250, 1250, 1250);
  drawALine(-1250, 0, 1250, 0);
  drawALine(-1250, -1250, 1250, -1250);

  drawALine(-1250, -1250, -1250, 1250);
  drawALine(0, -1250, 0, 1250);
  drawALine(1250, -1250, 1250, 1250);

  drawALine(-1250, -1250, 1250, 1250);
  drawALine(1250, -1250, -1250, 1250);
}

char numbers[] = "0123456789\n";
char letters[] = "aAbBcCdDeEfFgGhHiI\n";
char LETTERS[] = "ABCDEFGHIJFG\n";

char chars1[] = 
"!\"`$%&'()*+,-./\n";
char chars2[] = 
"0123456789:;<=>?@\n";
char chars3[] = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
char chars4[] = 
"abcdefghijklmnopqrstuvwxyz\n";
char chars5[] =
"[\\]^_`{|}~\n";


struct item calibrateFontList[] = {
  {text,10,0,0,chars1,  0,0},
  {text,10,0,0,chars2,  0,0},
  {text,10,0,0,chars3,  0,0},
  {text,10,0,0,chars4,  0,0},
  {text,10,0,0,chars5,  0,0},
  {listend,0,0,0,BlankLn,0,0}
};

void doCalibrateFont() {
  static int f = 0;
  static int count = 1;

  if(count++%100 == 0) {
    f = (f+1) % 5;

    calibrateFontList[0].font = f;
    calibrateFontList[1].font = f;
    calibrateFontList[2].font = f;
    calibrateFontList[3].font = f;
    calibrateFontList[4].font = f;
  }
}
