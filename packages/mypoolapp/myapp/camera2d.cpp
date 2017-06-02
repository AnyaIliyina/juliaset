#include "camera2d.h"

Camera2d::Camera2d(): m_centerX(0), m_centerY(0), m_w(1)
{
	updateMatrix();
}


Camera2d::~Camera2d()
{
}

void Camera2d::setCenter(double centerX, double centerY)
{
	m_centerX = centerX;
	m_centerY = centerY;
}

QPoint Camera2d::center() const
{
	return QPoint(m_centerX, m_centerY);
}

void Camera2d::setHalfWidth(double halfWidth)
{
	m_w = halfWidth;
}

double Camera2d::halfWidth() const
{
	return m_w;
}

void Camera2d::scale(double scaleFactor)
{
	m_w *= scaleFactor;
	updateMatrix();
}

void Camera2d::moveCenter(double xStep, double yStep)
{
	m_centerX += xStep;
	m_centerY += yStep;
	updateMatrix();
}

const QMatrix4x4 & Camera2d::viewMatrix() const
{
	return m_matrix;
}

void Camera2d::updateMatrix()
{
	m_matrix.ortho(m_centerX - m_w, m_centerX + m_w, 
					m_centerY - m_w, m_centerY + m_w, 
					-1.F, 1.F);

}
