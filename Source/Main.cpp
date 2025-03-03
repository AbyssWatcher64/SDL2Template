#define SDL_MAIN_HANDLED
#include "PreCompileHeaders.h"
#include "MemoryLeaksReporter.hpp"
//#include <Windows.h> // Use this for releases to hide the console windows

int main(int argc, char* argv[]) 
{
    //HWND hWnd = GetConsoleWindow(); // ONLY USE THIS FOR RELEASES
    //ShowWindow(hWnd, SW_HIDE); // This hides the console window
    //ShowWindow(hWnd, SW_SHOW); // This shows the console window

    ReportMemoryLeaks(); // This helps identifying memory leaks. They're in the ouput, once closing the game manually.
    int result = Engine::Singleton().Run();

    return result;
}