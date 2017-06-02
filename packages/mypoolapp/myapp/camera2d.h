#pragma once 
#include <QPoint>
#include <QMatrix4x4>

/*!
\brief	Создает квадратный порт просмотра
*/

class  Camera2d
{

public:

	Camera2d();
	~Camera2d();
	void setCenter(double centerX, double centerY);
	QPoint center() const;
	void setHalfWidth(double halfWidth);
	double halfWidth() const;

	void scale(double scaleFactor);
	void moveCenter(double xStep, double yStep);

	const QMatrix4x4 & viewMatrix() const;

protected:
	void updateMatrix();
	QMatrix4x4 m_matrix = QMatrix4x4();
	double m_w;
	double m_centerX, m_centerY;

};


