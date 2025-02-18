#pragma once

#include "Module.hpp"
#include "Vector2D.hpp"

class Renderer : public Module
{
public:
	// Constructor
	Renderer();

	// Destructor
	~Renderer();

	// Module Functions
	bool Awake() override;
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool CleanUp() override;

	// Viewports
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();

	// Drawing
	bool DrawTexture(SDL_Texture* texture, Vector2D vector, const SDL_Rect* section = NULL, bool useCamera = true, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;
	bool DrawTextureDifferentScale(SDL_Texture* texture, Vector2D vector, const SDL_Rect* section = NULL, int scaleFactor = 3, bool useCamera = true, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;
	bool DrawRectangle(const SDL_Rect& rect, SDL_Color rgb, bool filled = true, bool useCamera = true) const;
	bool DrawLine(Vector2D vector1, Vector2D vector2, SDL_Color rgb, bool useCamera = true) const;
	bool DrawCircle(Vector2D vector, int radius, SDL_Color rgb, bool useCamera = true) const;
	// Commenting because I'm trying with the RGB struct and Vector instead of two points
	//bool DrawRectangle(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool useCamera = true) const;
	//bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;
	//bool DrawCircle(int x1, int y1, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool useCamera = true) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

	// Getter of the renderer
	SDL_Renderer* GetRenderer() const;

	// FadeIn & FadeOut will come from another class

private:
	SDL_Renderer* renderer;
	SDL_Rect camera;
	SDL_Rect viewport;
	SDL_Color background;

};