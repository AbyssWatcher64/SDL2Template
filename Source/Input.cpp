#include "PreCompileHeaders.h"
#include "Input.hpp"
#include "Window.hpp"
#include "PlayerInput.hpp"
#include <unordered_set>

Input::Input() : Module(), keyboard(MAX_KEYS, KEY_IDLE)
{
    name = "input";
    playerInput = std::make_shared<PlayerInput>();
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

    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
    {
        LOG("SDL_GAMECONTROLLER could not initialize! SDL_Error: %s", SDL_GetError());
        ret = false;
    }
    else
    {
        OpenControllers();
    }

    return ret;
}

bool Input::Start()
{
    SDL_StopTextInput();
    return true;
}

bool Input::PreUpdate()
{
    memset(windowEvents, false, sizeof(windowEvents));  // Reset window events
    static SDL_Event event;

    const Uint8* keyboardKeys = SDL_GetKeyboardState(nullptr);
    SetKeyboardKeyState(keyboardKeys);
    SetMouseKeyState();

    while (SDL_PollEvent(&event))
    {
        ProcessSDLEvent(event);
    }

    UpdateControllerStates();
    playerInput->Update();
    return true;
}


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

int Input::GetNextKeyboardKeyPressed()
{
    SDL_Event event;

    // Keep checking for an event until a key is pressed
    while (true) 
    {
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_KEYDOWN) 
            {
                return event.key.keysym.sym;  // Return the key code
            }
        }
    }
}

int Input::GetNextControllerButtonPressed()
{
    SDL_Event event;

    // Keep checking for an event until a controller button is pressed
    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_CONTROLLERBUTTONDOWN)
            {
                return event.cbutton.button;  // Return the button ID
            }
        }
    }
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

//KeyState Input::GetControllerButton(int controllerId, ControllerButton button) const
//{
//    //return controllerButtons[controllerId][button];
//    return controllerButtons[button];
//}
//
//float Input::GetControllerAxis(int controllerId, ControllerAxis axis) const
//{
//    //return controllerAxis[controllerId][axis] / 32767.0f; // Normalize (-1.0 to 1.0)
//    return controllerAxis[axis] / 32767.0f; // Normalize (-1.0 to 1.0)
//}
//
//bool Input::IsControllerConnected(int controllerId) const
//{
//    //return controllers[controllerId] != nullptr;
//    return controller != nullptr;
//}

KeyState Input::GetControllerButton(ControllerButton button) const
{
    return controllerButtons[button];
}

float Input::GetControllerAxis(ControllerAxis axis) const
{
    return controllerAxis[axis] / 32767.0f; // Normalize (-1.0 to 1.0)
}

bool Input::IsControllerConnected() const
{
    return controller != nullptr;
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

    case SDL_CONTROLLERBUTTONDOWN:
    case SDL_CONTROLLERBUTTONUP:
    case SDL_CONTROLLERAXISMOTION:
        HandleControllerEvents(event);
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

std::shared_ptr<PlayerInput> Input::GetPlayerInput() const
{
    return playerInput;
}

void Input::HandleControllerEvents(const SDL_Event& event)
{
    //int controllerId = event.cdevice.which; // Get which controller triggered the event

    //if (controllerId < 0 || controllerId >= MAX_CONTROLLERS || !controllers[controllerId])
    //    return; // Ignore invalid controllers

    //switch (event.type)
    //{
    //case SDL_CONTROLLERBUTTONDOWN:
    //    controllerButtons[controllerId][event.cbutton.button] = KEY_DOWN;
    //    break;

    //case SDL_CONTROLLERBUTTONUP:
    //    controllerButtons[controllerId][event.cbutton.button] = KEY_UP;
    //    break;

    //case SDL_CONTROLLERAXISMOTION:
    //    controllerAxis[controllerId][event.caxis.axis] = event.caxis.value;
    //    break;
    //}

    int controllerId = event.cdevice.which; // Get which controller triggered the event

    if (controllerId < 0 || controllerId >= 2 || !controller)
        return; // Ignore invalid controllers

    switch (event.type)
    {
    case SDL_CONTROLLERBUTTONDOWN:
        controllerButtons[event.cbutton.button] = KEY_DOWN;
        break;

    case SDL_CONTROLLERBUTTONUP:
        controllerButtons[event.cbutton.button] = KEY_UP;
        break;

    case SDL_CONTROLLERAXISMOTION:
        controllerAxis[event.caxis.axis] = event.caxis.value;
        break;
    }
}


void Input::UpdateControllerStates()
{
    /*for (int i = 0; i < MAX_CONTROLLERS; ++i)
    {
        if (!controllers[i]) continue;

        for (int button = 0; button < SDL_CONTROLLER_BUTTON_MAX; ++button)
        {
            if (SDL_GameControllerGetButton(controllers[i], static_cast<SDL_GameControllerButton>(button)))
            {
                if (controllerButtons[i][button] == KEY_IDLE)
                    controllerButtons[i][button] = KEY_DOWN;
                else
                    controllerButtons[i][button] = KEY_REPEAT;
            }
            else
            {
                if (controllerButtons[i][button] == KEY_DOWN || controllerButtons[i][button] == KEY_REPEAT)
                    controllerButtons[i][button] = KEY_UP;
                else
                    controllerButtons[i][button] = KEY_IDLE;
            }
        }
    }*/
    if (!controller) return;

    for (int button = 0; button < SDL_CONTROLLER_BUTTON_MAX; ++button)
    {
        if (SDL_GameControllerGetButton(controller, static_cast<SDL_GameControllerButton>(button)))
        {
            if (controllerButtons[button] == KEY_IDLE)
                controllerButtons[button] = KEY_DOWN;
            else
                controllerButtons[button] = KEY_REPEAT;
        }
        else
        {
            if (controllerButtons[button] == KEY_DOWN || controllerButtons[button] == KEY_REPEAT)
                controllerButtons[button] = KEY_UP;
            else
                controllerButtons[button] = KEY_IDLE;
        }
    }

}


void Input::OpenControllers()
{
   /* for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            controllers[i] = SDL_GameControllerOpen(i);
            if (controllers[i])
            {
                LOG("Opened Controller %d: %s", i, SDL_GameControllerName(controllers[i]));
            }
        }
    }*/
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            controller = SDL_GameControllerOpen(i);
            if (controller)
            {
                LOG("Opened Controller: %s", SDL_GameControllerName(controller));
            }
        }
    }
}