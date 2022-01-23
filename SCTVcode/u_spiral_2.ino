// This face reads through memory and plots what it finds on the screen as a spiral.
// It walks along until reaching the 256KB point and then loops back to 0.

face * registerSpiral2() {
  face* f = (face*) malloc(sizeof(face));

  f->text = 0;

  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, (char*)"Memory Spiral - Bytes\n", 0, 0};
  f->title[1] = {listend, 0, 0, 0, BlankLn, 0, 0};

  f->reset = 0;
  f->draw = doSpiral2;
  f->uses_knobs = 0;

  return f;
}

void doSpiral2() {
  static int offset = 0;
  byte* b = 0; // beginning of memory...

  // go to the start point with beam off
  analogWrite(XDACPin, midDAC);
  analogWrite(YDACPin, midDAC);

//  for (int t = 40000; t >= 0; t--) {
  for (int t = 0; t < 40000; t+=2) {
    int x = ((costab[(t) % nsteps] * (t / 30)) >> 16) + midDAC + xPos;
    int y = ((sintab[(t) % nsteps] * (t / 30)) >> 16) + midDAC + yPos;

    setBrightness(100/(float)256*b[t/2+offset]);
    analogWrite(BlankPin, Brightness);
    analogWrite(XDACPin, x);
    analogWrite(YDACPin, y);
  }

  offset += 20;
  if (offset > 256 * 1024)
    offset = 0;

  analogWrite(BlankPin, 0);  // done, hide dot now
}
