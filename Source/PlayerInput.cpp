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

bool PlayerInput::IsGameButtonPressedRepeat(GameButton button)
{
	//if (Engine::Singleton().input->GetKey(keyBindings.at(button)) == KEY_REPEAT) return true;
	if (Engine::Singleton().input->GetKey(keyBindings.at(button)) == KEY_REPEAT) return true;
	//if (Engine::Singleton().input->GetKey(keyBindings.at(button)) == KEY_REPEAT) // Need to program Keyboard support
		return false;
}

bool PlayerInput::IsGameButtonPressed(GameButton button)
{
	return Engine::Singleton().input->GetKey(keyBindings.at(button)) == KEY_DOWN;
}

bool PlayerInput::IsGameButtonReleased(GameButton button)
{
	return Engine::Singleton().input->GetKey(keyBindings.at(button)) == KEY_UP;
}

void PlayerInput::RemapKey(GameButton key, int newKey)
{
	keyBindings[key] = SDL_GetScancodeFromKey(newKey);
}

void PlayerInput::RemapGamepadButton(GameButton button, int newButton)
{
	
}

void PlayerInput::DefaultBindings()
{
	keyBindings[GameButton::DPAD_UP] = SDL_SCANCODE_W;
	keyBindings[GameButton::DPAD_DOWN] = SDLK_s;
	keyBindings[GameButton::DPAD_LEFT] = SDLK_a;
	keyBindings[GameButton::DPAD_RIGHT] = SDLK_d;
	keyBindings[GameButton::BUTTON_UP] = SDLK_LSHIFT;
	keyBindings[GameButton::BUTTON_DOWN] = SDLK_SPACE;
	keyBindings[GameButton::BUTTON_LEFT] = SDLK_q;
	keyBindings[GameButton::BUTTON_RIGHT] = SDLK_e;
	keyBindings[GameButton::BUTTON_START] = SDLK_ESCAPE;

	gamepadBindings[GameButton::DPAD_UP] = SDL_CONTROLLER_BUTTON_DPAD_UP;
	gamepadBindings[GameButton::DPAD_DOWN] = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
	gamepadBindings[GameButton::DPAD_LEFT] = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
	gamepadBindings[GameButton::DPAD_RIGHT] = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
	gamepadBindings[GameButton::BUTTON_UP] = SDL_CONTROLLER_BUTTON_Y;
	gamepadBindings[GameButton::BUTTON_DOWN] = SDL_CONTROLLER_BUTTON_A;
	gamepadBindings[GameButton::BUTTON_LEFT] = SDL_CONTROLLER_BUTTON_X;
	gamepadBindings[GameButton::BUTTON_RIGHT] = SDL_CONTROLLER_BUTTON_B;
	gamepadBindings[GameButton::BUTTON_START] = SDL_CONTROLLER_BUTTON_START;
}