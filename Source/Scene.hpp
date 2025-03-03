#ifndef SCENE
#define SCENE

#include "Module.hpp"

class Camera;

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
private:
	std::shared_ptr<Camera> camera;
	SDL_Texture* TMPPlayerTexture;

	Vector2D TEMPPosition = Vector2D(352/2, 224/2);
};	

#endif