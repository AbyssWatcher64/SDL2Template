#include "Camera.hpp"

Camera::Camera()
{
	cameraView.x = 0;
	cameraView.y = 0;
	cameraView.w = 352;
	cameraView.h = 224;
	cameraViewCenter.SetX((cameraView.x + cameraView.w) / 2);
	cameraViewCenter.SetY((cameraView.y + cameraView.h) / 2);
}

Camera::Camera(SDL_Rect cameraView)
{
	this->cameraView.x = cameraView.x;
	this->cameraView.y = cameraView.y;
	this->cameraView.w = cameraView.w;
	this->cameraView.h = cameraView.h;
	this->cameraViewCenter.SetX((cameraView.x + cameraView.w) / 2);
	this->cameraViewCenter.SetY((cameraView.y + cameraView.h) / 2);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	if (lerping)
	{
		if (cameraViewCenter.GetX() < desiredXCenteredPosition)
		{
			cameraView.x++;
			cameraViewCenter.SetX(cameraViewCenter.GetX() + 1);
		}
		else if (cameraViewCenter.GetX() > desiredXCenteredPosition)
		{
			cameraView.x--;
			cameraViewCenter.SetX(cameraViewCenter.GetX() - 1);
		}
		if (cameraViewCenter.GetY() < desiredYCenteredPosition)
		{
			cameraView.y++;
			cameraViewCenter.SetY(cameraViewCenter.GetY() + 1);
		}
		else if (cameraViewCenter.GetY() > desiredYCenteredPosition)
		{
			cameraView.y--;
			cameraViewCenter.SetY(cameraViewCenter.GetY() - 1);
		}
		if (cameraViewCenter.GetX() == desiredXCenteredPosition &&
			cameraViewCenter.GetY() == desiredYCenteredPosition)
		{
			lerping = false;
		}
	}

	//cameraViewCenter.SetX((cameraView.x + cameraView.w) / 2);
	//cameraViewCenter.SetY((cameraView.y + cameraView.h) / 2);
}

SDL_Rect Camera::GetCameraView() const
{
	return cameraView;
}

int Camera::GetCameraXPosition() const
{
	return cameraView.x;
}

int Camera::GetCameraXCenteredPosition() const
{
	return ( cameraView.x + cameraView.w ) / 2;
}

int Camera::GetCameraYPosition() const
{
	return cameraView.y;
}

int Camera::GetCameraYCenteredPosition() const
{
	return (cameraView.y + cameraView.h) / 2;
}


void Camera::SetCenterCameraView(Vector2D vector)
{
	cameraView.x = vector.GetX() - cameraView.w/2;
	cameraView.y = vector.GetY() - cameraView.h/2;
	cameraViewCenter.SetX(vector.GetX());
	cameraViewCenter.SetY(vector.GetY());
}

void Camera::SetCenterCameraViewWithLerp(Vector2D vector)
{
	lerping = true;
	desiredXCenteredPosition = vector.GetX();
	desiredYCenteredPosition = vector.GetY();
}