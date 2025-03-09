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

	LoadFont("./Assets/Fonts/TempFont2.ttf", 8);
	LoadFont("./Assets/Fonts/TempFont.ttf");
	// If new fonts have to be added, add them below and create a new FontName enum.

	ret = VerifyLoadedFontsIntegrity();

	return ret;
}

bool Fonts::CleanUp()
{
	bool ret = true;
	LOG("Fonts: Clearing fonts and quitting the font module.");
	for (auto const& font : fonts)
	{
		TTF_CloseFont(font);
	}
	TTF_Quit(); 
	return ret;
}

TTF_Font* Fonts::GetDefaultFont() const
{
	return fonts[FontName::DEFAULT_FONT];
}

TTF_Font* Fonts::GetFont(FontName fontName) const
{
	if (fontName >= DEFAULT_FONT && fontName < FONTNAME_TOTALCOUNT)
	{
		return fonts[fontName];
	}
	// If incorrect number is retrieved, it will go back to the default font.
	return fonts[FontName::DEFAULT_FONT];
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
		fonts.push_back(font);
	}
	return font;
}

bool Fonts::VerifyLoadedFontsIntegrity()
{
	for (const auto& font : fonts)
	{
		if (!font)
		{
			return false;
			LOG("Fonts: Font detected as null! Breaking Start cycle.");
			break;
		}
	}

	if (fonts.size() != FONTNAME_TOTALCOUNT)
	{
		return false;
		LOG("Fonts: Total fonts amount doesn't match what it should! Breaking Start cycle.");
	}

	return true;
}