#include "Fonts.hpp"

Fonts::Fonts()
{
	name = "fonts";
}

Fonts::~Fonts() {}

bool Fonts::Awake()
{
	bool ret = true;
	if (TTF_Init() == -1) 
	{
		LOG("Fonts: Failed to initialize SDL_ttf: %s", TTF_GetError());
		ret = false;
	}
	else
	{
		LOG("Fonts: SDL_ttf initialized successfully!");
	}
	return ret;
}

bool Fonts::Start()
{
	bool ret = true;
	defaultFont = LoadFont("./Assets/Fonts/TempFont.ttf");
	if (!defaultFont)
	{
		ret = false;
	}
	return ret;
}

bool Fonts::CleanUp()
{
	bool ret = true;
	LOG("Fonts: Quitting the TTF module and using TTF_Quit.");
	TTF_Quit(); 
	return ret;
}


TTF_Font* Fonts::LoadFont(const std::string& path, int size)
{
	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	if (!font) 
	{
		LOG("Failed to load font %s: %s", path.c_str(), TTF_GetError());
	}
	else
	{
		LOG("Font loaded successfully from %s", path.c_str(), TTF_GetError());
	}
	return font;
}

TTF_Font* Fonts::GetDefaultFont() const
{
	return defaultFont;
}