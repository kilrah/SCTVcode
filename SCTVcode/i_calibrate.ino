void doCalibrateCircle() {
  for (int i = 100; i < 3000; i += 200) {
    drawACircle(0, 0, i);
    DoEnc();          // polled mode I/O, so we need to do it many times
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
/*
  {text,10,0,0,numbers,  0,0},
  {text,10,0,0,letters,  0,0},
  {text,10,0,1,numbers,  0,0},
  {text,10,0,1,letters,  0,0},
  {text,10,0,2,numbers,  0,0},
  {text,10,0,2,letters,  0,0},
  {text,10,0,3,numbers,  0,0},
  {text,10,0,3,letters,  0,0},
  */  
  {text,10,0,3,chars1,  0,0},
  {text,10,0,3,chars2,  0,0},
  {text,10,0,3,chars3,  0,0},
  {text,10,0,3,chars4,  0,0},
  {text,10,0,3,chars5,  0,0},
  {listend,0,0,0,BlankLn,0,0}
};
/*
void doCalibrateFont() {
 if(frame%4 == 0)
    lineStride = 1;
  else
    lineStride = 4;
}
*/
