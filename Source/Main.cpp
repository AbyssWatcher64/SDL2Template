#define SDL_MAIN_HANDLED
#include "PreCompileHeaders.h"


int main(int argc, char* argv[]) 
{
    //HWND hWnd = GetConsoleWindow(); // ONLY USE THIS FOR RELEASES
    //ShowWindow(hWnd, SW_HIDE); // This hides the console window

    //LOG("=== Initializing Engine ===");

    //Engine::EngineState state = Engine::EngineState::CREATE;

    //// result's default is EXIT_FAILURE in case of sudden crash
    //int result = EXIT_FAILURE;

    //do
    //{
    //    switch (state)
    //    {
    //    default:
    //        LOG("Incorrect state. Defaulting to failure.");
    //        state = Engine::EngineState::FAIL;
    //        break;
    //    case Engine::EngineState::FAIL:
    //        LOG("-1: Critical failure. Quitting program.");
    //        state = Engine::EngineState::EXIT;
    //        break;
    //    case Engine::EngineState::CREATE:
    //        LOG("1: Creation phase.");
    //        state = Engine::EngineState::AWAKE;
    //        break;
    //    case Engine::EngineState::AWAKE:
    //        LOG("2: Awake phase.");
    //        if (Engine::Singleton().Awake()) // Awake phase finished successfully?
    //        {
    //            state = Engine::EngineState::START;
    //        }
    //        else
    //        {
    //            LOG("Awake failed.");
    //            state = Engine::EngineState::FAIL;
    //        }
    //        break;
    //    case Engine::EngineState::START:
    //        LOG("3: Start phase.");
    //        if (Engine::Singleton().Start()) // Start phase finished successfully?
    //        {
    //            state = Engine::EngineState::LOOP;
    //            LOG("4: Update phase.");
    //        }
    //        else
    //        {
    //            LOG("Start failed.");
    //            state = Engine::EngineState::FAIL;
    //        }
    //        break;
    //    case Engine::EngineState::LOOP:
    //        if (!Engine::Singleton().Loop()) // Loop phase returned false, therefore it doesn't have to loop anymore?
    //        {
    //            state = Engine::EngineState::CLEAN;
    //        }
    //        break;

    //    case Engine::EngineState::CLEAN:
    //        LOG("5: Cleanup phase.");
    //        if (Engine::Singleton().CleanUp()) // Cleanup has finished successfully?
    //        {
    //            result = EXIT_SUCCESS;
    //            state = Engine::EngineState::EXIT;
    //        }
    //        else
    //        {
    //            state = Engine::EngineState::FAIL;
    //        }
    //        break;
    //    }
    //} while (state != Engine::EngineState::EXIT);


    //LOG("=== Closing Engine ===");
    int result = Engine::Singleton().Run();

    return result;
}