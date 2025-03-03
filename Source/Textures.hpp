#ifndef TEXTURES
#define TEXTURES

#include "Module.hpp"

class Textures : public Module
{
public:
	Textures();
	~Textures();

	bool Awake() override;
	bool Start() override;
	bool CleanUp() override;

	SDL_Texture* const Load(std::string path);
	void ReloadTextures();
	bool UnLoad(SDL_Texture* texture);
	void GetSize(const SDL_Texture* texture, int& width, int& height) const;

private:
	SDL_Texture* const LoadSurface(SDL_Surface* surface);

private:
	std::vector<std::pair<std::string, SDL_Surface*>> textureSurfaces;
	std::list<SDL_Texture*> textures;
};

#endif 
