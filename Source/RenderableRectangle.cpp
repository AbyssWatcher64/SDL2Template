#include "Engine.hpp"
#include "Renderer.hpp"
#include "RenderableRectangle.hpp"


RenderableRectangle::RenderableRectangle(const SDL_Rect& rectangle, const SDL_Color color, bool filled, bool forceDrawInsideCamera, int layer)
	: Renderable(layer, forceDrawInsideCamera) 
{
	this->rectangle = rectangle;
	this->color = color;
	this->filled = filled;
} 

void RenderableRectangle::Draw() const
{
	Engine::Singleton().renderer->DrawRectangle(rectangle, color, filled, forceDrawInsideCamera);
}
