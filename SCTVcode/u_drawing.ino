
face * registerDrawing() {
  face* f = (face*) malloc(sizeof(face));

  f->text = 0;

  f->title =  (item*) malloc(sizeof(item) * 2);
  f->title[0] = {text, 10, 0, 0, 0,0,0, (char*)"Viking\n", -300, 1000};
  f->title[1] = {listend, 0, 0, 0, 0,0,0, BlankLn, 0, 0};

  f->init = 0;
  f->uninit = 0;
  f->draw = doDrawing;
  f->uses_knobs = 0;

  return f;
}

short wowie5[][1000][2] = {
  {
    { 333, 492 },
    { 267, 480 },
    { 322, 462 },
    { 319, 452 },
    { 353, 532 },
    { 292, 586 },
    { 234, 526 },
    { 218, 480 },
    { 257, 496 },
    { 273, 571 },
    { 346, 541 },
    { 286, 529 },
    { 326, 516 },
    { 359, 517 },
    { 335, 410 },
    { 337, 414 },
    { 276, 418 },
    { 344, 391 },
    { 358, 386 },
    { 219, 380 },
    { 414, 331 },
    { 332, 371 },
    { 232, 369 },
    { 182, 326 },
    { 256, 365 },
    { 356, 361 },
    { 464, 311 },
    { 518, 240 },
    { 535, 143 },
    { 513, 46 },
    { 488, 81 },
    { 474, 176 },
    { 400, 207 },
    { 464, 177 },
    { 483, 84 },
    { 507, 30 },
    { 541, 122 },
    { 535, 222 },
    { 474, 294 },
    { 103, 283 },
    { 52, 199 },
    { 35, 102 },
    { 82, 49 },
    { 96, 148 },
    { 162, 189 },
    { 238, 172 },
    { 335, 166 },
    { 402, 237 },
    { 344, 179 },
    { 247, 177 },
    { 167, 206 },
    { 96, 168 },
    { 76, 71 },
    { 43, 101 },
    { 58, 198 },
    { 110, 282 },
    {0, 0}
  }
};

