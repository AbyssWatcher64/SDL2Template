#ifndef RENDERABLETEXT
#define RENDERABLETEXT

#include "Renderable.hpp"
#include <string>

class RenderableText : public Renderable
{
public:
	RenderableText(const std::string& text, Vector2D position, FontName font, SDL_Color color, bool forceDrawInsideCamera, int layer);
	~RenderableText();
	void Draw() const override;
private:
	std::string text;
	TTF_Font* font;
	Vector2D position;
	SDL_Color color;
};

#endif