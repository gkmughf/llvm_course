#include "sim.h"

#define PIXEL_SIZE 4
#define FIELD_SIZE (ALL / PIXEL_SIZE / PIXEL_SIZE)
#define FIELD_X_SIZE (SIM_X_SIZE / PIXEL_SIZE)
#define FIELD_Y_SIZE (SIM_Y_SIZE / PIXEL_SIZE)

#define BACKGROUND 0xFF000000


int clamp(int val, int min, int max) {
  if (val > max) return max;
  if (val < min) return min;
  return val;
}

int activation(int x) {
  return clamp(x, 0, 255);
}

void gen_mask(int m[9]) {
  int r = simRand();
  int rn = 0;  
  for (int i = 0; i < 9; ++i) {
    if (rn == 4) {
      r = simRand();
      rn = 0;
    }
    m[i] = ((r >> rn) & 7) - 4;
    ++rn;
  }
}

int get_cell_torus(int f[FIELD_SIZE], int x, int y) {
  if (x >= FIELD_X_SIZE)
    x = x - FIELD_X_SIZE;
  if (x < 0)
    x = FIELD_X_SIZE + x;

  if (y >= FIELD_Y_SIZE)
    y = y - FIELD_Y_SIZE;
  if (y < 0)
    y = FIELD_Y_SIZE + y;

  return f[y * FIELD_X_SIZE + x];
}

void field_update(int f[FIELD_SIZE], int mask[9]) {
  int new_f[FIELD_SIZE];

  int i = 0;
  for (int y = 0; y < FIELD_Y_SIZE; y++) {
    for (int x = 0; x < FIELD_X_SIZE; x++) {
      int m = 0;
      new_f[i] = 0;
      for (int dy = -1; dy <= 1; ++dy) {
	for (int dx = -1; dx <= 1; ++dx) {
	  new_f[i] += mask[m] * get_cell_torus(f, x + dx, y + dy);
	  ++m;
	}
      }
      new_f[i] = activation(new_f[i]);
      ++i;
    }
  }

  int sum = 0;
  for (int i = 0; i < FIELD_SIZE; ++i) {
    f[i] = new_f[i];
    sum += f[i];
  }
  if (sum == 0)
    f[0] = 64;
}

void put_pixel(int x, int y, int color) {
  for(int py = 0; py < PIXEL_SIZE; ++py) {
    for (int px = 0; px < PIXEL_SIZE; ++px) {
      simPutPixel(x + px, y + py, color);
    }
  }
}

void field_display(int f[FIELD_SIZE]) {
  simClear(BACKGROUND);

  int i = 0;
  for (int y = 0; y < SIM_Y_SIZE; y += PIXEL_SIZE) {
    for (int x = 0; x < SIM_X_SIZE; x += PIXEL_SIZE) {
      put_pixel(x, y, 0xFF000000 + 0x00010101 * f[i]);
      ++i;
    }
  }
  
  simFlush();
}


void field_init(int f[FIELD_SIZE]) {
  for (int i = 0; i < FIELD_SIZE; ++i) {
    f[i] = 0;
  }
  f[FIELD_SIZE / 2 + 64] = 64;
}



void app() {
  int field[FIELD_SIZE];
  field_init(field);

  int mask[9];
  gen_mask(mask);
  for (int i = 0;; ++i) {
    if (i % 10 == 0) {
      gen_mask(mask);
    }
    field_display(field);
    field_update(field, mask);
  }
}
