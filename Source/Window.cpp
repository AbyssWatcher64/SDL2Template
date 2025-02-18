//#include "PreCompileHeaders.h"
#include "Window.hpp"
#include "Module.hpp"
#include "SDL2/SDL_image.h"

Window::Window() : Module()
{
	window = NULL;
	name = "window";
}

Window::~Window()
{
}

// For pixel art check: https://sneslab.net/wiki/Widescreen
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

		Uint32 flags = SDL_WINDOW_SHOWN;
		bool fullscreen = false;
		bool borderless = false;
		bool resizable = false;
		bool fullscreen_window = false;
		std::string gameTitle = "SDL Engine Template";

		//TODO Get the values from the config file
		width = 352;
		height = 224;
		scale = 1;

		if (fullscreen == true) flags |= SDL_WINDOW_FULLSCREEN;
		if (borderless == true) flags |= SDL_WINDOW_BORDERLESS;
		if (resizable == true) flags |= SDL_WINDOW_RESIZABLE;
		if (fullscreen_window == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow(gameTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * scale, height * scale, flags);
		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}

		icon = IMG_Load("./Assets/UI/Misc/EngineIcon.png");
		if (icon == NULL)
		{
			LOG("Icon could not be loaded into the window! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			SDL_SetWindowIcon(window, icon);
			SDL_FreeSurface(icon);  
		}
	}

	return ret;
}

bool Window::CleanUp()
{
	LOG("Destroying SDL window.");

	// Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}

	// Quit SDL subsystems
	SDL_Quit();
	return true;
}

// TODO: Change this to return a vector? 
// Store windowWidth and windowHeight as scaled values when creating the window.
//void Window::GetWindowSize(int& outWidth, int& outHeight) const
//{
//	outWidth = width * scale;
//	outHeight = height * scale;
//}

int Window::GetScale() const
{
	return scale;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

