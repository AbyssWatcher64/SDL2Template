#ifndef TESTBED
#define TESTBED

#include "Module.hpp"

class Camera;
class PlayerInput;

class TestBed : public Module
{
public:
	// TestBed = Test Scene. Use it for all your testing.
	TestBed();
	~TestBed();

	bool Awake() override;
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool Render() override;
	bool PostUpdate() override;
	bool CleanUp() override;

	void KeyboardKeyRebind();
	void ControllerKeyRebind();

private:
	std::shared_ptr<Camera> camera;
	std::shared_ptr<PlayerInput> playerInput;
	SDL_Texture* TMPPlayerTexture;

	Vector2D TEMPPosition = Vector2D(352 / 2, 224 / 2);

	bool TEMPcheckingForKeyboardKeybinds = false;
	bool TEMPcheckingForControllerButtonbinds = false;
};

#endif