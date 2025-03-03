//#include "PreCompileHeaders.h"
#include "Window.hpp"
#include "Module.hpp"
#include "Renderer.hpp"
#include "Textures.hpp"

Window::Window() : Module()
{
	window = nullptr;
	name = "window";
	gameTitle = "SDL Engine Template";
	engineIconPath = "./Assets/UI/Misc/EngineIcon.png";
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
		InitializeWindowSize();
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
	DeleteWindow();

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

	Uint32 flags = InitializeAndSetWindowFlags();

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

	// Grab flags from ConfigXML file
	WindowFlagBools flagBools{};
	if (TMP_SETFULLSCREEN)
	{
		flagBools.fullscreen = true;
	}

	return flagBools;
	//return WindowFlagBools{}; // Automatically initializes all fields to false
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

void Window::InitializeWindowSize()
{
	// TODO Get the values from the config file
	width = 352;
	height = 224;
}

bool Window::AttemptToCreateWindow(const std::string& windowName, Uint32 flags)
{
	bool ret = true;
	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
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
void Window::ChangeResolution(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;

	LOG("EVENT: Deleting current window and changing resolution to: %d x %d", width, height);
	//SDL_SetWindowSize(window, width, height);
	DeleteWindow();

	AttemptToCreateWindowAndSetIcon();

	Engine::Singleton().renderer->RecreateRenderer();
	Engine::Singleton().renderer->ResizeViewPort(width, height);
	//Engine::Singleton().textures->ReloadTextures();
}

void Window::ToggleFullScreen()
{
	LOG("EVENT: Deleting current window and changing resolution to: %d x %d", width, height);
	DeleteWindow();

	TMP_SETFULLSCREEN = !TMP_SETFULLSCREEN;

	AttemptToCreateWindowAndSetIcon();

	SDL_GetWindowSize(window, &width, &height);
	Engine::Singleton().renderer->RecreateRenderer();
	Engine::Singleton().renderer->ResizeViewPort(width, height);

}

void Window::DeleteWindow()
{
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}

int Window::GetWindowWidth() const  
{
	return width;
}

int Window::GetWindowHeight() const
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

