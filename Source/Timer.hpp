#pragma once

class Timer
{
public:
	// Unsure whether this should be a ptr or not
	Timer();
	
	void Start();
	unsigned int GetSeconds() const;
	unsigned int GetMilliseconds() const;

private:
	int startTime;
};