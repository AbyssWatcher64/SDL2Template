#ifndef PLAYERINPUT
#define PLAYERINPUT

#include <unordered_map>

enum class GameButton
{
	DPAD_UP = 0,
	DPAD_DOWN,
	DPAD_LEFT,
	DPAD_RIGHT,

	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_START,
	BUTTON_SELECT,

	BUTTON_LSHOULDER,
	BUTTON_RSHOULDER,

	UNKNOWN
};

class PlayerInput
{
public:
	PlayerInput();
	~PlayerInput();

	void Update();

	bool IsGameButtonRepeatedlyPressed(GameButton button);
	bool IsGameButtonPressed(GameButton button);
	bool IsGameButtonReleased(GameButton button);

	void RemapKey(GameButton key, int newKey);
	void RemapGamepadButton(GameButton button, int newButton);


private:
	std::unordered_map<GameButton, int> keyBindings;
	std::unordered_map<GameButton, int> gamepadBindings;

	void DefaultBindings();
	GameButton GetKeyboardGameButtonFromString(const std::string& str);
};

#endif