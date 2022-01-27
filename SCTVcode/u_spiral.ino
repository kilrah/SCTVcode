// This face reads through memory and plots what it finds on the screen as a spiral.
// It walks along until reaching the 256KB point and then loops back to 0.
/*
  byte wowie[80*1024];

void reset_spiral() {

  for(int i =0; i < 80*1024; i++) {
    wowie[i] = 0;
  }

  if(wowie[2])
    ;
}
*/

face * registerSpiral1() {
  face* f = (face*) malloc(sizeof(face));

  f->text = 0;

  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0, (char*)"Memory Spiral - Bits\n", 0, 0};
  f->title[1] = {listend, 0, 0, 0, 0,0, BlankLn, 0, 0};

  f->reset = 0;
  f->draw = doSpiral1;
  f->uses_knobs = 0;

  return f;
}

void doSpiral1() {
  static int offset = 10*1024;
  byte* b = 0;

  byte current=0;
  
  // go to the start point with beam off
  analogWrite(XDACPin, midDAC);
  analogWrite(YDACPin, midDAC);

  // wait for the beam to reach the start point
  delayMicroseconds(10);
  digitalWrite(BlankPin, HIGH);
  delayMicroseconds(glowDelay);        // wait for glow to start

    for (int t = 0; t < 40000; t+=8) {
      current = b[t/8 + offset];
      
      for(int tt = 0; tt < 8; tt++) {
        int x = ((costab[(t+tt) % nsteps] * ((t+tt) / 30)) >> 16) + midDAC + xPos + XSaver;
        int y = ((sintab[(t+tt) % nsteps] * ((t+tt) / 30)) >> 16) + midDAC + yPos + YSaver;
  
//        Serial.printf("%5d %5d %8d %2X %2x %2x\n", x, y, t/8, current, current & 0x01, current >>1);
  
        if (current & 0x01)
          digitalWrite(BlankPin, HIGH);
        else
          digitalWrite(BlankPin, LOW);

        current = current >> 1;

  
//        analogWriteDAC0(x);
//        analogWriteDAC1(y);
        analogWrite(XDACPin, x);  
        analogWrite(YDACPin, y);
      }
    
      if (t == 0) {
        offset += 32;
        if (offset > 256 * 1024)
          offset = 0;
      }
  }

  delayMicroseconds(glowDelay);        // wait for glow to start
  digitalWrite(BlankPin, LOW);
}
