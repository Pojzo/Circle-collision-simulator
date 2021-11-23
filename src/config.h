#ifndef CONFIG_H
#define CONFIG_H

static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;
static const int FPS = 60;
static const float DELAY_MS = 1000. / FPS;
static const char WINDOW_NAME[]= "Window";

static const int CIRCLE_DEFAULT_MASS = 1;
static const float CIRCLE_MIN_MASS = 1;
static const float CIRCLE_MAX_MASS = 100;

static const int DEFAULT_NUM_CIRCLES = 5;

static const int BACKGROUND_R = 255;
static const int BACKGROUND_G = 255;
static const int BACKGROUND_B = 255;
static const int BACKGROUND_A = 255;

#endif
