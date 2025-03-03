#include "PreCompileHeaders.h" //Engine.h included in the PCH

// Module includes
#include "Window.hpp"
#include "Input.hpp"
#include "Textures.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"


Engine::Engine()
{
	frameTimer = PrecisionTimer();
	lastSecFrameTimer = PrecisionTimer();

	// TODO: Include all modules
	window = std::make_shared<Window>();		AddModule(window);
	input = std::make_shared<Input>();			AddModule(input);
	textures = std::make_shared<Textures>();	AddModule(textures);
	scene = std::make_shared<Scene>();			AddModule(scene);
	renderer = std::make_shared<Renderer>();	AddModule(renderer);
}

Engine& Engine::Singleton()
{
	static Engine singleton;
	return singleton;
}

void Engine::AddModule(std::shared_ptr<Module> module)
{
	module->Init();
	moduleList.emplace_back(module);
}

int Engine::Run() 
{
    return fsm.Run();
}

//TEMP
bool Engine::Awake()
{
	bool result = true;
	for (const auto& module : moduleList) 
	{
		//module.get()->LoadParameters(configFile.child("config").child(module.get()->name.c_str()));
		result = module.get()->Awake();
		if (!result) {
			break;
		}
	}
	return true;
}

//TEMP
bool Engine::Start()
{
	bool result = true;
	for (const auto& module : moduleList)
	{
		//module.get()->LoadParameters(configFile.child("config").child(module.get()->name.c_str()));
		result = module.get()->Start();
		if (!result) {
			break;
		}
	}
	return true;
}

// Called each loop iteration
bool Engine::Loop()
{
	bool ret = true;
	PrepareUpdate();

	/*if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;*/
	if (ret == true)	ret = PreUpdate();
	if (ret == true)	ret = DoUpdate();
	if (ret == true)	ret = DoRender();
	if (ret == true)	ret = PostUpdate();

	FinishUpdate();

	return ret;
}

//TEMP
bool Engine::CleanUp()
{
	bool result = true;
	for (const auto& module : moduleList) 
	{
		result = module.get()->CleanUp();
		if (!result) 
		{
			break;
		}
	}

	return result;
}

bool Engine::GetIsDebugModeActive() const
{
	return isDebugModeActive;
}

void Engine::SetIsDebugModeActive(bool value)
{
	isDebugModeActive = value;
}


void Engine::PrepareUpdate()
{
	frameTimer.Start();
}

void Engine::FinishUpdate()
{
	double currentDt = frameTimer.ReadMs();
	if (maxFrameDuration > 0 && currentDt < maxFrameDuration) 
	{
		int delay = (int)(maxFrameDuration - currentDt);

		// L03: TODO 2: Measure accurately the amount of time SDL_Delay() actually waits compared to what was expected
		PrecisionTimer delayTimer = PrecisionTimer();
		SDL_Delay(delay);
		//Measure accurately the amount of time SDL_Delay() actually waits compared to what was expected
		//LOG("We waited for %I32u ms and got back in %f ms",delay,delayTimer.ReadMs()); // Uncomment this line to see the results
	}
	
	// Amount of ms took the last update (dt)
	dt = (float)frameTimer.ReadMs();

	// Amount of frames during the last second, from 1-60 and resets at 60.
	lastSecFrameCount++;

	if (lastSecFrameTimer.ReadMs() > 1000) 
	{
		lastSecFrameTimer.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
	}
}

bool Engine::PreUpdate()
{
	//Iterates the module list and calls PreUpdate on each module
	bool result = true;
	for (const auto& module : moduleList) {
		result = module.get()->PreUpdate();
		if (!result) {
			break;
		}
	}

	return result;
}

bool Engine::DoUpdate()
{
	//Iterates the module list and calls Update on each module
	bool result = true;
	for (const auto& module : moduleList)
	{
		result = module.get()->Update(dt);
		if (!result)
		{
			break;
		}
	}

	return result;
}

bool Engine::DoRender()
{
	bool result = true;
	for (const auto& module : moduleList)
	{
		result = module.get()->Render();
		if (!result)
		{
			break;
		}
	}

	return result;
}

bool Engine::PostUpdate()
{
	//Iterates the module list and calls PostUpdate on each module
	bool result = true;
	for (const auto& module : moduleList) {
		result = module.get()->PostUpdate();
		if (!result) {
			break;
		}
	}

	return result;
}

