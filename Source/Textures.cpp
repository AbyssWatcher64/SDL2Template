#include "PreCompileHeaders.h"
#include "Textures.hpp"
#include "SDL2/SDL_image.h"
#include "Renderer.hpp"

Textures::Textures()
{
	name = "textures";
}

Textures::~Textures() { }

bool Textures::Awake()
{
	LOG("== Initializing Textures ==");
	bool ret = true;

	// Load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

bool Textures::Start()
{
	LOG("== Starting Textures ==");
	bool ret = true;
	return ret;
}

bool Textures::CleanUp()
{
    LOG("Freeing textures and Image library");

    // Destroy textures
    for (SDL_Texture* texture : textures)
    {
        SDL_DestroyTexture(texture);
    }
    textures.clear();

    // Free surfaces if necessary
    for (auto& surfacePair : textureSurfaces)
    {
        SDL_FreeSurface(surfacePair.second);
    }
    textureSurfaces.clear();

    IMG_Quit();
    return true;
}



SDL_Texture* const Textures::Load(std::string path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface)
    {
        LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
        return nullptr;
    }
    else
    {
        LOG("Texture from path %s loaded correctly.", path.c_str());
    }

    SDL_Texture* texture = LoadSurface(surface);
    SDL_FreeSurface(surface);

    // Store the surface along with its path for reloading later
    textureSurfaces.push_back(std::make_pair(path, surface));

    if (texture)
    {
        textures.push_back(texture);
    }

    return texture;
}


void Textures::ReloadTextures()
{
	// Clear all current textures
	for (SDL_Texture* texture : textures)
	{
		SDL_DestroyTexture(texture);
	}
	textures.clear();

	// Recreate textures from the stored surfaces
	for (auto& surfacePair : textureSurfaces)
	{
		SDL_Texture* newTexture = LoadSurface(surfacePair.second);
		textures.push_back(newTexture); // Add the new texture to the textures vector
	}
}


bool Textures::UnLoad(SDL_Texture* texture)
{
	if (!texture) return false;

	auto it = std::find(textures.begin(), textures.end(), texture);
	if (it != textures.end())
	{
		SDL_DestroyTexture(*it);
		textures.erase(it);
		return true;
	}
	return false;
}

void Textures::GetSize(const SDL_Texture* texture, int& width, int& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, &width, &height);
}

SDL_Texture* const Textures::LoadSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::Singleton().renderer->GetRenderer(), surface);

	if (texture == NULL)
	{
		LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		textures.push_back(texture);
	}

	return texture;
}