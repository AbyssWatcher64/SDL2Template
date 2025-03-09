#ifndef RENDERABLELINE
#define RENDEARBLELINE

#include "Renderable.hpp"

class RenderableLine : public Renderable
{
public:
	RenderableLine(Vector2D start, Vector2D end, SDL_Color color, bool forceDrawInsideCamera, int layer);
	void Draw() const override;
private:
	Vector2D start; 
	Vector2D end;
	SDL_Color color;
};

#endif