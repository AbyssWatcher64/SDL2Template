#include "Renderer.hpp"
#include "Renderable.hpp"
#include "Window.hpp"
#include "Camera.hpp"

Renderer::Renderer()
{
	renderer = nullptr;
	name = "renderer";

	// Create camera
	camera = std::make_shared<Camera>();
}

Renderer::~Renderer() {}


bool Renderer::Awake()
{
	LOG("== Initializing Renderer ==");
	bool ret = true;

	Uint32 flags = SDL_RENDERER_ACCELERATED;

	// TODO: Change this to use player configuration settings
	// Forcing VSync for the time being.
	flags |= SDL_RENDERER_PRESENTVSYNC;
	LOG("Using vsync");

	renderer = SDL_CreateRenderer(Engine::Singleton().window->GetWindow(), -1, flags);

	if (renderer == nullptr)
	{
		LOG("Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool Renderer::Start()
{
	LOG("== Starting Renderer ==");
	// Sets background
	background.r = 0; background.g = 0; background.b = 0; background.a = 0;

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
	camera->Update();
	return true;
}

bool Renderer::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
	SDL_RenderClear(renderer);

	std::vector<std::unique_ptr<Renderable>>* layers[LAYER_TOTALCOUNT] = {
		&backgroundLayer, &worldLayer, &entityLayer, &overEntityLayer, &debugLayer, &uiLayer
	};

	int i = 0;
	for (auto* layer : layers)  // Iterate through layer pointers
	{
		for (const auto& r : *layer)  // Dereference the pointer to access the vector
		{
			switch (r->type)
			{
			case Renderable::RenderType::TEXTURE:
				DrawTexture(r->texture, r->rect, r->forceDrawInsideCamera, r->layer, r->angle, r->pivot.x, r->pivot.y);
				break;

			case Renderable::RenderType::RECTANGLE:
				DrawRectangle(r->rect, r->color, r->forceDrawInsideCamera, r->filled);
				break;

			case Renderable::RenderType::LINE:
				DrawLine(r->point1, r->point2, r->color, r->forceDrawInsideCamera);
				break;

			case Renderable::RenderType::CIRCLE:
				DrawCircle(r->point1, r->radius, r->color, r->forceDrawInsideCamera);
				break;
			}
		}
		layer->clear();  // Use `layer->clear()` since it's now a pointer to a vector
	}


	SDL_RenderPresent(renderer);
	return true;
}

bool Renderer::CleanUp()
{
	LOG("== Destroying SDL renderer ==");
	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	return true;
}

void Renderer::RecreateRenderer()
{
	LOG("Recreating Renderer due to resolution change");

	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	renderer = SDL_CreateRenderer(Engine::Singleton().window->GetWindow(), -1, flags);

	if (renderer == nullptr)
	{
		LOG("Could not recreate renderer! SDL_Error: %s", SDL_GetError());
	}
}

void Renderer::SetViewPort(const SDL_Rect& rect)
{
	SDL_RenderSetViewport(renderer, &rect);
}

bool Renderer::ResizeViewPort(int screenWidth, int screenHeight)
{
	SetNewScreenWidthAndHeight(screenWidth, screenHeight);

	float screenAspect = static_cast<float>(newScreenWidth) / newScreenHeight;

	SDL_Rect newViewport;

	UseLetterBoxOrPillarBox(newViewport, screenAspect);

	// Apply new viewport
	SDL_RenderSetViewport(renderer, &newViewport);

	// Set logical size for automatic scaling
	SDL_RenderSetLogicalSize(renderer, baseWidth, baseHeight);

	LOG("Updated viewport to: %d x %d", newScreenWidth, newScreenHeight);
	return true;
}

void Renderer::SetNewScreenWidthAndHeight(int screenWidth, int screenHeight)
{
	newScreenWidth = screenWidth;
	newScreenHeight = screenHeight;
}

void Renderer::UseLetterBoxOrPillarBox(SDL_Rect& newViewport, const float screenAspect)
{
	if (screenAspect > baseAspectRatio)
	{
		UseLetterBox(newViewport);
	}
	else
	{
		UsePillarBox(newViewport);
	}
}

// Letterbox means black bars on left and right
void Renderer::UseLetterBox(SDL_Rect& newViewport)
{
	newViewport.h = newScreenHeight;
	newViewport.w = static_cast<int>(newScreenHeight * baseAspectRatio);
	newViewport.x = (newScreenWidth - newViewport.w) / 2;
	newViewport.y = 0;
}

// Pillarbox means black bars on top and bottom
void Renderer::UsePillarBox(SDL_Rect& newViewport)
{
	newViewport.w = newScreenWidth;
	newViewport.h = static_cast<int>(newScreenWidth / baseAspectRatio);
	newViewport.x = 0;
	newViewport.y = (newScreenHeight - newViewport.h) / 2;
}


void Renderer::ResetViewPort()
{
	SDL_RenderSetViewport(renderer, &viewport);
}

Vector2D Renderer::SetOffset(bool forceDrawInsideCamera)
{
	Vector2D offset = Vector2D();
	if (forceDrawInsideCamera)
	{
		offset.SetX(0);
		offset.SetY(0);
	}
	else
	{
		offset.SetX(-camera->GetCameraXPosition());
		offset.SetY(-camera->GetCameraYPosition());
		//offsetX = -camera->GetCameraXPosition();
		//offsetY = -camera->GetCameraYPosition();
	}
	return offset;
}

bool Renderer::QueueTexture(SDL_Texture* texture, SDL_Rect& section, bool forceDrawInsideCamera, int layer, double angle, int pivotX, int pivotY)
{
	// TODO: EDIT THIS TO WORK with the new structure
	bool ret = true;
	if (!texture)
	{
		LOG("ERROR: QueueTexture received a nullptr texture.");
		ret = false;
	}

	std::unique_ptr<Renderable> renderable = std::make_unique<Renderable>(texture, section, forceDrawInsideCamera, layer, angle, pivotX, pivotY);
	AddRenderableToAppropriateLayer(std::move(renderable));

	return ret;
}

bool Renderer::QueueDebugRectangle(const SDL_Rect& rect, SDL_Color color, bool filled, bool forceDrawInsideCamera, int layer)
{
	std::unique_ptr<Renderable> renderable = std::make_unique<Renderable>(rect, color, filled, forceDrawInsideCamera, layer);
	AddRenderableToAppropriateLayer(std::move(renderable));

	return true;
}


bool Renderer::QueueDebugLine(Vector2D start, Vector2D end, SDL_Color color, bool forceDrawInsideCamera, int layer)
{
	std::unique_ptr<Renderable> renderable = std::make_unique<Renderable>(start, end, color, forceDrawInsideCamera, layer);
	AddRenderableToAppropriateLayer(std::move(renderable));

	return true;
}

bool Renderer::QueueDebugCircle(Vector2D center, int radius, SDL_Color color, bool forceDrawInsideCamera, int layer)
{
	std::unique_ptr<Renderable> renderable = std::make_unique<Renderable>(center, radius, color, forceDrawInsideCamera, layer);
	AddRenderableToAppropriateLayer(std::move(renderable));

	return true;
}

void Renderer::AddRenderableToAppropriateLayer(std::unique_ptr<Renderable> renderable)
{
	switch (renderable->layer)
	{
	default:
		LOG("ERROR: Renderable's layer's number is wrong. The number is %d.", renderable->layer);
		LOG("The Renderable layer number should be between 0 and %d.", (Renderer::Layer::LAYER_TOTALCOUNT - 1));
		break;
	case Renderer::BACKGROUND:
		backgroundLayer.emplace_back(std::move(renderable));
		break;
	case Renderer::WORLD:
		worldLayer.emplace_back(std::move(renderable));
		break;
	case Renderer::ENTITY:
		entityLayer.emplace_back(std::move(renderable));
		break;
	case Renderer::OVERENTITY:
		overEntityLayer.emplace_back(std::move(renderable));
		break;
	case Renderer::DEBUG:
		debugLayer.emplace_back(std::move(renderable));
		break;
	case Renderer::UI:
		uiLayer.emplace_back(std::move(renderable));
		break;
	}
}

void Renderer::DrawTexture(SDL_Texture* texture, SDL_Rect& srcRect, bool forceDrawInsideCamera, int layer, double angle, int pivotX, int pivotY)
{
	if (!texture)
	{
		LOG("ERROR: DrawTexture received a nullptr texture.");
		return;
	}

	//SDL_Rect dstRect = srcRect; // Destination rectangle (could be modified if necessary)
	Vector2D offset = SetOffset(forceDrawInsideCamera);
	SDL_Rect dstRect = { 180+offset.GetX(), 50+offset.GetY(), srcRect.w, srcRect.h}; // Destination rectangle (could be modified if necessary)

	SDL_Point pivot = { pivotX, pivotY };

	if (SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle, &pivot, SDL_FLIP_NONE) != 0)
	{
		LOG("SDL_RenderCopyEx failed: %s", SDL_GetError());
	}
	//SDL_RenderCopyEx(renderer, texture, &srcRect, &dstRect, angle, nullptr/*&pivot*/, SDL_FLIP_NONE);
}

void Renderer::DrawRectangle(SDL_Rect& rectangle, SDL_Color color, bool forceDrawInsideCamera, bool filled)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	Vector2D offset = SetOffset(forceDrawInsideCamera);
	SDL_Rect renderingRectangle({ rectangle.x + offset.GetX(), rectangle.y + offset.GetY(), rectangle.w, rectangle.h });

	if (filled)
	{
		SDL_RenderFillRect(renderer, &renderingRectangle);
	}
	else
	{

		SDL_RenderDrawRect(renderer, &renderingRectangle);
	}
}

