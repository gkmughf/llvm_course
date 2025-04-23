#include "sim.h"


#define PIXEL_SIZE 4
#define FIELD_SIZE (ALL / PIXEL_SIZE / PIXEL_SIZE)
#define FIELD_X_SIZE (SIM_X_SIZE / PIXEL_SIZE)
#define FIELD_Y_SIZE (SIM_Y_SIZE / PIXEL_SIZE)

#define WIRE      1
#define HEAD      2
#define TAIL      3

#define BACKGROUND 0xFF000000
#define COLOR_WIRE  0xFF000000
#define COLOR_HEAD  0xFFFF00FF
#define COLOR_TAIL  0xFF00FFFF



int count_heads(int f[FIELD_SIZE], int y, int x, int type) {
    int cnt = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dy == 0 && dx == 0) continue;
            int ny = y + dy, nx = x + dx;
            if (ny <= 0 || ny > FIELD_Y_SIZE || nx <= 0 || nx > FIELD_X_SIZE) continue;
            if (f[ny * FIELD_X_SIZE + nx] == type) cnt++;
        }
    }
    return cnt;
}


void field_update(int f[FIELD_SIZE]) {
  int new_f[FIELD_SIZE];

  int i = 0;
  for (int y = 0; y < FIELD_Y_SIZE; y++) {
    for (int x = 0; x < FIELD_X_SIZE; x++) {
      int s = f[i];
      switch (s) {
      case WIRE: {
	int heads = count_heads(f, y, x, HEAD);
	new_f[i] = (heads == 1 || heads == 2) ? HEAD : WIRE;
	break;
      }
      case HEAD:
	new_f[i] = TAIL;
	break;
      case TAIL:
	new_f[i] = WIRE;
	break;
      }
      ++i;
    }
  }

  for (int i = 0; i < FIELD_SIZE; ++i) {
    f[i] = new_f[i];
  }
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
      int color;
      switch (f[i]) {
      case WIRE:  color = COLOR_WIRE;  break;
      case HEAD:  color = COLOR_HEAD;  break;
      case TAIL:  color = COLOR_TAIL;  break;
      default:    color = COLOR_WIRE; break;
      }
      put_pixel(x, y, color);
      ++i;
    }
  }
  
  simFlush();
}


void field_init(int f[FIELD_SIZE]) {
  for (int i = 0; i < FIELD_SIZE; ++i) {
    f[i] = WIRE;
  }
  int c = FIELD_SIZE / 2 + FIELD_X_SIZE / 2;
  
  for (int dx = -10; dx <= 10; ++dx) {
    f[c + dx] = WIRE;
  }
  f[c] = HEAD;
}



void app() {
  int field[FIELD_SIZE];
  field_init(field);
  while (1) {
    field_display(field);
    field_update(field);
  }
}
