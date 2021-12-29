// Cube from https://github.com/OpenHDZ/Arduino-experimentation/blob/master/cube_gfx.ino
// Hacked up by Audin Malmin.

char cubeStr[] = "A Cube\n";

struct item cubeList[] = {
//  {text,6,0,0,cubeStr, 0,0},
  {listend, 0, 0, 0, BlankLn, 0, 0}
};

float zOff = 75;
float xOff = 0;
float yOff = 0;
float cSize = 25;
float view_plane = 32;

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
int cube2d[8][2];
static int r=-1;
static int a=0;
static int b=0;
static int c=0;

void doCube() {
  if(r == -1 || frame%500==0) {
    r=random(5);
    a=random(3)+1;
    b=random(3)+1;
    c=random(3)+1;
  }
  switch(r) {
    case 0:
      xrotate(0.01F*a);
      yrotate(0.01F*b);
      zrotate(0.01F*c);
      break;
    case 1:
      yrotate(0.01F*a);
      break;
    case 2:
      zrotate(0.01F*a);
      break;
    case 3:
      xrotate(0.01F*b);
      zrotate(0.02F*c);
      break;
    case 4:
      xrotate(0.01F*a);
      yrotate(0.02F*b);
    break;
  }

  //calculate 2d points
  for(byte i = 0; i < 8; i++) {
    cube2d[i][0] = (cube3d[i][0] * view_plane / cube3d[i][2]) * 60.0;
    cube2d[i][1] = (cube3d[i][1] * view_plane / cube3d[i][2]) * 60.0;
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
