#pragma once

#include <vector>
#include <string>
#include <algorithm>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60
#define TTF_MENUSIZE 40

//--
//UI
#define HP_BAR_WIDTH 256
#define HP_BAR_HEIGHT 56

#define POWER_BAR_WIDTH 35
#define POWER_BAR_HEIGHT 15

#define WIND_BAR_WIDTH 136
#define WIND_BAR_HEIGHT 25
//--

struct Vec2 { // worm bottom pixels
    int X;
    int Y;
};

struct Vec2f { // worm bottom pixels
    float X;
    float Y;
};

struct Rect {
	int x;
	int y;
	int w;
	int h;

};


struct ScoreInfo
{
    std::string teamName;
    int punctuation;
};

struct WormUtilities {
    float lerpValue(float t, float a, float b) {
        return a + t * (b - a);
    }

    float mapValue(float val, float ogMin, float ogMax, float newMin, float newMax) {
        //get proportion in original range
        float prop = (val - ogMin) / (ogMax - ogMin);
        return lerpValue(prop, newMin, newMax);
    }
};

static WormUtilities Utiles;

enum Flip {
    FLIP_NONE,FLIP_HORIZONTAL,FLIP_VERTICAL
};


