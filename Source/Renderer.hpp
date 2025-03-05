#ifndef RENDERER
#define RENDERER

#include "Module.hpp"
#include "Vector2D.hpp"

class Renderable;
class Camera;

class Renderer : public Module
{
public:
	enum Layer
	{
		BACKGROUND = 0,
		WORLD = 1,
		ENTITY = 2,
		OVERENTITY = 3,
		DEBUG = 4,
		UI = 5,
		LAYER_TOTALCOUNT
	};


	// Constructor
	Renderer();

	// Destructor
	~Renderer();

	// Module Functions
	bool Awake() override;
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool CleanUp() override;

	// Viewports
	void SetViewPort(const SDL_Rect& rect);
	bool ResizeViewPort(int screenWidth, int screenHeight);
	void SetNewScreenWidthAndHeight(int screenWidth, int screenHeight);
	void UseLetterBoxOrPillarBox(SDL_Rect& newViewport, const float screenAspect);
	void UseLetterBox(SDL_Rect& newViewport);
	void UsePillarBox(SDL_Rect& newViewport);
	void ResetViewPort();

	void UpdateOffset();

	// Drawing
	bool QueueTexture(SDL_Texture* texture, SDL_Rect& sourceRect, SDL_Rect& destRect, bool forceDrawInsideCamera = false, int layer = Renderer::BACKGROUND, int basePoint = 0, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX);
	bool QueueDebugRectangle(const SDL_Rect& rect, SDL_Color color, bool filled, bool forceDrawInsideCamera = false, int layer = Renderer::DEBUG);
	bool QueueDebugLine(Vector2D start, Vector2D end, SDL_Color color, bool forceDrawInsideCamera = false, int layer = Renderer::DEBUG);
	bool QueueDebugCircle(Vector2D center, int radius, SDL_Color color, bool forceDrawInsideCamera = false, int layer = Renderer::DEBUG);

	void AddRenderableToAppropriateLayer(std::unique_ptr<Renderable> renderable);
	void SortEntityDrawOrder();
	void UpdateEntitiesBasePoint();

	void DrawTexture(SDL_Texture* texture, SDL_Rect& sourceRect, SDL_Rect& destRect, bool forceDrawInsideCamera = false, int layer = Renderer::BACKGROUND, double angle = 0.0, int pivotX = 0, int pivotY = 0);
	void DrawRectangle(SDL_Rect& rectangle, SDL_Color color, bool forceDrawInsideCamera = false, bool filled = true);
	void DrawLine(Vector2D originVector, Vector2D endVector, SDL_Color color, bool forceDrawInsideCamera = false);
	bool DrawCircle(Vector2D vector, int radius, SDL_Color rgb, bool forceDrawInsideCamera = false);
	void DrawCircleInternal(Vector2D vector, int radius, bool forceDrawInsideCamera = false);


	void SetBackgroundColor(SDL_Color color);

	// Getters
	SDL_Renderer* GetRenderer() const;
	std::shared_ptr<Camera> GetCamera();

	// FadeIn & FadeOut will come from another class

private:
	SDL_Renderer* renderer;
	std::vector<std::unique_ptr<Renderable>> backgroundLayer;
	std::vector<std::unique_ptr<Renderable>> worldLayer;
	std::vector<std::unique_ptr<Renderable>> entityLayer;
	std::vector<std::unique_ptr<Renderable>> overEntityLayer;
	std::vector<std::unique_ptr<Renderable>> debugLayer;
	std::vector<std::unique_ptr<Renderable>> uiLayer;
	std::shared_ptr<Camera> camera;

	SDL_Rect viewport;
	SDL_Color background;

	int newScreenWidth;
	int newScreenHeight;



	// Constants
private:
	// Base logical resolution
	Vector2D offset = Vector2D();
	const int baseWidth = 352;
	const int baseHeight = 224;
	const float baseAspectRatio = static_cast<float>(baseWidth) / baseHeight;
};

#endif