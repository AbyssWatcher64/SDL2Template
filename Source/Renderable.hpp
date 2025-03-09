#ifndef RENDERABLE
#define RENDERABLE

#include "PreCompileHeaders.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h" // necessary?
#include "Vector2D.hpp"

class Renderable
{
public:
	enum RenderType { TEXTURE, RECTANGLE, LINE, CIRCLE, TEXT };
	Renderable(SDL_Texture* texture, SDL_Rect& sourceRect, SDL_Rect& destRect, bool forceDrawInsideCamera, int layer, int basePoint, double angle, int pivotX, int pivotY);
	Renderable(const SDL_Rect& rect, const SDL_Color color, bool filled, bool forceDrawInsideCamera, int layer);
	Renderable(Vector2D start, Vector2D end, SDL_Color color, bool forceDrawInsideCamera, int layer);
	Renderable(Vector2D center, int radius, SDL_Color color, bool forceDrawInsideCamera, int layer);
	Renderable(const std::string& text, TTF_Font* font, Vector2D position, bool forceDrawInsideCamera, int layer, SDL_Color color);
	~Renderable();

	//RenderType GetType() const;
	//int GetLayer() const;

public:
	SDL_Texture* texture;

	RenderType type;
	SDL_Rect sourceRect;
	SDL_Rect destRect;
	SDL_Rect rect;
	int layer;
	int basePoint;
	double angle;
	SDL_Point pivot;
	bool forceDrawInsideCamera;
	SDL_Color color; // New field for debug shapes
	Vector2D position;
	Vector2D point1, point2; // For lines
	int radius; // For circles
	bool filled;

	std::string text;
	TTF_Font* font;
};

#endif