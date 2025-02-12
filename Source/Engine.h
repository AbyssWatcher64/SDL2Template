#pragma once
#include "PreCompileHeaders.h"

class Module;

class Engine
{
public:
	// Singleton instance of the Engine
	static Engine& Singleton();

	void AddModule(std::shared_ptr<Module> module);

	enum EngineState
	{
		FAIL = -1,
		EXIT = 0,
		CREATE = 1,
		AWAKE,
		START,
		LOOP,
		CLEAN
	};

	int Run(); // Main loop

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

	// Function pointers for FSM
	using StateFunction = EngineState(Engine::*)();
	EngineState StateCreate();
	EngineState StateAwake();
	EngineState StateStart();
	EngineState StateLoop();
	EngineState StateClean();
	EngineState StateFail();

	// State execution
	EngineState ExecuteState(EngineState state);


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
private:
	
	std::list<std::shared_ptr<Module>> moduleList;

	bool isDebugModeActive = true;
};