// original starfield code from https://github.com/jordanmack/arduino-starfield
// Hacked up by Audin Malmin.

//const int starCount = 256; // number of stars in the star field
//const int maxDepth = 128;   // maximum distance away for a star

//const int starCount = 512; // number of stars in the star field
//const int maxDepth = 48;   // maximum distance away for a star
const int starCount = 512; // number of stars in the star field
const int maxDepth = 72;   // maximum distance away for a star

int usedStarCount = 512;

const float magnitudeRange = 25;

// the star field - starCount stars represented as x, y and z co-ordinates
double stars[starCount][4];

face * registerStars() {
  face* f = (face*) malloc(sizeof(face));

  f->text = 0;

  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, (char*)"Stars\n",                 -300,  -600};
  f->title[1] = {listend, 0, 0, 0, BlankLn, 0, 0};

  f->reset = reset_stars;
  f->draw = doStars;
  f->uses_knobs = 0;

  return f;
}

void set_star_count(int c) {  // Reduce to increase performance.
  usedStarCount = c;
}

void reset_stars() {
  usedStarCount = starCount;

  randomSeed(millis());
  for (int i = 0; i < starCount; i++) {
    stars[i][0] = random(-25, 25);
    stars[i][1] = random(-25, 25);
    stars[i][2] = random(0, maxDepth);   // distance
    stars[i][3] = random(magnitudeRange+1);           // "absolute magnitude"
  }
}

void doStars() {
  int origin_x = 1500;
  int origin_y = 1500;
  int screen_size = 1500*2;

  // Iterate through the stars reducing the z co-ordinate in order to move the star closer.
  for (int i = 0; i < usedStarCount; i++) {
    stars[i][2] -= 0.39;

    // if the star has moved past the screen (z < 0) reposition it far away
    // with random x and y positions.
    if (stars[i][2] <= 0) {
      stars[i][0] = random(-25, 25);
      stars[i][1] = random(-25, 25);
      stars[i][2] = maxDepth;
      stars[i][3] = random(magnitudeRange+1);
    }

    // Convert the 3D coordinates to 2D using perspective projection.
    double k = screen_size / stars[i][2];
    int x = stars[i][0] * k + origin_x;
    int y = stars[i][1] * k + origin_y;

    // Draw the star (if it is visible in the screen).
    // Distant stars are smaller than closer stars.
    if ((0 <= x && x < screen_size) && (0 <= y && y < screen_size)) {
      int size = (1 - stars[i][2] / maxDepth) * 8;

      setBrightness(stars[i][3] * 4);
      drawACircle(x - origin_x, y - origin_y, (size+1)*3, 6, 13);
    }
  }

  setBrightness(BRIGHTNESS_DEFAULT);
}
