#ifndef RENDERABLE
#define RENDERABLE

#include "SDL2/SDL_image.h"
#include "Vector2D.hpp"

class Renderable
{
public:
	enum RenderType { TEXTURE, RECTANGLE, LINE, CIRCLE };
	Renderable(SDL_Texture* texture, SDL_Rect& section, bool forceDrawInsideCamera, int layer, double angle, int pivotX, int pivotY);
	Renderable(const SDL_Rect& rect, const SDL_Color color, bool filled, bool forceDrawInsideCamera, int layer);
	Renderable(Vector2D start, Vector2D end, SDL_Color color, bool forceDrawInsideCamera, int layer);
	Renderable(Vector2D center, int radius, SDL_Color color, bool forceDrawInsideCamera, int layer);
	~Renderable();

	//RenderType GetType() const;
	//int GetLayer() const;

public:
	SDL_Texture* texture;

	RenderType type;
	SDL_Rect rect;
	int layer;
	double angle;
	SDL_Point pivot;
	bool forceDrawInsideCamera;
	SDL_Color color; // New field for debug shapes
	Vector2D point1, point2; // For lines
	int radius; // For circles
	bool filled;
};

#endif