#pragma once
#include "PreCompileHeaders.h"
#include "EngineFSM.hpp"
#include "PrecisionTimer.hpp"

class Module;

class Window;

class Engine
{
public:
	// Singleton instance of the Engine
	static Engine& Singleton();

	void AddModule(std::shared_ptr<Module> module);

	int Run(); // Main loop for the FSM

	// Called before renderer is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Loop();

	// Called before quitting
	bool CleanUp();

	bool GetIsDebugModeActive() const;
	void SetIsDebugModeActive(bool value);

private:

	// Making the constructor private to prevent instantiation
	Engine();

	// Delete copy constructor and assignment operator to prevent copying
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	EngineFSM fsm;

	// Each frame consists of the following steps, which go in order:
	// 1. Call modules before each loop iteration
	void PrepareUpdate();

	// 2. Call update before each update loop iteration
	bool PreUpdate();

	// 3. Call update loop iteration
	bool DoUpdate();

	// 4. Call Render loop iteration
	bool DoRender();

	// 5. Call update after each update loop iteration
	bool PostUpdate();

	// 6. Call modules after each loop iteration
	void FinishUpdate();


public:
	// Modules
	std::shared_ptr<Window> window;

private:
	
	std::list<std::shared_ptr<Module>> moduleList;
	float dt;
	PrecisionTimer frameTimer;
	PrecisionTimer lastSecFrameTimer;

	//Maximum frame duration in miliseconds.
	int maxFrameDuration = 16;

	int framesPerSecond = 0;
	int lastSecFrameCount = 0;

	bool isDebugModeActive = true;
};