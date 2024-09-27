#include "sim.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define FRAME_TICKS 50

static SDL_Renderer *Renderer = NULL;
static SDL_Window *Window = NULL;
static Uint32 Ticks = 0;

void simInit() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(SIM_X_SIZE, SIM_Y_SIZE, 0, &Window, &Renderer);
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
  SDL_RenderClear(Renderer);
  srand(time(NULL));
  simPutPixel(0, 0, 0);
  simFlush();
}
void simClear() {
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
  SDL_RenderClear(Renderer);
}

void simExit() {
  SDL_Event event;
  while (1) {
    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
      break;
  }
  SDL_DestroyRenderer(Renderer);
  SDL_DestroyWindow(Window);
  SDL_Quit();
}

void simFlush() {
  SDL_PumpEvents();
  assert(SDL_TRUE != SDL_HasEvent(SDL_QUIT) && "User-requested quit");
  Uint32 cur_ticks = SDL_GetTicks() - Ticks;
  if (cur_ticks < FRAME_TICKS) {
    SDL_Delay(FRAME_TICKS - cur_ticks);
  }
  SDL_RenderPresent(Renderer);
  SDL_RenderClear(Renderer);
}

void simPutPixel(int x, int y, int argb) {
  assert(0 <= x && x < SIM_X_SIZE && "Out of range");
  assert(0 <= y && y < SIM_Y_SIZE && "Out of range");
  Uint8 a = argb >> 24;
  Uint8 r = (argb >> 16) & 0xFF;
  Uint8 g = (argb >> 8) & 0xFF;
  Uint8 b = argb & 0xFF;
  SDL_SetRenderDrawColor(Renderer, r, g, b, a);
  SDL_RenderDrawPoint(Renderer, x, y);
  Ticks = SDL_GetTicks();
}

struct {
  uint x, y, z, w;
} R_STATE;
uint TausStep(uint z, int S1, int S2, int S3, uint M) {
  uint b = (((z << S1) ^ z) >> S2);
  return (((z & M) << S3) ^ b);
}

uint LCGStep(uint z, uint A, uint C) { return (A * z + C); }

int simRand() {
  R_STATE.x = TausStep(R_STATE.x, 13, 19, 12, (uint)(4294967294));
  R_STATE.y = TausStep(R_STATE.y, 2, 25, 4, (uint)(4294967288));
  R_STATE.z = TausStep(R_STATE.z, 3, 11, 17, (uint)(4294967280));
  R_STATE.w = LCGStep(R_STATE.w, (uint)(1664525), (uint)(1013904223));
  return (R_STATE.x ^ R_STATE.y ^ R_STATE.z ^ R_STATE.w) * 1000;
}
