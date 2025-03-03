#pragma once
#include "Module.hpp"
#include "SDL2/SDL_image.h"

struct WindowFlagBools
{
	bool fullscreen = false;
	bool borderless = false;
	bool resizable = false;
	bool fullscreenWindow = false;
};

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

	// Window creation
	bool AttemptToCreateWindowAndSetIcon();
	Uint32 InitializeAndSetWindowFlags();
	WindowFlagBools InitializeWindowFlags();
	Uint32 SetFlagsForWindow(WindowFlagBools flagBools);
	void InitializeWindowSize();
	bool AttemptToCreateWindow(const std::string& windowName, Uint32 flags);
	bool AttemptToSetWindowIcon(const std::string& path);


	// Change title
	//void SetTitle(const char* title);
	void ChangeResolution(int newWidth, int newHeight);
	void ToggleFullScreen();
	void DeleteWindow();

	// TODO, maybe - Retrive window size
	//Vector2D GetWindowSize() const;
	int GetWindowWidth() const;
	int GetWindowHeight() const;

	// Getter of the window
	SDL_Window* GetWindow() const;

private:
	SDL_Window* window;

	std::string gameTitle;
	std::string engineIconPath;
	bool isFullScreen = false;
	int width;
	int height;

	bool TMP_SETFULLSCREEN = false;
};