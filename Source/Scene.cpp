#include "PreCompileHeaders.h"
#include "Scene.hpp"
#include "Fonts.hpp"
#include "Renderer.hpp"
//#include "Input.hpp" // I don't think Input is necessary if we're using the InputPlayer functions.
#include "Window.hpp"
#include "Textures.hpp"
#include "Camera.hpp"
#include "PlayerInput.hpp"

// TestBed = Test Scene. Use it for all your testing.
Scene::Scene() : Module()
{
	name = "scene";
}

Scene::~Scene()
{

}

bool Scene::Awake()
{
	LOG("== Initializing Scene ==");
	bool ret = true;

	return ret;
}

bool Scene::Start()
{
	camera = Engine::Singleton().renderer->GetCamera(); 
	playerInput = std::make_shared<PlayerInput>();

	return true;
}

bool Scene::PreUpdate()
{

	return true;
}

bool Scene::Update(float dt)
{

	return true;
}

bool Scene::Render()
{
	return true;
}

bool Scene::PostUpdate()
{
	return true;
}

bool Scene::CleanUp()
{
	return true;
}