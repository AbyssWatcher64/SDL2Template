#ifndef FONTS
#define FONTS

#include "Module.hpp"
#include "SDL2/SDL_ttf.h"

#endif

class Fonts : public Module
{
public:
	Fonts();
	~Fonts();

	bool Awake() override;
	bool Start() override;
	bool CleanUp() override;

	TTF_Font* LoadFont(const std::string& path, int size = 12);
	TTF_Font* GetDefaultFont() const;
private:
	TTF_Font* defaultFont = nullptr;
};