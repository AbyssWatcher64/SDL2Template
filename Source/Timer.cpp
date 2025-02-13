#include "Timer.hpp"
#include "SDL2\SDL_timer.h"

Timer::Timer()
{
	Start();
}

void Timer::Start()
{
	startTime = SDL_GetTicks();
}

unsigned int Timer::GetSeconds() const
{
	return SDL_GetTicks() - startTime / 1000;
}

unsigned int Timer::GetMilliseconds() const
{
	return SDL_GetTicks() - startTime;
}