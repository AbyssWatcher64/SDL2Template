#ifndef INPUT
#define INPUT

#include "Module.hpp"

#define NUM_MOUSE_BUTTONS 5
#define MAX_KEYS 300
#define MAX_CONTROLLERS 4  // Allow up to 4 controllers

class PlayerInput;

enum WindowEvent
{
    // WE = WindowEvent
    WE_QUIT = 0,
    WE_HIDE = 1,
    WE_SHOW = 2,
    WE_TOTALCOUNT
};

enum KeyState
{
    KEY_IDLE = 0,
    KEY_DOWN,
    KEY_REPEAT,
    KEY_UP
};

enum ControllerButton
{
    CONTROLLER_A = SDL_CONTROLLER_BUTTON_A,
    CONTROLLER_B = SDL_CONTROLLER_BUTTON_B,
    CONTROLLER_X = SDL_CONTROLLER_BUTTON_X,
    CONTROLLER_Y = SDL_CONTROLLER_BUTTON_Y,
    CONTROLLER_START = SDL_CONTROLLER_BUTTON_START,
    CONTROLLER_BACK = SDL_CONTROLLER_BUTTON_BACK,
    CONTROLLER_LB = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
    CONTROLLER_RB = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
};

enum ControllerAxis
{
    AXIS_LEFT_X = SDL_CONTROLLER_AXIS_LEFTX,
    AXIS_LEFT_Y = SDL_CONTROLLER_AXIS_LEFTY,
    AXIS_RIGHT_X = SDL_CONTROLLER_AXIS_RIGHTX,
    AXIS_RIGHT_Y = SDL_CONTROLLER_AXIS_RIGHTY
};

class Input : public Module
{
public:
    Input();
    virtual ~Input();

    bool Awake() override;
    bool Start() override;
    bool PreUpdate() override;
    bool CleanUp() override;

    KeyState GetKey(int id) const;
    KeyState GetMouseButtonDown(int id) const;
    int GetNextKeyboardKeyPressed();
    int GetNextControllerButtonPressed();
    bool GetWindowEvent(WindowEvent ev) const;

    void SetKeyboardKeyState(const Uint8* keys);
    void SetKeyboardKeyStateIfKeyPressed(int key);
    void SetKeyboardKeyStateIfNoKeyPressed(int key);
    void SetMouseKeyState();

    KeyState GetControllerButton(ControllerButton button) const;
    float GetControllerAxis(ControllerAxis axis) const;
    bool IsControllerConnected() const;

    void ProcessSDLEvent(const SDL_Event& event);
    void HandleWindowEvent(Uint8 windowEvent);
    void UpdateMouseMotion(const SDL_MouseMotionEvent& motion);

    Vector2D GetMousePosition() const;
    Vector2D GetMouseMotion() const;
    std::shared_ptr<PlayerInput> GetPlayerInput() const;
private:
    void HandleControllerEvents(const SDL_Event& event);
    void UpdateControllerStates();
    void OpenControllers();

private:
    // Mouse and Keyboard
    bool windowEvents[WE_TOTALCOUNT] = { false };
    std::vector<KeyState> keyboard;
    KeyState mouseButtons[NUM_MOUSE_BUTTONS] = { KEY_IDLE };

    // Controller
    SDL_GameController* controller = nullptr;
    KeyState controllerButtons[SDL_CONTROLLER_BUTTON_MAX] = { {KEY_IDLE} };
    int controllerAxis[SDL_CONTROLLER_AXIS_MAX] = { {0} };

    int mouseMotionX = 0;
    int mouseMotionY = 0;
    int mouseX = 0;
    int mouseY = 0;

    std::shared_ptr<PlayerInput> playerInput;
};

#endif