#pragma once
#include "Module.hpp"

class Window : public Module
{
public:
	// Constructor
	Window();

	// Destructor
	virtual ~Window();

	// Module functions
	bool Awake() override;
	bool CleanUp() override;

	// Change title
	//void SetTitle(const char* title);

	// TODO, maybe - Retrive window size
	//void GetWindowSize(int& width, int& height) const;

	// Retrieve window scale
	int GetScale() const;

	// Getter of the window
	SDL_Window* GetWindow() const;

private:
	SDL_Surface* icon;
	SDL_Window* window;

	std::string title;
	int width;
	int height;
	int scale;
};