short wowie[][1000][2] = {
  {
    { 333, 492 },
    { 324, 496 },
    { 316, 502 },
    { 308, 508 },
    { 298, 509 },
    { 289, 506 },
    { 281, 501 },
    { 273, 494 },
    { 265, 488 },
    { 261, 479 },
    { 267, 480 },
    { 273, 487 },
    { 282, 491 },
    { 290, 497 },
    { 299, 501 },
    { 308, 498 },
    { 316, 492 },
    { 325, 488 },
    { 330, 479 },
    { 329, 469 },
    { 322, 462 },
    { 314, 457 },
    { 308, 449 },
    { 306, 439 },
    { 306, 429 },
    { 311, 420 },
    { 319, 417 },
    { 313, 424 },
    { 311, 434 },
    { 314, 444 },
    { 319, 452 },
    { 328, 457 },
    { 335, 464 },
    { 338, 473 },
    { 337, 483 },
    { 338, 489 },
    { 347, 493 },
    { 352, 502 },
    { 354, 512 },
    { 354, 522 },
    { 353, 532 },
    { 354, 542 },
    { 357, 551 },
    { 355, 561 },
    { 346, 566 },
    { 337, 567 },
    { 327, 569 },
    { 318, 573 },
    { 310, 579 },
    { 302, 584 },
    { 292, 586 },
    { 282, 585 },
    { 273, 581 },
    { 265, 575 },
    { 258, 568 },
    { 249, 565 },
    { 241, 560 },
    { 240, 550 },
    { 240, 540 },
    { 239, 530 },
    { 234, 526 },
    { 226, 519 },
    { 220, 512 },
    { 215, 503 },
    { 212, 493 },
    { 210, 484 },
    { 208, 474 },
    { 207, 464 },
    { 215, 461 },
    { 217, 471 },
    { 218, 480 },
    { 219, 490 },
    { 221, 500 },
    { 225, 510 },
    { 231, 517 },
    { 237, 520 },
    { 236, 510 },
    { 239, 500 },
    { 245, 493 },
    { 255, 494 },
    { 257, 496 },
    { 248, 498 },
    { 244, 507 },
    { 244, 517 },
    { 246, 527 },
    { 248, 537 },
    { 249, 546 },
    { 249, 556 },
    { 258, 559 },
    { 266, 564 },
    { 273, 571 },
    { 281, 576 },
    { 291, 578 },
    { 301, 576 },
    { 309, 570 },
    { 317, 564 },
    { 326, 561 },
    { 336, 561 },
    { 346, 559 },
    { 349, 550 },
    { 346, 541 },
    { 346, 531 },
    { 347, 521 },
    { 347, 511 },
    { 343, 501 },
    { 335, 497 },
    { 324, 523 },
    { 315, 528 },
    { 305, 530 },
    { 295, 531 },
    { 286, 529 },
    { 276, 527 },
    { 268, 532 },
    { 261, 527 },
    { 268, 521 },
    { 278, 520 },
    { 288, 521 },
    { 298, 523 },
    { 308, 522 },
    { 317, 520 },
    { 326, 516 },
    { 392, 460 },
    { 392, 470 },
    { 390, 479 },
    { 387, 489 },
    { 383, 498 },
    { 378, 507 },
    { 371, 514 },
    { 367, 523 },
    { 360, 527 },
    { 359, 517 },
    { 365, 509 },
    { 371, 502 },
    { 376, 493 },
    { 381, 484 },
    { 385, 475 },
    { 387, 465 },
    { 388, 456 },
    { 331, 416 },
    { 326, 414 },
    { 335, 410 },
    { 344, 406 },
    { 353, 403 },
    { 363, 402 },
    { 373, 402 },
    { 378, 408 },
    { 369, 409 },
    { 359, 408 },
    { 355, 417 },
    { 346, 420 },
    { 337, 414 },
    { 238, 401 },
    { 228, 403 },
    { 220, 401 },
    { 227, 395 },
    { 237, 393 },
    { 247, 395 },
    { 256, 399 },
    { 264, 404 },
    { 272, 410 },
    { 276, 418 },
    { 268, 413 },
    { 260, 407 },
    { 260, 409 },
    { 254, 416 },
    { 244, 416 },
    { 243, 408 },
    { 340, 412 },
    { 328, 403 },
    { 336, 397 },
    { 344, 391 },
    { 352, 385 },
    { 360, 380 },
    { 370, 376 },
    { 380, 375 },
    { 388, 380 },
    { 393, 388 },
    { 385, 389 },
    { 377, 382 },
    { 367, 382 },
    { 358, 386 },
    { 350, 391 },
    { 342, 398 },
    { 334, 404 },
    { 327, 410 },
    { 263, 400 },
    { 256, 393 },
    { 248, 387 },
    { 239, 383 },
    { 229, 381 },
    { 219, 380 },
    { 209, 381 },
    { 208, 373 },
    { 218, 372 },
    { 228, 373 },
    { 238, 376 },
    { 247, 381 },
    { 255, 386 },
    { 262, 393 },
    { 269, 401 },
    { 414, 331 },
    { 412, 340 },
    { 408, 350 },
    { 400, 356 },
    { 391, 360 },
    { 381, 363 },
    { 371, 365 },
    { 362, 366 },
    { 352, 368 },
    { 342, 369 },
    { 332, 371 },
    { 322, 372 },
    { 312, 372 },
    { 302, 373 },
    { 292, 373 },
    { 282, 373 },
    { 272, 373 },
    { 262, 373 },
    { 252, 372 },
    { 242, 371 },
    { 232, 369 },
    { 222, 367 },
    { 213, 365 },
    { 203, 363 },
    { 193, 361 },
    { 184, 357 },
    { 178, 349 },
    { 181, 341 },
    { 177, 332 },
    { 175, 323 },
    { 182, 326 },
    { 187, 334 },
    { 187, 343 },
    { 188, 352 },
    { 197, 355 },
    { 207, 356 },
    { 217, 358 },
    { 227, 361 },
    { 237, 362 },
    { 247, 364 },
    { 256, 365 },
    { 266, 366 },
    { 276, 366 },
    { 286, 366 },
    { 296, 366 },
    { 306, 366 },
    { 316, 366 },
    { 326, 365 },
    { 336, 364 },
    { 346, 362 },
    { 356, 361 },
    { 366, 360 },
    { 376, 359 },
    { 386, 357 },
    { 395, 353 },
    { 403, 347 },
    { 407, 338 },
    { 410, 329 },
    { 416, 325 },
    { 454, 314 },
    { 464, 311 },
    { 471, 304 },
    { 469, 295 },
    { 468, 285 },
    { 477, 280 },
    { 486, 275 },
    { 495, 271 },
    { 503, 265 },
    { 509, 257 },
    { 513, 248 },
    { 518, 240 },
    { 524, 231 },
    { 527, 222 },
    { 530, 212 },
    { 531, 202 },
    { 532, 192 },
    { 533, 182 },
    { 534, 172 },
    { 534, 162 },
    { 535, 153 },
    { 535, 143 },
    { 534, 133 },
    { 533, 123 },
    { 532, 113 },
    { 531, 103 },
    { 529, 93 },
    { 526, 83 },
    { 524, 74 },
    { 521, 64 },
    { 517, 55 },
    { 513, 46 },
    { 507, 38 },
    { 500, 31 },
    { 491, 25 },
    { 482, 25 },
    { 476, 33 },
    { 477, 43 },
    { 479, 53 },
    { 481, 63 },
    { 485, 72 },
    { 488, 81 },
    { 491, 91 },
    { 493, 101 },
    { 494, 111 },
    { 495, 121 },
    { 494, 131 },
    { 492, 140 },
    { 489, 150 },
    { 485, 159 },
    { 480, 168 },
    { 474, 176 },
    { 467, 183 },
    { 460, 190 },
    { 456, 199 },
    { 452, 208 },
    { 443, 212 },
    { 437, 205 },
    { 429, 199 },
    { 419, 201 },
    { 410, 205 },
    { 400, 207 },
    { 400, 204 },
    { 410, 202 },
    { 418, 196 },
    { 427, 193 },
    { 436, 197 },
    { 441, 205 },
    { 449, 202 },
    { 453, 193 },
    { 457, 184 },
    { 464, 177 },
    { 471, 169 },
    { 476, 161 },
    { 481, 152 },
    { 484, 143 },
    { 487, 133 },
    { 488, 123 },
    { 488, 113 },
    { 487, 103 },
    { 485, 93 },
    { 483, 84 },
    { 479, 74 },
    { 476, 65 },
    { 473, 55 },
    { 471, 45 },
    { 471, 35 },
    { 472, 26 },
    { 480, 20 },
    { 490, 20 },
    { 499, 24 },
    { 507, 30 },
    { 514, 38 },
    { 519, 46 },
    { 524, 55 },
    { 527, 64 },
    { 531, 74 },
    { 533, 83 },
    { 536, 93 },
    { 538, 103 },
    { 540, 112 },
    { 541, 122 },
    { 541, 132 },
    { 542, 142 },
    { 542, 152 },
    { 541, 162 },
    { 541, 172 },
    { 540, 182 },
    { 539, 192 },
    { 538, 202 },
    { 537, 212 },
    { 535, 222 },
    { 531, 231 },
    { 527, 240 },
    { 521, 248 },
    { 516, 257 },
    { 512, 266 },
    { 505, 273 },
    { 496, 278 },
    { 488, 283 },
    { 479, 288 },
    { 474, 294 },
    { 479, 303 },
    { 475, 312 },
    { 466, 316 },
    { 457, 320 },
    { 448, 325 },
    { 138, 302 },
    { 129, 298 },
    { 120, 293 },
    { 111, 288 },
    { 103, 283 },
    { 95, 277 },
    { 87, 270 },
    { 81, 262 },
    { 76, 254 },
    { 71, 245 },
    { 67, 236 },
    { 63, 227 },
    { 59, 218 },
    { 55, 208 },
    { 52, 199 },
    { 48, 190 },
    { 45, 180 },
    { 41, 171 },
    { 38, 161 },
    { 37, 151 },
    { 36, 141 },
    { 36, 131 },
    { 36, 121 },
    { 36, 111 },
    { 35, 102 },
    { 34, 92 },
    { 36, 82 },
    { 40, 73 },
    { 44, 64 },
    { 49, 55 },
    { 54, 47 },
    { 61, 39 },
    { 69, 34 },
    { 77, 40 },
    { 82, 49 },
    { 83, 59 },
    { 83, 69 },
    { 84, 79 },
    { 84, 89 },
    { 85, 99 },
    { 86, 109 },
    { 88, 119 },
    { 90, 128 },
    { 93, 138 },
    { 96, 148 },
    { 100, 157 },
    { 104, 166 },
    { 110, 174 },
    { 116, 182 },
    { 122, 190 },
    { 128, 198 },
    { 137, 200 },
    { 145, 194 },
    { 152, 187 },
    { 162, 189 },
    { 169, 197 },
    { 177, 200 },
    { 187, 199 },
    { 196, 203 },
    { 205, 207 },
    { 212, 201 },
    { 215, 192 },
    { 221, 184 },
    { 229, 178 },
    { 238, 172 },
    { 247, 168 },
    { 256, 165 },
    { 266, 162 },
    { 276, 161 },
    { 286, 159 },
    { 295, 159 },
    { 305, 159 },
    { 315, 160 },
    { 325, 163 },
    { 335, 166 },
    { 344, 170 },
    { 352, 175 },
    { 360, 181 },
    { 368, 188 },
    { 374, 195 },
    { 381, 203 },
    { 387, 211 },
    { 392, 220 },
    { 397, 228 },
    { 402, 237 },
    { 401, 246 },
    { 395, 238 },
    { 391, 230 },
    { 386, 221 },
    { 380, 212 },
    { 374, 204 },
    { 368, 197 },
    { 360, 190 },
    { 352, 184 },
    { 344, 179 },
    { 335, 174 },
    { 325, 171 },
    { 316, 169 },
    { 306, 167 },
    { 296, 166 },
    { 286, 168 },
    { 276, 169 },
    { 266, 171 },
    { 257, 173 },
    { 247, 177 },
    { 238, 181 },
    { 230, 187 },
    { 223, 194 },
    { 218, 203 },
    { 213, 211 },
    { 204, 215 },
    { 196, 210 },
    { 187, 206 },
    { 177, 207 },
    { 167, 206 },
    { 161, 198 },
    { 152, 195 },
    { 145, 202 },
    { 137, 208 },
    { 127, 207 },
    { 120, 200 },
    { 114, 192 },
    { 108, 184 },
    { 102, 176 },
    { 96, 168 },
    { 92, 159 },
    { 88, 150 },
    { 85, 140 },
    { 82, 131 },
    { 80, 121 },
    { 79, 111 },
    { 77, 101 },
    { 77, 91 },
    { 76, 81 },
    { 76, 71 },
    { 75, 61 },
    { 74, 51 },
    { 69, 43 },
    { 61, 45 },
    { 55, 53 },
    { 51, 62 },
    { 47, 72 },
    { 44, 81 },
    { 42, 91 },
    { 43, 101 },
    { 44, 111 },
    { 44, 121 },
    { 44, 131 },
    { 43, 141 },
    { 44, 151 },
    { 45, 161 },
    { 48, 170 },
    { 52, 180 },
    { 55, 189 },
    { 58, 198 },
    { 62, 208 },
    { 66, 217 },
    { 69, 226 },
    { 73, 235 },
    { 77, 245 },
    { 82, 254 },
    { 88, 262 },
    { 94, 269 },
    { 102, 276 },
    { 110, 282 },
    { 118, 287 },
    { 127, 292 },
    { 136, 297 },
    { 142, 302 },
    {0, 0}
  }
};

