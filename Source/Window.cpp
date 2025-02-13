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
		std::string gameTitle = "RPG Game";

		//TODO Get the values from the config file
		width = 1080;
		height = 720;
		scale = 1;

		if (fullscreen == true) flags |= SDL_WINDOW_FULLSCREEN;
		if (borderless == true) flags |= SDL_WINDOW_BORDERLESS;
		if (resizable == true) flags |= SDL_WINDOW_RESIZABLE;
		if (fullscreen_window == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow(gameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
		if (window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}

		//icon = IMG_Load("./Assets/UI/brandicon.png");
		if (icon == NULL)
		{
			LOG("Icon could not be loaded into the window! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}

		//SDL_SetWindowIcon(window, icon);
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
	}
	else

	// Quit SDL subsystems
	SDL_Quit();
	return true;
}

int Window::GetScale() const
{
	return scale;
}