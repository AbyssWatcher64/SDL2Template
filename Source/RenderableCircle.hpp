#ifndef RENDERABLECIRCLE
#define RENDERABLECIRCLE

#include "Renderable.hpp"

class RenderableCircle : public Renderable
{
public:
	RenderableCircle(Vector2D centerPosition, int radius, SDL_Color color, bool forceDrawInsideCamera, int layer);
	void Draw() const override;
private:
	Vector2D centerPosition;
	int radius;
	SDL_Color color;
};

#endif
