#include "Engine.hpp"
#include "Renderer.hpp"
#include "RenderableTexture.hpp"

RenderableTexture::RenderableTexture(SDL_Texture* texture, SDL_Rect& sourceRectangle, SDL_Rect& destinationRectangle,
									 int basePoint, float angle, SDL_Point pivot, bool forceDrawInsideCamera, int layer)
: Renderable(layer, forceDrawInsideCamera)
{
	this->texture = texture;
	this->sourceRectangle = sourceRectangle;
	this->destinationRectangle = destinationRectangle;
	this->basePoint = basePoint;
	this->angle = angle;
	this->pivot = pivot;
}

RenderableTexture::~RenderableTexture()
{
	this->texture = nullptr;
}

void RenderableTexture::Draw() const
{
	Engine::Singleton().renderer->DrawTexture(texture, sourceRectangle, destinationRectangle, angle, pivot, forceDrawInsideCamera);
}

int RenderableTexture::GetRenderBasePoint() const
{
	return basePoint;
}

void RenderableTexture::SetRenderBasePoint(int newBasePoint)
{
	basePoint = newBasePoint;
}

int RenderableTexture::GetYPosition() const
{
	return destinationRectangle.y;
}