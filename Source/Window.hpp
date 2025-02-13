#pragma once

#include "PreCompileHeaders.h"
#include "Module.hpp"
#include "SDL2/SDL_Video.h"

class Window : public Module
{
public:

	Window();

	// Destructor
	virtual ~Window();

	// Called before renderer is available
	bool Awake();

	// Called before quitting
	bool CleanUp();

	// Changae title
	void SetTitle(const char* title);

	// TODO, maybe?
	// Retrive window size
	void GetWindowSize(int& width, int& height) const;

	// Retrieve window scale
	int GetScale() const;

	// The window we'll be rendering to
private:
	SDL_Surface* icon;
	std::string title;

public:
	SDL_Window* window;

	int width;
	int height;
	int scale;
};