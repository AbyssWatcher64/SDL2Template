#include "PreCompileHeaders.h"
#include "PlayerInput.hpp"
#include "Input.hpp"
#include "IniParser.hpp"

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

// TODO MUCH LATER ON: Make remapping keys work properly (low priority)
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
	std::unordered_map<std::string, std::string> configFile = LoadConfig("keybinds.ini");
	for (auto& it : configFile)
	{
		SDL_Scancode scancode = SDL_GetScancodeFromName(it.second.c_str());

		if (scancode != SDL_SCANCODE_UNKNOWN)
		{
			keyBindings[GetKeyboardGameButtonFromString(it.first)] = scancode;
		}
		else
		{
			std::cerr << "Warning: Invalid key in config for " << it.first << " -> " << it.second << std::endl;
		}
	}

	// TODO MUCH LATER ON: Fix gamepad bindings to function with the config file, and make them remappable. (low priority)
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

GameButton PlayerInput::GetKeyboardGameButtonFromString(const std::string& str)
{
	static const std::unordered_map<std::string, GameButton> gameButtonMap =
	{
		{"DPAD_UP", GameButton::DPAD_UP},
		{"DPAD_DOWN", GameButton::DPAD_DOWN},
		{"DPAD_LEFT", GameButton::DPAD_LEFT},
		{"DPAD_RIGHT", GameButton::DPAD_RIGHT},
		{"BUTTON_UP", GameButton::BUTTON_UP},
		{"BUTTON_DOWN", GameButton::BUTTON_DOWN},
		{"BUTTON_LEFT", GameButton::BUTTON_LEFT},
		{"BUTTON_RIGHT", GameButton::BUTTON_RIGHT},
		{"BUTTON_START", GameButton::BUTTON_START},
		{"BUTTON_SELECT", GameButton::BUTTON_SELECT},
		{"BUTTON_LSHOULDER", GameButton::BUTTON_LSHOULDER},
		{"BUTTON_RSHOULDER", GameButton::BUTTON_RSHOULDER}


	};
	auto it = gameButtonMap.find(str);
	return (it != gameButtonMap.end()) ? it->second : GameButton::UNKNOWN;
}