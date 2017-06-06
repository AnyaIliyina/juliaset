#include "glwidget.h"
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_1_1>
#include <QGLWidget>
#include <QIcon>
#include <QDir>
#include <QFileInfo>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>


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



void GLWidget::mousePressEvent(QMouseEvent * event)
{
	m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent * event)
{
	int dx = m_lastPos.x() - event->x();
	int dy = event->y() - m_lastPos.y();
	
	if (event->buttons() & Qt::LeftButton) {
		cam.moveCenter(m_scaling*dx, m_scaling*dy);
	}
	
	m_lastPos = event->pos();
	event->accept();
	update();
}

void GLWidget::wheelEvent(QWheelEvent * event)
{
	if (event->delta() > 0) 
	{
		cam.scale(2);
	}
	else {
		cam.scale(0.8);
	}
	m_scaling = cam.halfWidth() * 2 / m_side;
	event->accept();
	update();
}

void GLWidget::makeObject()
{
	static const float coords[3][2] = {
		{-0.5, 0},
		{0.5, 0.5},
		{0.5, 0}
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
	{
		for (int j = 0; j < 2; ++j)
		{
			vertData.append(coords[i][j]);
		}
		for (int j = 0; j < 2; ++j)
		{
			vertData.append(textCoords[i][j]);
		}
	}

	for (int i = 0; i < 3; ++i)
		indData.append(indeces[i]);

	m_vbo.create();
	m_vbo.bind();
	m_vbo.allocate(vertData.constData(), vertData.count()*sizeof(GLfloat));

	m_ibo.create();
	m_ibo.bind();
	m_ibo.allocate(indData.constData(), indData.count() * sizeof(GLint));

	//auto icon = QIcon(":/texture");
	auto image = QImage("../../../../packages/mypoolapp/myapp/images/texture.png");
	m_texture = new QOpenGLTexture(image);

}

void GLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	makeObject();

	QOpenGLShader* vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
	const char* vertSource =  "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
		"}\n";
	vshader->compileSourceCode(vertSource);

	QOpenGLShader* fragShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char* fragSource =  "uniform sampler2D texture;\n"
        "varying mediump vec4 texc;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = texture2D(texture, texc.st);\n"
		"}\n";
	fragShader->compileSourceCode(fragSource);

#define VERTEX_ATTR 0
#define TEXTURE_ATTR 1
	m_program = new QOpenGLShaderProgram;
	m_program->addShader(vshader);
	m_program->addShader(fragShader);
	m_program->bindAttributeLocation("vertex", VERTEX_ATTR);
	m_program->bindAttributeLocation("texCoord", TEXTURE_ATTR);
	m_program->link();
	m_program->bind();
	m_program->setUniformValue("texture", 0);

	
}

void GLWidget::resizeGL(int width, int height)
{
	
	m_side = qMin(width, height);
	m_projection.setToIdentity();
	m_projection.viewport((width - m_side) / 2, (height - m_side) / 2, m_side, m_side);
	m_scaling = cam.halfWidth()*2/ m_side;
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	QMatrix4x4 m;
	//m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
	//m.translate(0.0f, 0.0f, -10.0f);
	//m.rotate(xRot / 16.0f, 1.0f, 0.0f, 0.0f);
	//m.rotate(yRot / 16.0f, 0.0f, 1.0f, 0.0f);
	//m.rotate(zRot / 16.0f, 0.0f, 0.0f, 1.0f);
	auto matr = cam.viewMatrix();
	m_program->setUniformValue("matrix", cam.viewMatrix()* m_projection);
	m_program->enableAttributeArray(VERTEX_ATTR);
	m_program->enableAttributeArray(TEXTURE_ATTR);
	m_program->setAttributeBuffer(VERTEX_ATTR, GL_FLOAT, 0, 2, 4 * sizeof(GLfloat));
	m_program->setAttributeBuffer(TEXTURE_ATTR, GL_FLOAT, 2 * sizeof(GLfloat), 2, 4 * sizeof(GLfloat));

	m_texture->bind();
//	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, )
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	
}
