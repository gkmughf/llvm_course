#include "sim.h"

#define MAX_ITERATIONS 1000
#define MAX_PARTICLES 5000
#define FIXED_SHIFT 14
#define FIXED_ONE (1 << FIXED_SHIFT)
#define G 5000
#define BLACK_HOLE_RADIUS (15 * FIXED_ONE)

static inline int fixed_mul(int a, int b) {
  return ((long long)a * (long long)b) >> FIXED_SHIFT;
}

static inline int fixed_div(int a, int b) {
  return ((long long)a << FIXED_SHIFT) / b;
}

static inline int fixed_sqrt(int a) {
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
  return res << 7;
}

int clamp(int val, int min, int max) {
  if (val > max)
    return max;
  if (val < min)
    return min;
  return val;
}
#define BH_X (SIM_Y_SIZE / 2 * FIXED_ONE)
#define BH_Y (SIM_X_SIZE / 2 * FIXED_ONE)

static int particles_x[MAX_PARTICLES];
static int particles_y[MAX_PARTICLES];
static int particles_vx[MAX_PARTICLES];
static int particles_vy[MAX_PARTICLES];
static int particles_active[MAX_PARTICLES];
static int particles_count = 0;

void init_particle(int i) {
  particles_x[i] = (simRand() % (512 * FIXED_ONE));
  particles_y[i] = (simRand() % (512 * FIXED_ONE));

  int dx = particles_x[i] - BH_X;
  int dy = particles_y[i] - BH_Y;
  int distance_sq = fixed_mul(dx, dx) + fixed_mul(dy, dy);
  int distance = fixed_sqrt(distance_sq);

  if (distance_sq > 256 * 256 * FIXED_ONE)
    return;
  if (distance == 0) {
    particles_vx[i] = 0;
    particles_vy[i] = 0;
  } else {
    int norm_dx = fixed_div(dx, distance);
    int norm_dy = fixed_div(dy, distance);
    int orbital_speed = fixed_sqrt(fixed_div(G * FIXED_ONE, distance));
    particles_vx[i] = fixed_mul(-norm_dy, orbital_speed);
    particles_vy[i] = fixed_mul(norm_dx, orbital_speed);
  }

  particles_active[i] = 1;
}

void init_particles() {
  particles_count = MAX_PARTICLES;
  for (int i = 0; i < MAX_PARTICLES; i++) {
    init_particle(i);
  }
}

void update_particles() {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (!particles_active[i]) {
      init_particle(i);
    }
  }
  int dt = fixed_div(FIXED_ONE, 15 * FIXED_ONE);
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (!particles_active[i])
      continue;

    int dx = -particles_x[i] + BH_X;
    int dy = -particles_y[i] + BH_Y;
    int distance_sq = fixed_mul(dx, dx) + fixed_mul(dy, dy);

    if (distance_sq < fixed_mul(BLACK_HOLE_RADIUS, BLACK_HOLE_RADIUS)) {
      particles_active[i] = 0;
      continue;
    }

    if (distance_sq == 0)
      continue;
    int a = fixed_div(G * FIXED_ONE, distance_sq);

    int ax = fixed_mul(a, dx);
    int ay = fixed_mul(a, dy);

    particles_vx[i] = clamp(particles_vx[i] + fixed_mul(ax, dt),
                            -100 * FIXED_ONE, 100 * FIXED_ONE);
    particles_vy[i] = clamp(particles_vy[i] + fixed_mul(ay, dt),
                            -100 * FIXED_ONE, 100 * FIXED_ONE);

    particles_x[i] += fixed_mul(particles_vx[i], dt);
    particles_y[i] += fixed_mul(particles_vy[i], dt);
  }
}
int get_velocity_sq(int i) {
  return fixed_mul(particles_vx[i], particles_vx[i]) +
         fixed_mul(particles_vy[i], particles_vy[i]);
}
void display_particles() {
  for (int y = 0; y < SIM_X_SIZE; y++) {
    for (int x = 0; x < SIM_Y_SIZE; x++) {
      simPutPixel(x, y, 0xFF000000);
    }
  }

  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (!particles_active[i])
      continue;

    int screen_x = particles_x[i] >> FIXED_SHIFT;
    int screen_y = particles_y[i] >> FIXED_SHIFT;

    if (screen_x >= 0 && screen_x < SIM_Y_SIZE && screen_y >= 0 &&
        screen_y < SIM_X_SIZE) {
      int speed_colour =
          fixed_mul(fixed_div(get_velocity_sq(i), 20000 * FIXED_ONE), 255);
      simPutPixel(screen_y, screen_x,
                  0xFFFFFFFF - (speed_colour << 8 | (speed_colour << 8)));
    }
  }

  simFlush();
}

void app() {
  init_particles();

  for (int iter = 0; iter < MAX_ITERATIONS; iter--) {
    update_particles();
    display_particles();
  }
}
