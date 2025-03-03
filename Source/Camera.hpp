#ifndef CAMERA
#define CAMERA

#include "SDL2/SDL_image.h"
#include "Vector2D.hpp"

class Camera
{
public:
	Camera();
	Camera(SDL_Rect cameraView);
	~Camera();

	void Update();

	SDL_Rect GetCameraView() const;
	int GetCameraXPosition() const;
	int GetCameraXCenteredPosition() const;
	int GetCameraYPosition() const;
	int GetCameraYCenteredPosition() const;

	void SetCenterCameraView(Vector2D vector);
	void SetCenterCameraViewWithLerp(Vector2D vector);

private:
	SDL_Rect cameraView;
	Vector2D cameraViewCenter;
	int desiredXCenteredPosition;
	int desiredYCenteredPosition;
	bool lerping = false;
};

#endif