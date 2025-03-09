#ifndef RENDERABLERECTANGLE
#define RENDERABLERECTANGLE

#include "Renderable.hpp"

class RenderableRectangle : public Renderable
{
public:
	RenderableRectangle(const SDL_Rect& rectangle, const SDL_Color color, bool filled, bool forceDrawInsideCamera, int layer);
	void Draw() const override;
private:
	SDL_Rect rectangle;
	bool filled;
	SDL_Color color;
};

#endif