void doDrawing() {
//  int x = -20000, y = -20000;
  int x = wowie[0][0][0];
  int y = wowie[0][0][1];
  
  int x2 = 0, y2 = 0;
  int dist;

//  Serial.printf("0: %d %d = %d\n", sizeof wowie, sizeof wowie[0], sizeof wowie / sizeof wowie[0]);
  // 2656000 8000 - should be 332.

  // go to the start point with beam off
  analogWrite(XDACPin, x);
  analogWrite(YDACPin, y);

//  Serial.printf("%d : % 3.3d % 3.3d -> % 3.3d % 3.3d -> %d\n", 0, x, y, x2, y2, dist);

  // wait for the beam to reach the start point
  delayMicroseconds(10);
  digitalWrite(BlankPin, HIGH);
  delayMicroseconds(glowDelay);        // wait for glow to start

  for (int i = (sizeof wowie / sizeof wowie[0]) - 1; i >= 0; i--) {
    //Serial.printf("1: %d %d %d\n", sizeof wowie[0], sizeof wowie[0][0], sizeof wowie[0] / sizeof wowie[0][0]);
    for (int j = 0; j < 999; j++) {
      //Serial.printf("%d %d - %d %d\n", i, j, (int)wowie[i][j][0], (int)wowie[i][j][1]);

      x2 = (((wowie[i][j][0] / (float)600) - 0.5) * -2000) + midDAC + xPos + XSaver;
      y2 = (((wowie[i][j][1] / (float)600) - 0.5) * -2000) + midDAC + yPos + YSaver;

      if (wowie[i][j][0] == 0 && wowie[i][j][1] == 0)
        break;

//      dist = (int)sqrt(((x2 - x) * (x2 - x)) + ((y2 - y) * (y2 - y)));

//      if (abs(x - x2) < 100 && abs(y - y2) < 100)
//      if(dist < 200)
//        drawALine(x, y, x2, y2);

  analogWriteDAC0(x2);
  analogWriteDAC1(y2);

//      delayMicroseconds(10);
//      Serial.printf("%d : % 3.3d % 3.3d -> % 3.3d % 3.3d -> %d\n", j, x, y, x2, y2, dist);

      x = x2;
      y = y2;

    }
  }
  digitalWrite(BlankPin, LOW);

}
