//#include "PreCompileHeaders.h"
#include "Window.hpp"
#include "Module.hpp"
#include "Renderer.hpp"
#include "Textures.hpp"
#include "IniParser.hpp"

Window::Window() : Module()
{
	window = nullptr;
	name = "window";
	gameTitle = "SDL Engine Template";
	engineIconPath = "./Assets/UI/Misc/EngineIcon.png";
}

Window::~Window() {}

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
	std::unordered_map<std::string, std::string> configFile = LoadConfig("config.ini");

	WindowFlagBools flagBools{};
	flagBools.fullscreen = GetBoolFromConfig(configFile, "fullscreen");
	flagBools.borderless = GetBoolFromConfig(configFile, "borderless");
	flagBools.resizable = GetBoolFromConfig(configFile, "resizable");
	flagBools.fullscreenWindow = GetBoolFromConfig(configFile, "fullscreen_window");

	return flagBools;
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
	std::unordered_map<std::string, std::string> configFile = LoadConfig("config.ini");

	width = GetIntFromConfig(configFile, "width_resolution");
	height = GetIntFromConfig(configFile, "height_resolution");
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
	icon = nullptr;
	return ret;
}

void Window::ChangeResolution(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;

	LOG("EVENT: Changing resolution to: %d x %d", width, height);
	SDL_SetWindowSize(window, width, height);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	Engine::Singleton().renderer->ResizeViewPort(width, height);

	std::unordered_map<std::string, std::string> configFile = LoadConfig("config.ini");
	configFile.find("width_resolution")->second = std::to_string(newWidth);
	configFile.find("height_resolution")->second = std::to_string(newHeight);
	SaveConfig("config.ini", configFile);
}

void Window::ToggleFullScreen()
{
	LOG("Setting FullScreen with resolution: %d x %d", width, height);

	TMP_SETFULLSCREEN = !TMP_SETFULLSCREEN;
	Uint32 flags = InitializeAndSetWindowFlags();
	SDL_SetWindowFullscreen(window, flags);

	SDL_GetWindowSize(window, &width, &height);
	Engine::Singleton().renderer->ResizeViewPort(width, height);
	if (!TMP_SETFULLSCREEN)
	{
		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
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

