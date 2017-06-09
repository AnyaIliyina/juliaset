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
	
}


GLWidget::~GLWidget()
{
}

void GLWidget::setC(double cX, double cY)
{
	m_program->link();
	m_program->bind();
	m_program->setUniformValue("texture", 0);
	m_program->setUniformValue("iter", 500);
	m_program->setUniformValue("c", QVector2D(cX, cY));
	cam.setHalfWidth(0.7);
	update();
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
	static const float coords[4][2] = {
		{-1, 1},
		{ 1, 1 },
		{1, -1},
		{-1, -1},
		
		
	};
	static const  float textCoords[4][2] = {
		{0, 1},
		{1, 1},
		{1, 0},
		{ 0, 0 },
	};
	static const int indeces[5] = { 0, 1, 2,3, 0};

	QVector <GLfloat> vertData;
	QVector <GLint> indData;
	QVector <GLfloat> textData;

	for (int i = 0; i < 4; ++i)
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

	for (int i = 0; i < 5; ++i)
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
		"{ \n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
		"}\n";
	vshader->compileSourceCode(vertSource);

	QOpenGLShader* fragShader = new QOpenGLShader(QOpenGLShader::Fragment, this);
	const char* fragSource = "uniform sampler2D texture;\n"
		"varying mediump vec4 texc;\n"
		"uniform mediump vec2 c;\n"
		"uniform int iter;\n"
		"void main(void)\n"
		"{\n"

		"mediump vec2 z;\n"
		"mediump vec2 t;\n"
		"z.x = 4.0 * (texc.x - 0.5);\n"
		"z.y = 4.0 * (texc.y - 0.5);\n"
		
		"int i;\n"
		"for (i = 0; i<iter; i++)\n"
		"{\n"
			"mediump float x = (z.x * z.x - z.y * z.y) + c.x;\n"
			"mediump float y = (z.y * z.x + z.x * z.y) + c.y;\n"

			"if ((x * x + y * y) > 4.0) break;\n"
			"z.x = x;\n"
			"z.y = y;\n"
		"}\n"
		
		"t.y = 0.5;\n"
		"if(i== iter)\n"
			"t.x = 0.0; \n"	
		"else t.x = float(i) / 100.0;\n"

		"gl_FragColor = texture2D(texture, t);\n"				//xyzw rgba stpq
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
	m_program->setUniformValue("iter", 500);
	setC(-0.4, 0.6);
	
	
}

void GLWidget::resizeGL(int width, int height)
{
	
	m_side = qMin(width, height);
	m_projection.setToIdentity();
	//m_projection.ortho(-2, 2, -2, 2, -1, 1);
	m_projection.viewport((width - m_side) / 2, (height - m_side) / 2, m_side, m_side);
	//m_projection.perspective(30, (GLfloat)width / height, -1, 1);
	m_scaling = cam.halfWidth()*2/ m_side;
	
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	
	m_program->setUniformValue("matrix", cam.viewMatrix());
	m_program->enableAttributeArray(VERTEX_ATTR);
	m_program->enableAttributeArray(TEXTURE_ATTR);
	m_program->setAttributeBuffer(VERTEX_ATTR, GL_FLOAT, 0, 2, 4 * sizeof(GLfloat));
	m_program->setAttributeBuffer(TEXTURE_ATTR, GL_FLOAT, 2 * sizeof(GLfloat), 2, 4 * sizeof(GLfloat));

	m_texture->bind();

	glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 4);
	
	
}
