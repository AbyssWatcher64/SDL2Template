#ifndef FONTS
#define FONTS

#include "Module.hpp"
#include "SDL2/SDL_ttf.h"

enum FontName
{
	DEFAULT_FONT = 0,
	DEFAULT_FONT1 = 1,
	// If new fonts have to be added, add a new enum below and Load them in the Fonts::Start()

	FONTNAME_TOTALCOUNT
};

class Fonts : public Module
{
public:
	Fonts();
	~Fonts();

	bool Awake() override;
	bool Start() override;
	bool CleanUp() override;

	TTF_Font* GetDefaultFont() const;
	TTF_Font* GetFont(FontName fontName) const;

private:
	TTF_Font* LoadFont(const std::string& path, int size = 12);
	bool VerifyLoadedFontsIntegrity();

private:
	std::vector<TTF_Font*> fonts;
};

#endif