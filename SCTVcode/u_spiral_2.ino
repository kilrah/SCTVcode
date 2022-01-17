// This face reads through memory and plots what it finds on the screen as a spiral.
// It walks along until reaching the 256KB point and then loops back to 0.

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

    analogWrite(BlankPin, (HighestBrightness-LowBrightness)/256 * b[t/2+offset] + LowBrightness);

    analogWrite(XDACPin, x);
    analogWrite(YDACPin, y);
  }

  offset += 20;
  if (offset > 256 * 1024)
    offset = 0;

  analogWrite(BlankPin, 0);  // done, hide dot now
}
