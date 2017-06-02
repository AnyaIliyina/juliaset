#include "glwidget.h"
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_1_1>
#include <QGLWidget>
#include <QIcon>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

static const char *vertexShaderSource =
//"uniform sampler1D palette; \n"
////"uniform vec2 c; \n "
////"uniform int iter; \n "
//"varying vec3 f_color; \n"
//
//"void main() { \n "
//
//"vec2 c = vec2(0.25, 0); \n"
//"int iter = 7; \n"
//
//"vec2 z; \n "
//"z.x = 3.0 * (gl_TexCoord[0].x - 0.5); \n "
//"z.y = 2.0 * (gl_TexCoord[0].y - 0.5); \n "
//
//"int i; \n "
//"for (i = 0; i<iter; i++) { \n "
//"	float x = (z.x * z.x - z.y * z.y) + c.x; \n "
//"	float y = (z.y * z.x + z.x * z.y) + c.y; \n "
//
//"	if ((x * x + y * y) > 4.0) break; \n "
//"	z.x = x; \n "
//"	z.y = y; \n "
//"}  \n "
//
////"f_color = texture1D(palette, (i == iter ? 0.0 : float(i)) / 100.0); \n "
//"f_color =  vec3(1.0,0.0,0.0); \n "
//"} \n ";
//"varying vec3 coord3d;\n "
"attribute vec3 coord3d; \n"
"attribute vec3 v_color; \n"
"uniform mat4 mvp; \n"
"varying vec3 f_color; \n"
"void main(void) { \n"
"gl_Position = mvp*vec4(coord3d, 0);\n"
//"gl_Position = mvp * vec4(coord3d, 1.0);\n"
"f_color = vec3(1.0, 1.0, 0.0); }";

static const char *fragmentShaderSourceCore =
"varying highp vec3 f_color;\n"
"void main(void) \n"
"{ gl_FragColor = vec4(f_color.x, f_color.y, f_color.z, 1.0); \n"
"}";

//http://doc.qt.io/qt-5/qtopengl-hellogl2-example.html
//http://nuclear.mutantstargoat.com/articles/sdr_fract/

GLWidget::GLWidget(QWidget* parent): QOpenGLWidget(parent),
	m_vbo(QOpenGLBuffer::Type::VertexBuffer), m_ibo(QOpenGLBuffer::Type::IndexBuffer)
{
	cam.setHalfWidth(2);
}


GLWidget::~GLWidget()
{
}

void GLWidget::loadPaletteTexture()
{
	/*auto *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_1_1>();
	
	f->glBindTexture(GL_TEXTURE_1D, 1);
	f->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	f->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	f->glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	QImage image;
	auto imagePath = "e:/openGL/juliaset/packages/mypoolapp/myapp/images/pal.ppm";
	if (!image.load(imagePath))
		qDebug() << "error loading image:\n" << imagePath;
	auto img = QGLWidget::convertToGLFormat(image);
	if (img.isNull()) return;

	f->glTexImage1D(GL_TEXTURE_1D, 0, 4, 256, 0, GL_BGRA, GL_UNSIGNED_BYTE, img.bits());
	
	f->glEnable(GL_TEXTURE_1D);*/
}

void GLWidget::mousePressEvent(QMouseEvent * event)
{
	m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent * event)
{
	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();
	auto br = m_scaling*dx;

	if (event->buttons() & Qt::LeftButton) {
		cam.moveCenter(m_scaling*dx, m_scaling*dy);
	}
	/*else if (event->buttons() & Qt::RightButton) {
		setXRotation(m_xRot + 8 * dy);
		setZRotation(m_zRot + 8 * dx);
	}*/
	m_lastPos = event->pos();
	update();
}

void GLWidget::wheelEvent(QWheelEvent * event)
{
	qDebug() << event->delta();
	if (event->delta() > 0) 
	{
		cam.scale(1.3);
	}
	else {
		cam.scale(0.8);
	}
	event->accept();
	update();
}

void GLWidget::makeObject()
{
	static const float coords[3][2] = {
		{-1, 0}, 
		{1, 1},
		{1, 0}
	};
	static const  float textCoords[3][2] = {
		{0, 0},
		{0.5, 1},
		{1, 1}
	};
	static const int indeces[3] = { 0,1,2 };

	QVector <GLfloat> vertData;
	QVector <GLint> indData;
	QVector <GLfloat> textData;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 2; ++j)
		{
			vertData.append(coords[i][j]);
			vertData.append(textCoords[i][j]);
		}

	for (int i = 0; i < 3; ++i)
		indData.append(indeces[i]);

	m_vbo.create();
	m_vbo.bind();
	m_vbo.allocate(vertData.constData(), vertData.count()*sizeof(GLfloat));

	m_ibo.create();
	m_ibo.bind();
	m_ibo.allocate(indData.constData(), indData.count() * sizeof(GLint));

	auto icon = QIcon(":/texture");
	auto fjfjf = QImage(":/texture");
	qDebug() << fjfjf.isNull();
	m_texture = new QOpenGLTexture(QImage(":/texture"));

}

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	makeObject();
}

void GLWidget::resizeGL(int w, int h)
{
	auto min = qMin(w, h);
	//m_projection.viewport(0, h - min, min, min, -1, 1);
//	m_projection.setToIdentity();
	//m_projection.viewport(-2, -2, 4, 4, -1.F, 1.F);
//	m_projection.perspective(45.0f, (GLfloat)w / h, -1.F, 1.F);
//	m_scaling = cam.halfWidth()*2/min;
}

void GLWidget::paintGL()
{
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glClear(GL_COLOR_BUFFER_BIT);
	QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
	m_program->enableAttributeArray(0);
	m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 2 * sizeof(GLfloat));
	auto matr =  cam.viewMatrix();
	matr.setToIdentity();
m_program->setUniformValue(m_mvpLoc, matr);
	f->glEnableVertexAttribArray(m_coordLoc);
	f->glBindBuffer(GL_ARRAY_BUFFER, m_vbo.bufferId());
	f->glVertexAttribPointer(m_coordLoc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	f->glDrawArrays(GL_TRIANGLES, 0, 3);


	m_program->release();
	
	
}
