#ifndef RENDERABLETEXTURE
#define RENDERABLETEXTURE

#include "Renderable.hpp"

class RenderableTexture : public Renderable
{
public:
	RenderableTexture(SDL_Texture* texture, SDL_Rect& sourceRectangle, SDL_Rect& destinationRectangle, 
					  int basePoint, float angle, SDL_Point pivot, bool forceDrawInsideCamera, int layer);
	~RenderableTexture();
	void Draw() const override;

	int GetRenderBasePoint() const override;
	void SetRenderBasePoint(int newBasePoint) override;
	int GetYPosition() const override;

private:
	SDL_Texture* texture;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	int basePoint;
	float angle;
	SDL_Point pivot;
};

#endif