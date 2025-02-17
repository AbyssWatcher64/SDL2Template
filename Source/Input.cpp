#include "PreCompileHeaders.h"
#include "Input.hpp"
#include "Window.hpp"

#define MAX_KEYS 300

Input::Input() : Module(), keyboard(MAX_KEYS, KEY_IDLE)
{
    name = "input";
}

// Destructor
Input::~Input() {}

// Called before SDL video is available
bool Input::Awake()
{
    LOG("== Initializing SDL input event system ==");
    bool ret = true;

    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
    {
        LOG("SDL_EVENTS could not initialize! SDL_Error: %s", SDL_GetError());
        ret = false;
    }

    return ret;
}

// Called before the first frame
bool Input::Start()
{
    SDL_StopTextInput();
    return true;
}

// Called each loop iteration
bool Input::PreUpdate()
{
    memset(windowEvents, false, sizeof(windowEvents)); // Reset window events

    static SDL_Event event;
    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    // Sets state of each keyboard key individually to what it should
    for (int i = 0; i < MAX_KEYS; ++i)
    {
        if (keys[i])  // If key is currently pressed
        {
            if (keyboard[i] == KEY_IDLE)
            {
                keyboard[i] = KEY_DOWN; // Key was idle before, now it's first pressed
            }
            else
            {
                keyboard[i] = KEY_REPEAT; // Key was already pressed, so it's repeating
            }
        }
        else  // If key is NOT pressed
        {
            if (keyboard[i] == KEY_DOWN || keyboard[i] == KEY_REPEAT)
            {
                keyboard[i] = KEY_UP; // Key was pressed but is now released
            }
            else
            {
                keyboard[i] = KEY_IDLE; // Key remains idle
            }
        }
    }


    // Sets state of each mouse key individually to what it should
    for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
    {
        if (mouseButtons[i] == KEY_UP)          mouseButtons[i] = KEY_IDLE;
        else if (mouseButtons[i] == KEY_DOWN)   mouseButtons[i] = KEY_REPEAT;
    }

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            windowEvents[WE_QUIT] = true;
            break;

        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_HIDDEN:
            case SDL_WINDOWEVENT_MINIMIZED:
            case SDL_WINDOWEVENT_FOCUS_LOST:
                windowEvents[WE_HIDE] = true;
                break;

            case SDL_WINDOWEVENT_SHOWN:
            case SDL_WINDOWEVENT_FOCUS_GAINED:
            case SDL_WINDOWEVENT_MAXIMIZED:
            case SDL_WINDOWEVENT_RESTORED:
                windowEvents[WE_SHOW] = true;
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseButtons[event.button.button - 1] = KEY_DOWN;
            break;

        case SDL_MOUSEBUTTONUP:
            mouseButtons[event.button.button - 1] = KEY_UP;
            break;

        case SDL_MOUSEMOTION:
            int scale = Engine::Singleton().window->GetScale();
            mouseMotionX = event.motion.xrel /* / scale */;
            mouseMotionY = event.motion.yrel /* / scale */;
            mouseX = event.motion.x /* / scale */;
            mouseY = event.motion.y /* / scale */;
            break;
        }
    }

    return true;
}

KeyState Input::GetKey(int id) const 
{
    return keyboard[id];
}

KeyState Input::GetMouseButtonDown(int id) const 
{ 
    return mouseButtons[id - 1]; 
}

bool Input::GetWindowEvent(WindowEvent ev) const
{
    return windowEvents[ev];
}

// Called before quitting
bool Input::CleanUp()
{
    LOG("== Quitting SDL event subsystem ==");
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    return true;
}

Vector2D Input::GetMousePosition() const
{
    return Vector2D(mouseX, mouseY);
}

Vector2D Input::GetMouseMotion() const
{
    return Vector2D(mouseMotionX, mouseMotionY);
}
