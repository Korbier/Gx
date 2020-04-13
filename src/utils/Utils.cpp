#include "Utils.h"

SDL_FPoint radMvtToCoord(float angle, float distance) {
	float rad = angle * M_PI / 180.0;
	float x = sin(rad) * distance;
	float y = cos(rad) * distance * -1;
	return { x, y };
}
