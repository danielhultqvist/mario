#include "Camera.h"

Camera::Camera()
{
	m_offsetX = 0;
	m_offsetY = 0;
	m_windowSizeX = 1024;
	m_windowSizeY = 768;
}

void Camera::moveCamera(MovementVector vector, MapBounds bounds)
{
	//m_offsetX -= vector.dx;
	//m_offsetX = std::min(bounds.left, m_offsetX);
	if (bounds.left + m_windowSizeX / 2 > vector.x)
	{
		m_offsetX = 0;
	}
	else if (bounds.right - m_windowSizeX/2 < vector.x)
	{
		m_offsetX = -(bounds.right - m_windowSizeX);
	}
	else
	{
 		m_offsetX = -(vector.x - bounds.left - m_windowSizeX / 2);	
	}

	
}

int Camera::getOffsetX()
{
	return m_offsetX;
}

int Camera::getOffsetY()
{
	return m_offsetY;
}

int Camera::getWindowSizeX()
{
	return m_windowSizeX;
}

int Camera::getWindowSizeY()
{
	return m_windowSizeY;
}