void Renderer::DrawLine(Vector2D originVector, Vector2D endVector, SDL_Color color, bool forceDrawInsideCamera)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	Vector2D offset = SetOffset(forceDrawInsideCamera);
	SDL_RenderDrawLine(renderer, originVector.GetX() + offset.GetX(), originVector.GetY() + offset.GetY(), 
									endVector.GetX() + offset.GetX(), endVector.GetY()	  + offset.GetY());
}

bool Renderer::DrawCircle(Vector2D vector, int radius, SDL_Color rgb, bool forceDrawInsideCamera)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);

	DrawCircleInternal(vector, radius, forceDrawInsideCamera);  // Call internal function
	return true;
}

void Renderer::DrawCircleInternal(Vector2D vector, int radius, bool forceDrawInsideCamera) 
{
	SDL_Point points[360];
	float factor = (float)M_PI / 180.0f;

	Vector2D offset = SetOffset(forceDrawInsideCamera);

	for (int i = 0; i < 360; ++i)
	{

		points[i].x = (int)(vector.GetX() + offset.GetX() + (int)(radius * cos(i * factor)));
		points[i].y = (int)(vector.GetY() + offset.GetY() + (int)(radius * sin(i * factor)));
	}

	SDL_RenderDrawPoints(renderer, points, 360);
}

SDL_Renderer* Renderer::GetRenderer() const
{
	return renderer;
}

std::shared_ptr<Camera> Renderer::GetCamera()
{
	return camera;
}