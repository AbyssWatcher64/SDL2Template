#include "Engine.hpp"
#include "Renderer.hpp"
#include "RenderableLine.hpp"


RenderableLine::RenderableLine(Vector2D start, Vector2D end, SDL_Color color, bool forceDrawInsideCamera, int layer) 
	: Renderable(layer, forceDrawInsideCamera)
{
	this->start = start;
	this->end = end;
	this->color = color;
}

void RenderableLine::Draw() const
{
	Engine::Singleton().renderer->DrawLine(start, end, color, forceDrawInsideCamera);
}
