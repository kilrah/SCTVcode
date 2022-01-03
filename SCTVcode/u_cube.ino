// Cube from https://github.com/OpenHDZ/Arduino-experimentation/blob/master/cube_gfx.ino
// Hacked up by Audin Malmin.

float zOff = 75;
float xOff = 0;
float yOff = 0;
float cSize = 25;
float view_plane = 32;
float scale = 60.0;
int xshift = 0;
int yshift = 0;

float cube3d[8][3] = {
  {xOff - cSize, yOff + cSize, zOff - cSize},
  {xOff + cSize, yOff + cSize, zOff - cSize},
  {xOff - cSize, yOff - cSize, zOff - cSize},
  {xOff + cSize, yOff - cSize, zOff - cSize},
  {xOff - cSize, yOff + cSize, zOff + cSize},
  {xOff + cSize, yOff + cSize, zOff + cSize},
  {xOff - cSize, yOff - cSize, zOff + cSize},
  {xOff + cSize, yOff - cSize, zOff + cSize}
};

void reset_cube() {
    setCubeSize(0, 0, 75, 25, 32, 60, 0, 0);
}

// setCubeSize(0, 0, 75, 25, 32, 60);
void setCubeSize(float xo, float yo, float zo, float cs, float vp, float s, int xs, int ys) {
  xOff = xo;
  yOff = yo;
  zOff = zo;
  cSize = cs;
  view_plane = vp;
  scale = s;
  xshift = xs;
  yshift = ys;
}

void doCube() {
  static int a=0;
  static int b=1;
  static int c=2;

  int cube2d[8][2];

  if((a==0 && b==0 && c==0) || frame%500==0) {
    switch(random(3)) {
      case 0:
        a=random(7)-3;
        break;
      case 1:
        b=random(7)-3;
        break;
      case 2:
        c=random(7)-3;
    }
  }

  xrotate(0.01F*a);
  yrotate(0.01F*b);
  zrotate(0.01F*c);

  for(byte i = 0; i < 8; i++) {
    cube2d[i][0] = (cube3d[i][0] * view_plane / cube3d[i][2]) * scale + xshift;
    cube2d[i][1] = (cube3d[i][1] * view_plane / cube3d[i][2]) * scale + yshift;
  }

  drawALine(cube2d[0][0],cube2d[0][1],cube2d[1][0],cube2d[1][1]);
  drawALine(cube2d[0][0],cube2d[0][1],cube2d[2][0],cube2d[2][1]);
  drawALine(cube2d[0][0],cube2d[0][1],cube2d[4][0],cube2d[4][1]);
  drawALine(cube2d[1][0],cube2d[1][1],cube2d[5][0],cube2d[5][1]);
  drawALine(cube2d[1][0],cube2d[1][1],cube2d[3][0],cube2d[3][1]);
  drawALine(cube2d[2][0],cube2d[2][1],cube2d[6][0],cube2d[6][1]);
  drawALine(cube2d[2][0],cube2d[2][1],cube2d[3][0],cube2d[3][1]);
  drawALine(cube2d[4][0],cube2d[4][1],cube2d[6][0],cube2d[6][1]);
  drawALine(cube2d[4][0],cube2d[4][1],cube2d[5][0],cube2d[5][1]);
  drawALine(cube2d[7][0],cube2d[7][1],cube2d[6][0],cube2d[6][1]);
  drawALine(cube2d[7][0],cube2d[7][1],cube2d[3][0],cube2d[3][1]);
  drawALine(cube2d[7][0],cube2d[7][1],cube2d[5][0],cube2d[5][1]);
}

void zrotate(float q) {
  float tx,ty,temp;
  for(byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    ty = cube3d[i][1] - yOff;
    temp = tx * cos(q) - ty * sin(q);
    ty = tx * sin(q) + ty * cos(q);
    tx = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][1] = ty + yOff;
  }
}

void yrotate(float q) {
  float tx,tz,temp;
  for(byte i = 0; i < 8; i++) {
    tx = cube3d[i][0] - xOff;
    tz = cube3d[i][2] - zOff;
    temp = tz * cos(q) - tx * sin(q);
    tx = tz * sin(q) + tx * cos(q);
    tz = temp;
    cube3d[i][0] = tx + xOff;
    cube3d[i][2] = tz + zOff;
  }
}

void xrotate(float q) {
  float ty,tz,temp;
  for(byte i = 0; i < 8; i++) {
    ty = cube3d[i][1] - yOff;
    tz = cube3d[i][2] - zOff;
    temp = ty * cos(q) - tz * sin(q);
    tz = ty * sin(q) + tz * cos(q);
    ty = temp;
    cube3d[i][1] = ty + yOff;
    cube3d[i][2] = tz + zOff;
  }
}
