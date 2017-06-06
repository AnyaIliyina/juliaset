#pragma once 
#include <QOpenGlWidget>
#include <QMatrix4x4>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include "camera2d.h"
#include <qfile.h>
class QOpenGLShaderProgram;
class QOpenGLTexture;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
public:

	GLWidget(QWidget *parent = 0);
	~GLWidget();
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	Camera2d cam;
	QPoint m_lastPos;
	double m_scaling;
	int m_side;
	QOpenGLShaderProgram* m_program;
	int m_mvpLoc, m_cLoc, m_iterCountLoc, m_paletteLoc, m_coordLoc;
	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	QOpenGLBuffer m_ibo;
	QOpenGLTexture* m_texture;
	void makeObject();
	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;
	QMatrix4x4 m_projection = QMatrix4x4();
};


