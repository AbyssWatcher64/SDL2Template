#include "PreCompileHeaders.h"
#include "Input.hpp"
#include "Window.hpp"
#include <unordered_set>

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
    const Uint8* keyboardKeys = SDL_GetKeyboardState(nullptr);

    // Sets state of each keyboard key individually to what it should
    SetKeyboardKeyState(keyboardKeys);

    // Sets state of each mouse key individually to what it should
    SetMouseKeyState();

    // Sets state of window depending on Window events
    while (SDL_PollEvent(&event))
    {
        ProcessSDLEvent(event);
    }

    return true;
}

// Called before quitting
bool Input::CleanUp()
{
    LOG("== Quitting SDL event subsystem ==");
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
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

void Input::SetKeyboardKeyState(const Uint8* keys)
{
    for (int i = 0; i < MAX_KEYS; ++i)
    {
        if (keys[i])  // If key is currently pressed
        {
            SetKeyboardKeyStateIfKeyPressed(i);
        }
        else  // If key is NOT pressed
        {
            SetKeyboardKeyStateIfNoKeyPressed(i);
        }
    }
}

void Input::SetKeyboardKeyStateIfKeyPressed(int key)
{
    if (keyboard[key] == KEY_IDLE)
    {
        keyboard[key] = KEY_DOWN; // Key was idle before, now it's first pressed
    }
    else
    {
        keyboard[key] = KEY_REPEAT; // Key was already pressed, so it's repeating
    }
}

void Input::SetKeyboardKeyStateIfNoKeyPressed(int key)
{
    if (keyboard[key] == KEY_DOWN || keyboard[key] == KEY_REPEAT)
    {
        keyboard[key] = KEY_UP; // Key was pressed but is now released
    }
    else
    {
        keyboard[key] = KEY_IDLE; // Key remains idle
    }
}

void Input::SetMouseKeyState()
{
    for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
    {
        if (mouseButtons[i] == KEY_UP)          mouseButtons[i] = KEY_IDLE;
        else if (mouseButtons[i] == KEY_DOWN)   mouseButtons[i] = KEY_REPEAT;
    }
}

void Input::ProcessSDLEvent(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        windowEvents[WE_QUIT] = true;
        break;

    case SDL_WINDOWEVENT:
        HandleWindowEvent(event.window.event);
        break;

    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button >= 1 && event.button.button <= NUM_MOUSE_BUTTONS)
        {
            mouseButtons[event.button.button - 1] = KEY_DOWN; 
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button >= 1 && event.button.button <= NUM_MOUSE_BUTTONS)
        {
            mouseButtons[event.button.button - 1] = KEY_UP;
        }
        break;

    case SDL_MOUSEMOTION:
        UpdateMouseMotion(event.motion);
        break;
    }
}

void Input::HandleWindowEvent(Uint8 windowEvent)
{
    // Lookup table to make things cleaner instead big switch statement
    // This just sets WE_HIDE or WE_SHOW to true depending on the WindowEvent
    static const std::unordered_set<Uint8> hideEvents =
    {
        SDL_WINDOWEVENT_HIDDEN,
        SDL_WINDOWEVENT_MINIMIZED,
        SDL_WINDOWEVENT_FOCUS_LOST
    };

    static const std::unordered_set<Uint8> showEvents =
    {
        SDL_WINDOWEVENT_SHOWN,
        SDL_WINDOWEVENT_FOCUS_GAINED,
        SDL_WINDOWEVENT_MAXIMIZED,
        SDL_WINDOWEVENT_RESTORED
    };

    if (hideEvents.count(windowEvent))
    {
        windowEvents[WE_HIDE] = true;
    }
    else if (showEvents.count(windowEvent))
    {
        windowEvents[WE_SHOW] = true;
    }
}

void Input::UpdateMouseMotion(const SDL_MouseMotionEvent& motion)
{
    mouseMotionX = motion.xrel /* / scale */;
    mouseMotionY = motion.yrel /* / scale */;
    mouseX = motion.x /* / scale */;
    mouseY = motion.y /* / scale */;
}

Vector2D Input::GetMousePosition() const
{
    return Vector2D(mouseX, mouseY);
}

Vector2D Input::GetMouseMotion() const
{
    return Vector2D(mouseMotionX, mouseMotionY);
}
