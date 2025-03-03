#include "PreCompileHeaders.h"
#include "Scene.hpp"
#include "Renderer.hpp"
#include "Input.hpp"
#include "Window.hpp"
#include "Textures.hpp"
#include "Camera.hpp"

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
	TMPPlayerTexture = Engine::Singleton().textures->Load("./Assets/Textures/Characters/GutsPixelArt_PROVISIONAL.png");
	return true;
}

bool Scene::PreUpdate()
{

	return true;
}

bool Scene::Update(float dt)
{
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{
		TMPPlayerTexture = Engine::Singleton().textures->Load("./Assets/Textures/Characters/GutsPixelArt_PROVISIONAL.png");
	}
	return true;
}

bool Scene::Render()
{
	SDL_Rect rect({ 0,0,0,0 });
	Engine::Singleton().renderer->QueueDebugRectangle(SDL_Rect({ 0,0,50,50 }), { 0,0,255,255 }, true, false, Renderer::UI);
	Engine::Singleton().renderer->QueueDebugRectangle(SDL_Rect({0,0,352,224}), {0,255,0,255}, true, true, Renderer::BACKGROUND);
	Engine::Singleton().renderer->QueueDebugRectangle(SDL_Rect({10,10,332,204}), {0,122,255,255}, true, true, Renderer::BACKGROUND);
	Engine::Singleton().renderer->QueueDebugRectangle(SDL_Rect({0,0,100,100}), {255,0,0,255}, true, false);

	//Engine::Singleton().renderer->QueueDebugCircle({ 100,100 }, 20, { 255,0,0,255 }, false, Renderer::DEBUG);
	Engine::Singleton().renderer->QueueDebugCircle({ 176,224 / 2 }, 30, { 255,255,0,255 }, false, Renderer::UI);
	Engine::Singleton().renderer->QueueDebugCircle({ 0,0 }, 10, { 255,255,0,255 }, false, Renderer::UI);
	Engine::Singleton().renderer->QueueDebugCircle({ 10,10 }, 10, { 255,255,0,255 }, true, Renderer::UI);
	Engine::Singleton().renderer->QueueDebugRectangle(SDL_Rect({ 352 / 2, 224 / 2,1,1 }), { 255,0,0,255 }, true, true, Renderer::UI);
	Engine::Singleton().renderer->QueueDebugLine({ 0,0 }, { 100,200 }, { 0,255,255,255 }, false, Renderer::UI);

	SDL_Rect rectangle = SDL_Rect({ 0,0,48,67 });
	Engine::Singleton().renderer->QueueTexture(TMPPlayerTexture, rectangle, false, Renderer::ENTITY);

	// TEMP Player movement
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if (TEMPPosition.GetX() < 352)
		{
			TEMPPosition.SetX(TEMPPosition.GetX() + 1);
		}
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if (TEMPPosition.GetX() > 0)
		{
			TEMPPosition.SetX(TEMPPosition.GetX() - 1);
		}
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		if (TEMPPosition.GetY() > 0)
		{
			TEMPPosition.SetY(TEMPPosition.GetY() - 1);
		}
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		if (TEMPPosition.GetY() < 224)
		{
			TEMPPosition.SetY(TEMPPosition.GetY() + 1);
		}
	}
	Engine::Singleton().renderer->QueueDebugCircle({ TEMPPosition.GetX(),TEMPPosition.GetY() }, 10, {255,255,0,255}, false, Renderer::UI);
	camera->SetCenterCameraView({ TEMPPosition.GetX(),TEMPPosition.GetY() });


		



	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		Engine::Singleton().window->ChangeResolution(1920, 1080);
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		Engine::Singleton().window->ChangeResolution(1080, 720);
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		Engine::Singleton().window->ChangeResolution(352, 224);
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		Engine::Singleton().window->ChangeResolution(2560, 1440);
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
	{
		camera->SetCenterCameraViewWithLerp({ 176 / 2, 224 / 2 });
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
	{
		camera->SetCenterCameraViewWithLerp({ 352 / 2, 224 / 2 });
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
	{
		camera->SetCenterCameraView({ 352 / 2, 224 / 2 });
	}
	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
	{
		return false;
	}

	if (Engine::Singleton().input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		Engine::Singleton().window->ToggleFullScreen();
	}




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