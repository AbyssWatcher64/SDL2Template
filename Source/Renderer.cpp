//#include "PreCompileHeaders.h"
#include "Renderer.hpp"
#include "Window.hpp"

// Constructor
Renderer::Renderer()
{
	renderer = nullptr;
	name = "renderer";

	// Set background to transparent
	// TODO: Revise if necessary.
	background.r = 0; background.g = 0; background.b = 0; background.a = 0;
}

// Destructor
Renderer::~Renderer()
{

}

// Module Functions
bool Renderer::Awake()
{
	// TODO: Get this better.
	LOG("== Initializing Renderer ==");
	bool ret = true;

	Uint32 flags = SDL_RENDERER_ACCELERATED;

	//L05 TODO 5 - Load the configuration of the Renderer module
	//if (configParameters.child("vsync").attribute("value").as_bool() == true) {
	//	flags |= SDL_RENDERER_PRESENTVSYNC;
	//	LOG("Using vsync");
	//}
	// Forcing VSync for the time being.
	flags |= SDL_RENDERER_PRESENTVSYNC;
	LOG("Using vsync");

	int scale = Engine::Singleton().window.get()->GetScale();

	SDL_Window* window = Engine::Singleton().window->GetWindow();
	renderer = SDL_CreateRenderer(window, -1, flags);

	if (renderer == NULL)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//// Nothing seems to change this
		//camera.w = Engine::GetInstance().window.get()->width * scale;
		//camera.h = Engine::GetInstance().window.get()->height * scale;
		//camera.x = 0;
		//camera.y = 0;
	}

	return ret;
}

bool Renderer::Start()
{
	LOG("== Starting Renderer ==");
	// back background
	/*timer = new Timer();
	timer->Start();*/
	SDL_RenderGetViewport(renderer, &viewport);
	return true;
}

bool Renderer::PreUpdate()
{
	SDL_RenderClear(renderer);
	return true;
}

bool Renderer::Update(float dt)
{
	return true;
}

bool Renderer::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.g, background.a);
	SDL_RenderPresent(renderer);
	return true;
}

bool Renderer::CleanUp()
{
	LOG("== Destroying SDL renderer ==");
	SDL_DestroyRenderer(renderer);
	return true;
}

// Viewports
void Renderer::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

// MEGATEMP - TODO: Fix this.
bool Renderer::ResizeViewPort(int screenWidth, int screenHeight)
{
    int cameraWidth = camera.w;
    int cameraHeight = camera.h;

    // Get screen and camera aspect ratios
    float screenAspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
    float cameraAspect = static_cast<float>(cameraWidth) / static_cast<float>(cameraHeight);

    // Determine new viewport size based on aspect ratios
    SDL_Rect newViewport;

    if (screenAspect > cameraAspect) {
        // Letterbox scenario: We scale based on height
        newViewport.h = screenHeight;
        newViewport.w = static_cast<int>(screenHeight * cameraAspect);
        newViewport.x = (screenWidth - newViewport.w) / 2;  // Center horizontally
        newViewport.y = 0;
    }
    else {
        // Pillarbox scenario: We scale based on width
        newViewport.w = screenWidth;
        newViewport.h = static_cast<int>(screenWidth / cameraAspect);
        newViewport.x = 0;
        newViewport.y = (screenHeight - newViewport.h) / 2;  // Center vertically
    }

    // Set the new viewport
    SDL_RenderSetViewport(renderer, &newViewport);

    // Update the camera's scaling factor based on the new resolution
    camera.x = newViewport.x;
    camera.y = newViewport.y;
    camera.w = newViewport.w;
    camera.h = newViewport.h;

    return true;
}

void Renderer::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

bool Renderer::DrawTexture(SDL_Texture* texture, Vector2D vector, const SDL_Rect* section, bool useCamera, float speed, double angle, int pivotX, int pivotY) const
{
	bool ret = true;
	int scale = Engine::Singleton().window.get()->GetScale();

	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + vector.GetX() * scale;
	rect.y = (int)(camera.y * speed) + vector.GetY() * scale;

	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}


	if (!useCamera)
	{
		rect.x = (int)(vector.GetX() * scale);
		rect.y = (int)(vector.GetY() * scale);
	}

	rect.w *= scale;
	rect.h *= scale;


	SDL_Point* p = NULL;
	SDL_Point pivot;

	if (pivotX != INT_MAX && pivotY != INT_MAX)
	{
		pivot.x = pivotX;
		pivot.y = pivotY;
		p = &pivot;
	}

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, angle, p, SDL_FLIP_NONE) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

//bool Renderer::DrawTextureDifferentScale(SDL_Texture* texture, Vector2D vector, const SDL_Rect* section = NULL, int scaleFactor = 3, bool useCamera = true, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const
//{
//
//}

bool Renderer::DrawRectangle(const SDL_Rect& rect, SDL_Color rgb, bool filled, bool useCamera) const
{
	bool ret = true;
	int scale = Engine::Singleton().window.get()->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);

	SDL_Rect rec(rect);
	if (useCamera)
	{
		rec.x = (int)(camera.x + rect.x * scale);
		rec.y = (int)(camera.y + rect.y * scale);
		rec.w *= scale;
		rec.h *= scale;
	}

	int result = (filled) ? SDL_RenderFillRect(renderer, &rec) : SDL_RenderDrawRect(renderer, &rec);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Renderer::DrawLine(Vector2D vector1, Vector2D vector2, SDL_Color rgb, bool useCamera) const
{
	bool ret = true;
	int scale = Engine::Singleton().window.get()->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);

	int result = -1;

	if (useCamera)
		result = SDL_RenderDrawLine(renderer, camera.x + vector1.GetX() * scale, camera.y + vector1.GetY() * scale, camera.x + vector2.GetX() * scale, camera.y + vector2.GetY() * scale);
	else
		result = SDL_RenderDrawLine(renderer, vector1.GetX() * scale, vector1.GetY() * scale, vector2.GetX() * scale, vector2.GetY() * scale);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Renderer::DrawCircle(Vector2D vector, int radius, SDL_Color rgb, bool useCamera) const
{
	bool ret = true;
	int scale = Engine::Singleton().window.get()->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);

	int result = -1;
	SDL_Point points[360];

	float factor = (float)M_PI / 180.0f;

	for (int i = 0; i < 360; ++i)
	{
		points[i].x = (int)(vector.GetX() * scale + camera.x) + (int)(radius * cos(i * factor));
		points[i].y = (int)(vector.GetY() * scale + camera.y) + (int)(radius * sin(i * factor));
	}

	result = SDL_RenderDrawPoints(renderer, points, 360);

	if (result != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}