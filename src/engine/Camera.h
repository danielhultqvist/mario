#ifndef CAMERA_H
#define CAMERA_H
#include "../models/MovementVector.h"
#include "../models/Map.h"

class Camera
{
public:
	Camera();
	void moveCamera(MovementVector vector, MapBounds bounds);
	int getOffsetX();
	int getOffsetY();
	int getWindowSizeX();
	int getWindowSizeY();

private:
	int m_offsetX, m_offsetY;
	int m_windowSizeX, m_windowSizeY;
};

#endif