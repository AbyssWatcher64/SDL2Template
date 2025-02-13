#include "PrecisionTimer.hpp"

PrecisionTimer::PrecisionTimer()
{
	Start();
}

void PrecisionTimer::Start()
{
	frequency = SDL_GetPerformanceFrequency();
	startTime = SDL_GetPerformanceCounter();
}

double PrecisionTimer::ReadMs() const
{
	return ((double)(SDL_GetPerformanceCounter() - startTime) / frequency * 1000);
}

Uint64 PrecisionTimer::ReadTicks() const
{
	return SDL_GetPerformanceCounter() - startTime;
}