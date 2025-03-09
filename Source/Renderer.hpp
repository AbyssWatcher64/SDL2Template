#ifndef RENDERER
#define RENDERER

#include "Module.hpp"
#include "Vector2D.hpp"
#include "Fonts.hpp"

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
		OVER_ENTITY = 3,
		DEBUG = 4,
		UI = 5,
		TEXT_UI = 6,
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
	bool QueueTexture(SDL_Texture* texture, SDL_Rect& sourceRect, SDL_Rect& destRect, bool forceDrawInsideCamera = false, int layer = Renderer::BACKGROUND, int renderBasePoint = 0, float angle = 0, SDL_Point pivot = { INT_MAX,INT_MAX });
	bool QueueDebugRectangle(const SDL_Rect& rect, SDL_Color color, bool filled = true, bool forceDrawInsideCamera = false, int layer = Renderer::DEBUG);
	bool QueueDebugLine(Vector2D start, Vector2D end, SDL_Color color, bool forceDrawInsideCamera = false, int layer = Renderer::DEBUG);
	bool QueueDebugCircle(Vector2D center, int radius, SDL_Color color, bool forceDrawInsideCamera = false, int layer = Renderer::DEBUG);
	bool QueueText(const std::string& text, Vector2D position, FontName font = DEFAULT_FONT, SDL_Color color = { 255, 255, 255, 255 }, bool forceDrawInsideCamera = true, int layer = Renderer::TEXT_UI);

	// Getters
	SDL_Renderer* GetRenderer() const;
	std::shared_ptr<Camera> GetCamera();

	void DrawTexture(SDL_Texture* texture, const SDL_Rect& sourceRect, const SDL_Rect& destRect, float angle, SDL_Point pivot, bool forceDrawInsideCamera);
	void DrawRectangle(const SDL_Rect& rectangle, SDL_Color color, bool filled, bool forceDrawInsideCamera);
	void DrawLine(Vector2D originVector, Vector2D endVector, SDL_Color color, bool forceDrawInsideCamera);
	bool DrawCircle(Vector2D vector, int radius, SDL_Color rgb, bool forceDrawInsideCamera);
	void DrawCircleInternal(Vector2D vector, int radius, bool forceDrawInsideCamera);
	void DrawText(const std::string& text, Vector2D position, TTF_Font* font, SDL_Color color, bool forceDrawInsideCamera);

private:
	void AddRenderableToAppropriateLayer(std::unique_ptr<Renderable> renderable);
	void SortEntityDrawOrder();
	void UpdateEntitiesBasePoint();

	SDL_Texture* CreateTextTexture(const std::string& text, TTF_Font* font, SDL_Color color);

private:
	SDL_Renderer* renderer;
	std::vector<std::unique_ptr<Renderable>> backgroundLayer;
	std::vector<std::unique_ptr<Renderable>> worldLayer;
	std::vector<std::unique_ptr<Renderable>> entityLayer;
	std::vector<std::unique_ptr<Renderable>> overEntityLayer;
	std::vector<std::unique_ptr<Renderable>> debugLayer;
	std::vector<std::unique_ptr<Renderable>> uiLayer;
	std::vector<std::unique_ptr<Renderable>> textuiLayer;
	std::shared_ptr<Camera> camera;

	SDL_Rect viewport;
	SDL_Color background;

	int newScreenWidth;
	int newScreenHeight;



	// Constants
private:
	// Base logical resolution
	Vector2D offset = Vector2D();
	const float baseAspectRatio = static_cast<float>(baseWidth) / baseHeight;
};

#endif