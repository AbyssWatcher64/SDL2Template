#include "PreCompileHeaders.h" //Engine.h included in the PCH

Engine::Engine()
{


}

Engine& Engine::Singleton()
{
	static Engine singleton;
	return singleton;
}

int Engine::Run() 
{
    LOG("=== Initializing Engine ===");

    EngineState state = CREATE;
    int result = EXIT_FAILURE;

    while (state != EXIT) 
    {
        state = ExecuteState(state);
    }

    if (state == EXIT) 
    {
        result = EXIT_SUCCESS;
    }

    LOG("Engine exited with code: %d", result);

    LOG("=== Closing Engine ===");
    return result;
}

Engine::EngineState Engine::ExecuteState(EngineState state) 
{
    switch (state) 
    {
    case CREATE: return StateCreate();
    case AWAKE:  return StateAwake();
    case START:  return StateStart();
    case LOOP:   return StateLoop();
    case CLEAN:  return StateClean();
    case FAIL:   return StateFail();
    default:
        LOG("Incorrect state. Defaulting to failure.");
        return FAIL;
    }
}

Engine::EngineState Engine::StateCreate() 
{
    LOG("1: Creation phase.");
    return AWAKE;
}

Engine::EngineState Engine::StateAwake() 
{
    LOG("2: Awake phase.");

    if (Awake()) 
    {
        return START;
    }
    else 
    {
        LOG("Awake failed.");
        return FAIL;
    }
}

Engine::EngineState Engine::StateStart() 
{
    LOG("3: Start phase.");

    if (Start()) 
    {
        LOG("4: Update phase.");
        return LOOP;
    }
    else 
    {
        LOG("Start failed.");
        return FAIL;
    }
}

Engine::EngineState Engine::StateLoop() 
{
    if (Loop()) 
    {
        return LOOP; // Keep looping
    }
    else 
    {
        return CLEAN;
    }
}

Engine::EngineState Engine::StateClean() 
{
    LOG("5: Cleanup phase.");

    if (CleanUp()) 
    {
        return EXIT;
    }
    else 
    {
        return FAIL;
    }
}

Engine::EngineState Engine::StateFail() 
{
    LOG("-1: Critical failure. Quitting program.");
    return EXIT;
}

//TEMP
bool Engine::Awake()
{
	return true;
}

//TEMP
bool Engine::Start()
{
	return true;
}

// Called each loop iteration
bool Engine::Loop()
{
	return true;
}

//TEMP
bool Engine::CleanUp()
{
	return true;
}

bool Engine::GetIsDebugModeActive() const
{
	return isDebugModeActive;
}

void Engine::SetIsDebugModeActive(bool value)
{
	isDebugModeActive = value;
}