#include <QtGui>
#include <QtOpenGL>

#include <cmath>

#include "viewer3D.h"

Viewer3D::Viewer3D(std::vector <std::vector <int> > array, QWidget *parent)
	: QGLWidget(parent)
{
	int i,j, topx, topy;
	object = 0;
	xRot = 0;
	yRot = 0;
	zRot = 0;
	zx=0; zy=0;
	topx=array.size();
	topy=array[0].size();
	SurfaceArray.resize(topx);
	MAXZ=array[0][0];
	for(i=0; i<topx;i++){
		SurfaceArray[i].resize(topy);
		for(j=0;j<topy;j++){
			SurfaceArray[i][j]=array[i][j];
			if(array[i][j]>MAXZ) MAXZ=array[i][j];
		}
	}
	MINX=0; MINY=0;
	MAXX=topx; MAXY=topy;
		

	//trolltechGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
//	trolltechPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
}

Viewer3D::~Viewer3D()
{
	makeCurrent();
	glDeleteLists(object, 1);
}

QSize Viewer3D::minimumSizeHint() const
{
	return QSize(0,0);
}

QSize Viewer3D::sizeHint() const
{
	return QSize(MAXX, MAXY);
}

void Viewer3D::setXRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != xRot) {
		xRot = angle;
		updateGL();
	}
}

void Viewer3D::setYRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != yRot) {
		yRot = angle;
		updateGL();
	}
}

void Viewer3D::setZRotation(int angle)
{
	normalizeAngle(&angle);
	if (angle != zRot) {
		zRot = angle;
		updateGL();
	}
}

void Viewer3D::initializeGL()
{
	qglClearColor(trolltechPurple.dark());
	object = makeObject();
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	GLfloat lightDiffuse[] = {1, 1, 1, 1};    
	GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 0.2f};
	GLfloat lightSpecular[] = {0.2f, 0.2f, 0.2f, 0.2f}; 
	GLfloat lightPosition[] = {((GLfloat)MAXX)/2.0f, -2, 30, 1.0f};

    //Ambient light component
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    //Diffuse light component
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    //Light position
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void Viewer3D::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
//	glTranslated(-100.0, -100.0, -100.0);
	glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
	glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
	glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
	glTranslatef(zx,zy,0);
	glCallList(object);
}

void Viewer3D::resizeGL(int width, int height)
{
	int side = qMin(width, height);
	glViewport((width - side) / 2, (height - side) / 2, side, side);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, MAXX+100, -100, MAXY+100, -1500, 1500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Viewer3D::mousePressEvent(QMouseEvent *event)
{
	lastPos = event->pos();
}

void Viewer3D::wheelEvent ( QWheelEvent *event )
{
	zx += event->x() -lastWheel.x();
	zy += event->y() - lastWheel.y();
	lastWheel = event->pos();
	updateGL();
}
void Viewer3D::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot + 8 * dy);
		setYRotation(yRot + 8 * dx);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot + 8 * dy);
		setZRotation(zRot + 8 * dx);
	}
	lastPos = event->pos();
}

GLuint Viewer3D::makeObject()
{
	GLuint list = glGenLists(1);
	glNewList(list, GL_COMPILE);

	GLdouble x1,x2,i,j;
	GLdouble y1,y2;
	GLdouble z1,z2;
	step=1;
	glColor3d(0.3, 1.0, 0.1);
	for(j=MINY;j<MAXY-step;j=j+step){
		glBegin(GL_LINE_STRIP);
		for(i=MINX;i<MAXX-step;i=i+step){
			x1=i; y1=j; z1=(GLdouble) SurfaceArray[x1][MAXY-y1-1];
			if(abs(z1)>MAXZ) z1=MAXZ*z1/abs(z1);
			x2=(i+step); y2=j; z2=SurfaceArray[x2][MAXY-y2-1];
			if(abs(z2)>MAXZ) z2=MAXZ*z2/abs(z2);
			glVertex3d(x1,y1,-z1);
			glVertex3d(x2,y2,-z2);
		}
		glEnd();
	}
	
	for(i=MINX;i<MAXX-step;i=i+step){
		glBegin(GL_LINE_STRIP);
		for(j=MINY;j<MAXY-step;j=j+step){
			x1=i; y1=j; z1=SurfaceArray[x1][MAXY-y1-1];
			if(abs(z1)>MAXZ) z1=MAXZ*z1/abs(z1);
			x2=i; y2=j+step; z2=SurfaceArray[x2][MAXY-y2-1];
			if(abs(z2)>MAXZ) z2=MAXZ*z2/abs(z2);
			glVertex3d(x1,y1,-z1);
			glVertex3d(x2,y2,-z2);
		}
		glEnd();
	}
	glEndList();
	return list;
}
void Viewer3D::normalizeAngle(int *angle)
{
	while (*angle < 0)
		*angle += 360 * 16;
	while (*angle > 360 * 16)
		*angle -= 360 * 16;
}
