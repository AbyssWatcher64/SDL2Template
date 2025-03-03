#include "Renderable.hpp"
#include "SDL2/SDL_render.h"
#include <iostream>

Renderable::Renderable(SDL_Texture* texture, SDL_Rect& section, bool forceDrawInsideCamera, int layer, double angle, int pivotX, int pivotY)
{
	this->type = RenderType::TEXTURE;
	this->texture = texture;
	this->pivot.x = pivotX;
	this->pivot.y = pivotY;
	this->forceDrawInsideCamera = forceDrawInsideCamera;
	this->rect = section;
	this->layer = layer;
	this->angle = angle;
}

Renderable::Renderable(const SDL_Rect& rect, const SDL_Color color, bool filled, bool forceDrawInsideCamera, int layer)
{
	this->type = RenderType::RECTANGLE;
	this->rect = rect;
	this->color = color;
	this->forceDrawInsideCamera = forceDrawInsideCamera;
	this->layer = layer;
	this->filled = filled;
}

Renderable::Renderable(Vector2D start, Vector2D end, SDL_Color color, bool forceDrawInsideCamera, int layer)
{
	this->type = RenderType::LINE;
	this->point1 = start;
	this->point2 = end;
	this->color = color;
	this->forceDrawInsideCamera = forceDrawInsideCamera;
	this->layer = layer;
}

Renderable::Renderable(Vector2D center, int radius, SDL_Color color, bool forceDrawInsideCamera, int layer)
{
	this->type = RenderType::CIRCLE;
	this->point1 = center;
	this->radius = radius;
	this->color = color;
	this->forceDrawInsideCamera = forceDrawInsideCamera;
	this->layer = layer;
}

Renderable::~Renderable()
{

}

//Renderable::RenderType Renderable::GetType() const
//{
//	return this->type;
//}
//
//int Renderable::GetLayer() const
//{
//	return this->layer;
//}