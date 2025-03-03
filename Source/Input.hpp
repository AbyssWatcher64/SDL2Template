#ifndef INPUT
#define INPUT

#include "Module.hpp"

#define NUM_MOUSE_BUTTONS 5
#define MAX_KEYS 300

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

    bool GetWindowEvent(WindowEvent ev) const;

    void SetKeyboardKeyState(const Uint8* keys);
    void SetKeyboardKeyStateIfKeyPressed(int key);
    void SetKeyboardKeyStateIfNoKeyPressed(int key);
    void SetMouseKeyState();

    void ProcessSDLEvent(const SDL_Event& event);
    void HandleWindowEvent(Uint8 windowEvent);
    void UpdateMouseMotion(const SDL_MouseMotionEvent& motion);

    Vector2D GetMousePosition() const;
    Vector2D GetMouseMotion() const;

private:
    bool windowEvents[WE_TOTALCOUNT] = { false };
    std::vector<KeyState> keyboard;
    KeyState mouseButtons[NUM_MOUSE_BUTTONS] = { KEY_IDLE };

    int mouseMotionX = 0;
    int mouseMotionY = 0;
    int mouseX = 0;
    int mouseY = 0;
};

#endif