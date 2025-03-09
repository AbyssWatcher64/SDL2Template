#include "SDL2/SDL_ttf.h"
#include "Renderer.hpp"
#include "Renderable.hpp"
#include "RenderableTexture.hpp"
#include "RenderableRectangle.hpp"
#include "RenderableCircle.hpp"
#include "RenderableLine.hpp"
#include "RenderableText.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "IniParser.hpp"
#include "Fonts.hpp" // REMOVE 

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

	std::unordered_map<std::string, std::string> configFile = LoadConfig("config.ini");
	bool vSync = GetBoolFromConfig(configFile, "vsync");

	Uint32 flags = SDL_RENDERER_ACCELERATED;
	if (vSync)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
		LOG("Renderer: Using vsync");
	}

	renderer = SDL_CreateRenderer(Engine::Singleton().window->GetWindow(), -1, flags);

	if (renderer == nullptr)
	{
		LOG("Renderer: Could not create the renderer! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (TTF_Init() == -1) {
		LOG("Renderer: Failed to initialize SDL_ttf: %s", TTF_GetError());
		return false;
	}
	LOG("Renderer: SDL_ttf initialized successfully!");

	return ret;
}

bool Renderer::Start()
{
	LOG("== Starting Renderer ==");
	// Sets background
	background.r = 0; background.g = 0; background.b = 0; background.a = 0;

	SDL_RenderGetViewport(renderer, &viewport);
	ResizeViewPort(Engine::Singleton().window->GetWindowWidth(), Engine::Singleton().window->GetWindowHeight());

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
	
	UpdateOffset();
	
	SortEntityDrawOrder();

	std::vector<std::unique_ptr<Renderable>>* layers[LAYER_TOTALCOUNT] = { &backgroundLayer, &worldLayer, &entityLayer, &overEntityLayer, &debugLayer, &uiLayer, &textuiLayer };

	for (auto* layer : layers)  // Iterate through layer pointers
	{
		for (const auto& renderable : *layer)  // Dereference the pointer to access the vector
		{
			renderable->Draw();
		}
		layer->clear(); 
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

void Renderer::UpdateOffset()
{
	offset.SetX(-camera->GetCameraXPosition());
	offset.SetY(-camera->GetCameraYPosition());
}

bool Renderer::QueueTexture(SDL_Texture* texture, SDL_Rect& sourceRect, SDL_Rect& destRect, bool forceDrawInsideCamera, int layer, int renderBasePoint, float angle, SDL_Point pivot)
{
	bool ret = true;
	if (!texture)
	{
		LOG("ERROR: QueueTexture received a nullptr texture.");
		ret = false;
	}

	std::unique_ptr<Renderable> renderable = std::make_unique<RenderableTexture>(texture, sourceRect, destRect, renderBasePoint, 
																		  angle, pivot, forceDrawInsideCamera, layer);
	AddRenderableToAppropriateLayer(std::move(renderable));

	return ret;
}

bool Renderer::QueueDebugRectangle(const SDL_Rect& rect, SDL_Color color, bool filled, bool forceDrawInsideCamera, int layer)
{
	std::unique_ptr<Renderable> renderable = std::make_unique<RenderableRectangle>(rect, color, filled, forceDrawInsideCamera, layer);
	AddRenderableToAppropriateLayer(std::move(renderable));

	return true;
}


bool Renderer::QueueDebugLine(Vector2D start, Vector2D end, SDL_Color color, bool forceDrawInsideCamera, int layer)
{
	std::unique_ptr<Renderable> renderable = std::make_unique<RenderableLine>(start, end, color, forceDrawInsideCamera, layer);
	AddRenderableToAppropriateLayer(std::move(renderable));

	return true;
}

bool Renderer::QueueDebugCircle(Vector2D centerPosition, int radius, SDL_Color color, bool forceDrawInsideCamera, int layer)
{
	std::unique_ptr<Renderable> renderable = std::make_unique<RenderableCircle>(centerPosition, radius, color, forceDrawInsideCamera, layer);
	AddRenderableToAppropriateLayer(std::move(renderable));

	return true;
}

bool Renderer::QueueText(const std::string& text, Vector2D position, FontName font, SDL_Color color, bool forceDrawInsideCamera, int layer)
{
	std::unique_ptr<Renderable> renderable = std::make_unique<RenderableText>(text, position, font, color, forceDrawInsideCamera, layer);
	AddRenderableToAppropriateLayer(std::move(renderable));

	return true;
}

void Renderer::AddRenderableToAppropriateLayer(std::unique_ptr<Renderable> renderable)
{
	switch (renderable->GetLayer())
	{
	default:
		LOG("ERROR: Renderable's layer's number is wrong. The number is %d.", renderable->GetLayer());
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
	case Renderer::OVER_ENTITY:
		overEntityLayer.emplace_back(std::move(renderable));
		break;
	case Renderer::DEBUG:
		debugLayer.emplace_back(std::move(renderable));
		break;
	case Renderer::UI:
		uiLayer.emplace_back(std::move(renderable));
		break;
	case Renderer::TEXT_UI:
		textuiLayer.emplace_back(std::move(renderable));
		break;
	}
}

void Renderer::SortEntityDrawOrder()
{
	UpdateEntitiesBasePoint();

	// Bubble swap
	int n = (int)entityLayer.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (entityLayer[j]->GetRenderBasePoint() > entityLayer[j + 1]->GetRenderBasePoint())
				swap(entityLayer[j], entityLayer[j + 1]);
		}
	}
}

