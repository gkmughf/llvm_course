#include "sim.h"

#define SLOW 50
#define BACKGROUND 0xFF000000

#define MAX_PARTICLES 1000
#define MAX_SPAWN_RADIUS 512
#define MAX_SPEED 100

#define FIXED_SHIFT 10
#define FIXED_ONE (1 << FIXED_SHIFT)

#define G 5000
#define BLACK_HOLE_RADIUS (50 * FIXED_ONE)
#define BH_X (SIM_Y_SIZE / 2 * FIXED_ONE)
#define BH_Y (SIM_X_SIZE / 2 * FIXED_ONE)

int fixed_mul(int a, int b) {
  return ((long long)a * (long long)b) >> FIXED_SHIFT;
}

int fixed_div(int a, int b) { return ((long long)a << FIXED_SHIFT) / b; }

int fixed_sqrt(int a) {
  if (a <= 0)
    return 0;
  int res = 0;
  int bit = 1 << (30 - FIXED_SHIFT);
  while (bit > a)
    bit >>= 2;
  while (bit != 0) {
    if (a >= res + bit) {
      a -= res + bit;
      res = (res >> 1) + bit;
    } else {
      res >>= 1;
    }
    bit >>= 2;
  }
  return res << (FIXED_SHIFT / 2);
}

void swap_i(int *a, int *b) {
  *a += *b;
  *b = *a - *b;
  *a -= *b;
}

int clamp(int val, int min, int max) {
  if (val > max)
    return max;
  if (val < min)
    return min;
  return val;
}

int abs(int a) {
  int tmp[2] = {-a, a};
  return tmp[a > 0];
}

void draw_line(int x0, int y0, int x1, int y1, int color) {
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);

  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;

  int err = dx - dy;

  while (1) {
    if (x0 >= 0 && x0 < SIM_Y_SIZE && y0 >= 0 && y0 < SIM_X_SIZE) {
      simPutPixel(x0, y0, color);
    }

    if (x0 == x1 && y0 == y1)
      break;

    int e2 = 2 * err;

    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

/* struct particles_t { */
/*   int p[MAX_PARTICLES][2]; */
/*   int v[MAX_PARTICLES][2]; */
/*   int active[MAX_PARTICLES]; */
/*   int count; */
/* }; */

void swap(int i, int j, int p[MAX_PARTICLES][2], int v[MAX_PARTICLES][2],
          int active[MAX_PARTICLES], int *count) {
  swap_i(&active[i], &active[j]);
  swap_i(&v[i][0], &v[j][0]);
  swap_i(&v[i][1], &v[j][1]);
  swap_i(&p[i][0], &p[j][0]);
  swap_i(&p[i][1], &p[j][1]);
}

void init_particle(int i, int p[MAX_PARTICLES][2], int v[MAX_PARTICLES][2],
                   int active[MAX_PARTICLES], int *count) {
  active[i] = 0;
  p[i][0] = (simRand() % (SIM_X_SIZE * FIXED_ONE));
  p[i][1] = (simRand() % (SIM_Y_SIZE * FIXED_ONE));

  int dx = p[i][0] - BH_X;
  int dy = p[i][1] - BH_Y;
  int distance_sq = fixed_mul(dx, dx) + fixed_mul(dy, dy);
  int distance = fixed_sqrt(distance_sq);

  if (distance_sq > MAX_SPAWN_RADIUS * MAX_SPAWN_RADIUS * FIXED_ONE)
    return;
  if (distance == 0) {
    v[i][0] = 0;
    v[i][1] = 0;
  } else {
    int norm_dx = fixed_div(dx, distance);
    int norm_dy = fixed_div(dy, distance);
    int orbital_speed = fixed_sqrt(fixed_div((G / 2) * FIXED_ONE, distance));
    v[i][0] = fixed_mul(-norm_dy, orbital_speed);
    v[i][1] = fixed_mul(norm_dx, orbital_speed);
  }

  active[i] = 1;
  ++*count;
}

void delete_particle(int i, int p[MAX_PARTICLES][2], int v[MAX_PARTICLES][2],
                     int active[MAX_PARTICLES], int *count) {
  active[i] = 0;
  swap(i, --*count, p, v, active, count);
}

void init_particles(int p[MAX_PARTICLES][2], int v[MAX_PARTICLES][2],
                    int active[MAX_PARTICLES], int *count) {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    init_particle(i, p, v, active, count);
  }
}

void update_particles(int p[MAX_PARTICLES][2], int v[MAX_PARTICLES][2],
                      int active[MAX_PARTICLES], int *count) {
  for (int i = *count; i < MAX_PARTICLES; i++) {
    init_particle(*count, p, v, active, count);
  }
  int dt = fixed_div(FIXED_ONE, SLOW * FIXED_ONE);
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (!active[i])
      continue;

    int dx = -p[i][0] + BH_X;
    int dy = -p[i][1] + BH_Y;
    int distance_sq = fixed_mul(dx, dx) + fixed_mul(dy, dy);

    if (distance_sq < fixed_mul(BLACK_HOLE_RADIUS, BLACK_HOLE_RADIUS)) {
      delete_particle(i, p, v, active, count);
      --i;
      continue;
    }

    if (distance_sq == 0)
      continue;

    int a = fixed_div(G * FIXED_ONE, distance_sq);

    int ax = fixed_mul(a, dx);
    int ay = fixed_mul(a, dy);

    v[i][0] = clamp(v[i][0] + fixed_mul(ax, dt), -MAX_SPEED * FIXED_ONE,
                    MAX_SPEED * FIXED_ONE);
    v[i][1] = clamp(v[i][1] + fixed_mul(ay, dt), -MAX_SPEED * FIXED_ONE,
                    MAX_SPEED * FIXED_ONE);

    p[i][0] += fixed_mul(v[i][0], dt);
    p[i][1] += fixed_mul(v[i][1], dt);
  }
}

int get_velocity_sq(int i, int p[MAX_PARTICLES][2], int v[MAX_PARTICLES][2],
                    int active[MAX_PARTICLES]) {
  return fixed_mul(v[i][0], v[i][0]) + fixed_mul(v[i][1], v[i][1]);
}

void display_particles(int p[MAX_PARTICLES][2], int v[MAX_PARTICLES][2],
                       int active[MAX_PARTICLES]) {
  simClear(BACKGROUND);

  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (!active[i])
      continue;

    int screen_x = p[i][0] >> FIXED_SHIFT;
    int screen_y = p[i][1] >> FIXED_SHIFT;
    int prev_screen_x = (p[i][0] - v[i][0] / 10) >> FIXED_SHIFT;
    int prev_screen_y = (p[i][1] - v[i][1] / 10) >> FIXED_SHIFT;

    int speed_colour = fixed_mul(
        fixed_div(get_velocity_sq(i, p, v, active), 20000 * FIXED_ONE), 255);
    draw_line(screen_x, screen_y, prev_screen_x, prev_screen_y,
              0xFFFFFFFF - (speed_colour << 9 | (speed_colour << 3)));
  }

  simFlush();
}

void app() {
  int p[MAX_PARTICLES][2];
  int v[MAX_PARTICLES][2];
  int active[MAX_PARTICLES];
  int count = 0;
  init_particles(p, v, active, &count);
  while (1) {
    update_particles(p, v, active, &count);
    display_particles(p, v, active);
  }
}
