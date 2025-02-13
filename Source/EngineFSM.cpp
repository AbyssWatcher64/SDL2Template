#include "PreCompileHeaders.h"
#include "EngineFSM.hpp"

EngineFSM::EngineFSM() : currentState(CREATE)
{
    stateFunctions =
    {
        {CREATE, &EngineFSM::StateCreate},
        {AWAKE,  &EngineFSM::StateAwake},
        {START,  &EngineFSM::StateStart},
        {LOOP,   &EngineFSM::StateLoop},
        {CLEAN,  &EngineFSM::StateClean},
        {FAIL,   &EngineFSM::StateFail}
    };
}

int EngineFSM::Run()
{
    while (currentState != EXIT)
    {
        auto it = stateFunctions.find(currentState);

        if (it != stateFunctions.end())
        {
            currentState = (this->*it->second)();
        }
        else
        {
            LOG("Incorrect state. Defaulting to failure.");
            currentState = FAIL;
        }
    }

    return EXIT_SUCCESS;
}

EngineFSM::EngineState EngineFSM::StateCreate()
{
    LOG("1: Creation phase.");
    return AWAKE;
}

EngineFSM::EngineState EngineFSM::StateAwake()
{
    LOG("2: Awake phase.");

    if (Engine::Singleton().Awake())
    {
        return START;
    }
    else
    {
        LOG("Awake failed.");
        return FAIL;
    }
}

EngineFSM::EngineState EngineFSM::StateStart()
{
    LOG("3: Start phase.");

    if (Engine::Singleton().Start())
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

EngineFSM::EngineState EngineFSM::StateLoop()
{
    if (Engine::Singleton().Loop())
    {
        return LOOP;
    }
    else
    {
        return CLEAN;
    }
}

EngineFSM::EngineState EngineFSM::StateClean()
{
    LOG("5: Cleanup phase.");

    if (Engine::Singleton().CleanUp())
    {
        return EXIT;
    }
    else
    {
        return FAIL;
    }
}

EngineFSM::EngineState EngineFSM::StateFail()
{
    LOG("-1: Critical failure. Quitting program.");
    return EXIT;
}
