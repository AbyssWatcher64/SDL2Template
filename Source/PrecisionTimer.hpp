#pragma once
#include "SDL2\SDL_timer.h"

class PrecisionTimer
{
public:

	// Constructor
	PrecisionTimer();

	void Start();
	double ReadMs() const;
	Uint64 ReadTicks() const;

private:
	Uint64 startTime;
	Uint64 frequency;
};