#include "PreCompileHeaders.h"
#include "PlayerInput.hpp"
#include "Input.hpp"

PlayerInput::PlayerInput()
{
	DefaultBindings();
}

PlayerInput::~PlayerInput() {}

void PlayerInput::Update()
{
	
}

bool PlayerInput::IsGameButtonRepeatedlyPressed(GameButton button)
{
	if (Engine::Singleton().input->GetKey(keyBindings.at(button)) == KEY_REPEAT) return true;
	if (Engine::Singleton().input->GetControllerButton(static_cast<ControllerButton>(gamepadBindings.at(button))) == KEY_REPEAT) return true;
	
	return false;
}

bool PlayerInput::IsGameButtonPressed(GameButton button)
{
	if (Engine::Singleton().input->GetKey(keyBindings.at(button)) == KEY_DOWN) return true;
	if (Engine::Singleton().input->GetControllerButton(static_cast<ControllerButton>(gamepadBindings.at(button))) == KEY_DOWN) return true;
	
	return false;
}

bool PlayerInput::IsGameButtonReleased(GameButton button)
{
	if (Engine::Singleton().input->GetKey(keyBindings.at(button)) == KEY_UP) return true;
	if (Engine::Singleton().input->GetControllerButton(static_cast<ControllerButton>(gamepadBindings.at(button))) == KEY_UP) return true;
	
	return false;
}

void PlayerInput::RemapKey(GameButton key, int newKey)
{
	keyBindings[key] = SDL_GetScancodeFromKey(newKey);
}

void PlayerInput::RemapGamepadButton(GameButton button, int newButton)
{
	gamepadBindings[button] = static_cast<ControllerButton>(newButton);
}

void PlayerInput::DefaultBindings()
{
	keyBindings[GameButton::DPAD_UP] = SDL_SCANCODE_W;
	keyBindings[GameButton::DPAD_DOWN] = SDL_SCANCODE_S;
	keyBindings[GameButton::DPAD_LEFT] = SDL_SCANCODE_A;
	keyBindings[GameButton::DPAD_RIGHT] = SDL_SCANCODE_D;
	keyBindings[GameButton::BUTTON_UP] = SDL_SCANCODE_LSHIFT;
	keyBindings[GameButton::BUTTON_DOWN] = SDL_SCANCODE_SPACE;
	keyBindings[GameButton::BUTTON_LEFT] = SDL_SCANCODE_Q;
	keyBindings[GameButton::BUTTON_RIGHT] = SDL_SCANCODE_E;
	keyBindings[GameButton::BUTTON_START] = SDL_SCANCODE_ESCAPE;
	keyBindings[GameButton::BUTTON_SELECT] = SDL_SCANCODE_RETURN;
	keyBindings[GameButton::BUTTON_LSHOULDER] = SDL_SCANCODE_TAB;
	keyBindings[GameButton::BUTTON_RSHOULDER] = SDL_SCANCODE_R;

	gamepadBindings[GameButton::DPAD_UP] = SDL_CONTROLLER_BUTTON_DPAD_UP;
	gamepadBindings[GameButton::DPAD_DOWN] = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
	gamepadBindings[GameButton::DPAD_LEFT] = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
	gamepadBindings[GameButton::DPAD_RIGHT] = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
	gamepadBindings[GameButton::BUTTON_UP] = SDL_CONTROLLER_BUTTON_X;
	gamepadBindings[GameButton::BUTTON_DOWN] = SDL_CONTROLLER_BUTTON_B;
	gamepadBindings[GameButton::BUTTON_LEFT] = SDL_CONTROLLER_BUTTON_Y;
	gamepadBindings[GameButton::BUTTON_RIGHT] = SDL_CONTROLLER_BUTTON_A;
	gamepadBindings[GameButton::BUTTON_START] = SDL_CONTROLLER_BUTTON_START;
	gamepadBindings[GameButton::BUTTON_SELECT] = SDL_CONTROLLER_BUTTON_BACK;
	gamepadBindings[GameButton::BUTTON_LSHOULDER] = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
	gamepadBindings[GameButton::BUTTON_RSHOULDER] = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
}