void Renderer::UpdateEntitiesBasePoint()
{
	for (const auto& renderable : entityLayer)
	{
		renderable->SetRenderBasePoint(renderable->GetRenderBasePoint() + renderable->GetYPosition());
		//renderable->SetRenderBasePoint(renderable->GetRenderBasePoint() + renderable->destRect.y;
	}
}

void Renderer::DrawTexture(SDL_Texture* texture, const SDL_Rect& sourceRect, const SDL_Rect& destRect, float angle, SDL_Point pivot, bool forceDrawInsideCamera)
{
	if (!texture)
	{
		LOG("ERROR: DrawTexture received a nullptr texture.");
		return;
	}

	int offsetX = forceDrawInsideCamera ? 0 : offset.GetX();
	int offsetY = forceDrawInsideCamera ? 0 : offset.GetY();
	SDL_Rect renderingRectangle({ destRect.x + offsetX, destRect.y + offsetY, destRect.w, destRect.h });

	if (SDL_RenderCopyEx(renderer, texture, &sourceRect, &renderingRectangle, (double)angle, &pivot, SDL_FLIP_NONE) != 0)
	{
		LOG("SDL_RenderCopyEx failed: %s", SDL_GetError());
	}
}

void Renderer::DrawRectangle(const SDL_Rect& rectangle, SDL_Color color, bool filled, bool forceDrawInsideCamera)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	int offsetX = forceDrawInsideCamera ? 0 : offset.GetX();
	int offsetY = forceDrawInsideCamera ? 0 : offset.GetY();
	SDL_Rect renderingRectangle({ rectangle.x + offsetX, rectangle.y + offsetY, rectangle.w, rectangle.h });

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
	int offsetX = forceDrawInsideCamera ? 0 : offset.GetX();
	int offsetY = forceDrawInsideCamera ? 0 : offset.GetY();
	//Vector2D offset = SetOffset(forceDrawInsideCamera);
	SDL_RenderDrawLine(renderer, originVector.GetX() + offsetX, originVector.GetY() + offsetY,
									endVector.GetX() + offsetX, endVector.GetY()	  + offsetY);
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

	int offsetX = forceDrawInsideCamera ? 0 : offset.GetX();
	int offsetY = forceDrawInsideCamera ? 0 : offset.GetY();

	for (int i = 0; i < 360; ++i)
	{

		points[i].x = (int)(vector.GetX() + offsetX + (int)(radius * cos(i * factor)));
		points[i].y = (int)(vector.GetY() + offsetY + (int)(radius * sin(i * factor)));
	}

	SDL_RenderDrawPoints(renderer, points, 360);
}

void Renderer::DrawText(const std::string& text, Vector2D position, TTF_Font* font, SDL_Color color, bool forceDrawInsideCamera)
{
	SDL_Texture* textTexture = CreateTextTexture(text, font, color);
	if (!textTexture)
	{
		font = nullptr;
		return;
	}

	int offsetX = forceDrawInsideCamera ? 0 : offset.GetX();
	int offsetY = forceDrawInsideCamera ? 0 : offset.GetY();

	SDL_Rect textRect;
	TTF_SizeText(font, text.c_str(), &textRect.w, &textRect.h); // Get text dimensions
	textRect.x = position.GetX() + offsetX;
	textRect.y = position.GetY() + offsetY;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
	SDL_DestroyTexture(textTexture); // Free texture after rendering
}

SDL_Texture* Renderer::CreateTextTexture(const std::string& text, TTF_Font* font, SDL_Color color)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (!textSurface) 
	{
		LOG("Failed to create text surface: %s", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface); // Free the surface after creating the texture

	if (!textTexture) 
	{
		LOG("Failed to create text texture: %s", SDL_GetError());
	}

	return textTexture;
}

SDL_Renderer* Renderer::GetRenderer() const
{
	return renderer;
}

std::shared_ptr<Camera> Renderer::GetCamera()
{
	return camera;
}