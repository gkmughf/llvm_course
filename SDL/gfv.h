#define GFV_X_SIZE 512
#define GFV_Y_SIZE 512
#define ALL (GFV_X_SIZE * GFV_Y_SIZE)

#ifndef __gfv__
void gfvFlush();
void gfvPutPixel(int x, int y, int argb);
int gfvRand();
void gfvClear(int argb);
#endif

extern void gfvInit();
extern void app();
extern void gfvExit();
