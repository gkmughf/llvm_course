#define SIM_X_SIZE 512
#define SIM_Y_SIZE 512

#ifndef __sim__
void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();
void simClear(int argb);
#endif

extern void simInit();
extern void app();
extern void simExit();
