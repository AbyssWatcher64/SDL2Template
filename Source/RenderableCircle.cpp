#include "Engine.hpp"
#include "Renderer.hpp"
#include "RenderableCircle.hpp"

RenderableCircle::RenderableCircle(Vector2D centerPosition, int radius, SDL_Color color, bool forceDrawInsideCamera, int layer) 
	: Renderable(layer, forceDrawInsideCamera)
{
	this->centerPosition = centerPosition;
	this->radius = radius;
	this->color = color;

}

void RenderableCircle::Draw() const
{
	Engine::Singleton().renderer->DrawCircle(centerPosition, radius, color, forceDrawInsideCamera);
}
