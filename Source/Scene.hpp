#ifndef SCENE
#define SCENE

#include "Module.hpp"

class Camera;
class PlayerInput;

class Scene : public Module
{
public:
	Scene();

	~Scene();
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

	Vector2D TEMPPosition = Vector2D(352/2, 224/2);

	bool TEMPcheckingForKeyboardKeybinds = false;
	bool TEMPcheckingForControllerButtonbinds = false;
};	

#endif