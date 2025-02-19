//#include "PreCompileHeaders.h"
#include "Window.hpp"
#include "Module.hpp"

Window::Window() : Module()
{
	window = nullptr;
	name = "window";
}

Window::~Window()
{
}

// For resolution in SNES-like games check: https://sneslab.net/wiki/Widescreen
bool Window::Awake()
{
	LOG("== Initializing SDL window ==");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		ret = AttemptToCreateWindowAndSetIcon();
	}

	return ret;
}

bool Window::CleanUp()
{
	LOG("Destroying SDL window.");


	// Quit SDL subsystems
	SDL_Quit();

	// Destroy window
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	return true;
}

// TODO: Change this to return a vector? 
// Store windowWidth and windowHeight as scaled values when creating the window.
//void Window::GetWindowSize(int& outWidth, int& outHeight) const
//{
//	outWidth = width * scale;
//	outHeight = height * scale;
//}

bool Window::AttemptToCreateWindowAndSetIcon()
{
	bool ret = true;

	std::string gameTitle = "SDL Engine Template";
	std::string engineIconPath = "./Assets/UI/Misc/EngineIcon.png";

	Uint32 flags = InitializeAndSetWindowFlags();
	InitializeWindowSizeAndScale();

	// ret becomes true only if both are true
	ret = AttemptToCreateWindow(gameTitle, flags) && AttemptToSetWindowIcon(engineIconPath); 

	return ret;
}

Uint32 Window::InitializeAndSetWindowFlags()
{
	Uint32 flags = SetFlagsForWindow(InitializeWindowFlags());
	return flags;
}

WindowFlagBools Window::InitializeWindowFlags()
{
	//WindowFlagBools flagBools;
	//flagBools.fullscreen = false;
	//flagBools.borderless = false;
	//flagBools.resizable = false;
	//flagBools.fullscreenWindow = false;
	//return flagBools;

	return WindowFlagBools{}; // Automatically initializes all fields to false
}

Uint32 Window::SetFlagsForWindow(WindowFlagBools flagBools)
{
	Uint32 flags = SDL_WINDOW_SHOWN;
	if (flagBools.fullscreen)		flags |= SDL_WINDOW_FULLSCREEN;
	if (flagBools.borderless)		flags |= SDL_WINDOW_BORDERLESS;
	if (flagBools.resizable)		flags |= SDL_WINDOW_RESIZABLE;
	if (flagBools.fullscreenWindow) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	return flags;
}

void Window::InitializeWindowSizeAndScale()
{
	// TODO Get the values from the config file
	width = 352;
	height = 224;
	scale = 1;
}

bool Window::AttemptToCreateWindow(const std::string& windowName, Uint32 flags)
{
	bool ret = true;
	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * scale, height * scale, flags);
	if (window == nullptr)
	{
		LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	return ret;
}

bool Window::AttemptToSetWindowIcon(const std::string& path)
{
	bool ret = true;
	SDL_Surface* icon = IMG_Load(path.c_str());
	if (icon == nullptr)
	{
		LOG("Icon could not be loaded into the window! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}
	return ret;
}

// I don't like this.
//Vector2D Window::GetWindowSize() const
//{
//	return Vector2D(width, height);
//}

int Window::GetWindowWidth() const  
{
	return width;
}

int Window::GetWindowHeight() const
{
	return height;
}

int Window::GetScale() const
{
	return scale;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

