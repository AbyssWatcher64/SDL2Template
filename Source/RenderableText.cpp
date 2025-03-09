#include "Engine.hpp"
#include "Renderer.hpp"
#include "Fonts.hpp"
#include "RenderableText.hpp"
#include "SDL2/SDL_ttf.h"

RenderableText::RenderableText(const std::string& text, Vector2D position, FontName font, SDL_Color color, bool forceDrawInsideCamera, int layer)
	: Renderable(layer, forceDrawInsideCamera)
{
	this->text = text;
	this->font = Engine::Singleton().fonts->GetFont(font);
	this->color = color;
	this->position = position;
}

RenderableText::~RenderableText()
{
	this->font = nullptr;
}

void RenderableText::Draw() const
{
	Engine::Singleton().renderer->DrawText(text, position, font, color, forceDrawInsideCamera);
}
