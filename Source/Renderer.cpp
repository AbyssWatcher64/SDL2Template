//#include "PreCompileHeaders.h"
#include "Renderer.hpp"

// Constructor
Renderer::Renderer()
{
	renderer = NULL;
	name = "renderer";

	// Set background to transparent
	// TODO: Revise if necessary.
	background.r = 0; background.g = 0; background.b = 0; background.a = 0;
}

// Destructor
Renderer::~Renderer()
{

}

// Module Functions
bool Renderer::Awake()
{
	return true;
}

bool Renderer::Start()
{
	return true;
}

bool Renderer::PreUpdate()
{
	return true;
}

bool Renderer::Update(float dt)
{
	return true;
}

bool Renderer::PostUpdate()
{
	return true;
}

bool Renderer::CleanUp()
{
	return true;
}

// Viewports
void Renderer::SetViewPort(const SDL_Rect& rect)
{

}

void Renderer::ResetViewPort()
{

}

