#pragma once
#include "PreCompileHeaders.h"
#include <unordered_map>

class EngineFSM
{
public:
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

    using StateFunction = EngineState(EngineFSM::*)();

    EngineFSM();
    int Run();

private:
    EngineState currentState;

    EngineState StateCreate();
    EngineState StateAwake();
    EngineState StateStart();
    EngineState StateLoop();
    EngineState StateClean();
    EngineState StateFail();

    std::unordered_map<EngineState, StateFunction> stateFunctions;
};
