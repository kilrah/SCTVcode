// original starfield code from https://github.com/jordanmack/arduino-starfield
// Hacked up by Audin Malmin.

//const int starCount = 256; // number of stars in the star field
//const int maxDepth = 128;   // maximum distance away for a star

const int starCount = 512; // number of stars in the star field
const int maxDepth = 48;   // maximum distance away for a star

// the star field - starCount stars represented as x, y and z co-ordinates
double stars[starCount][4];

void reset_stars() {
  randomSeed(millis());
  for (int i = 0; i < starCount; i++) {
    stars[i][0] = random(-25, 25);
    stars[i][1] = random(-25, 25);
    stars[i][2] = random(0, maxDepth);   // distance
    stars[i][3] = random(5)+1;           // "absolute magnitude"
  }
}

void doStars() {
  int origin_x = 1500;
  int origin_y = 1500;
  int screen_size = 1500*2;

  // Iterate through the stars reducing the z co-ordinate in order to move the star closer.
  for (int i = 0; i < starCount; ++i) {
    stars[i][2] -= 0.39;

    // if the star has moved past the screen (z < 0) reposition it far away
    // with random x and y positions.
    if (stars[i][2] <= 0) {
      stars[i][0] = random(-25, 25);
      stars[i][1] = random(-25, 25);
      stars[i][2] = maxDepth;
      stars[i][3] = random(5)+1;
    }

    // Convert the 3D coordinates to 2D using perspective projection.
    double k = screen_size / stars[i][2];
    int x = stars[i][0] * k + origin_x;
    int y = stars[i][1] * k + origin_y;

    // Draw the star (if it is visible in the screen).
    // Distant stars are smaller than closer stars.
    if ((0 <= x && x < screen_size) && (0 <= y && y < screen_size)) {
      int size = (1 - stars[i][2] / maxDepth) * 8;

//      if (i == 1)
//        Serial.printf("%4d %4d %4d\n", x, y, size);

      for(int j = stars[i][3]; j>0; j--) {
        drawACircle(x - origin_x, y - origin_y, (size+1)*3);    
      }
    }
  }
}
