struct item calibrateCircleList[] = {
  {listend, 0, 0, BlankLn, 0, 0}
};

void doCalibrateCircle() {
  for (int i = 100; i < 2700; i += 100) {
    drawACircle(0, 0, i);
    DoEnc();          // polled mode I/O, so we need to do it many times
  }
}

struct item calibrateSquareList[] = {
  {listend, 0, 0, BlankLn, 0, 0}
};

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

struct item calibrateFontList[] = {
  {text,16,0,numbers,  0,0},
  {text,16,0,numbers,  0,0},
  {text,16,0,numbers,  0,0},
  {text,16,0,numbers,  0,0},
  {listend,0,0,BlankLn,0,0}
};