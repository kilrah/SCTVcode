// This face reads through memory and plots what it finds on the screen as a spiral.
// It walks along until reaching the 256KB point and then loops back to 0.

void doSpiral() {
  static int offset = 0;
  byte* b = 0;

  // go to the start point with beam off
  analogWrite(XDACPin, midDAC);
  analogWrite(YDACPin, midDAC);

  // wait for the beam to reach the start point
  delayMicroseconds(10);
  digitalWrite(BlankPin, HIGH);        // start making photons
  delayMicroseconds(glowDelay);        // wait for glow to start

  //  for (int t = 0; t < 40000; t++) {
  for (int t = 40000; t >= 0; t--) {
    int x = ((costab[(t) % nsteps] * (t / 30)) >> 16) + midDAC + xPos;
    int y = ((sintab[(t) % nsteps] * (t / 30)) >> 16) + midDAC + yPos;

    if (b[t + offset] > 128)
      digitalWrite(BlankPin, HIGH);
    else
      digitalWrite(BlankPin, LOW);

    analogWrite(XDACPin, x);
    analogWrite(YDACPin, y);

    if (t == 0) {
      offset += 10;
      if (offset > 256 * 1024)
        offset = 0;
    }
  }

  delayMicroseconds(glowDelay);        // wait for glow to start
  digitalWrite(BlankPin, LOW);         // done, hide dot now
}
