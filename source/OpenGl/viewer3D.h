#ifndef VIEWER3D_H
#define VIEWER3D_H
#include <QGLWidget>

class Viewer3D : public QGLWidget
{
    Q_OBJECT

public:
	Viewer3D(std::vector <std::vector <int> > array, QWidget *parent = 0);
    ~Viewer3D();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent ( QWheelEvent *event );

private:
    GLuint makeObject();
    void normalizeAngle(int *angle);
	std::vector <std::vector <GLint> > SurfaceArray;
	GLdouble MAXZ, MINX, MAXX, MINY,MAXY;
	GLdouble step;

    GLuint object;
    int xRot;
    int yRot;
    int zRot;
	int zx, zy;
	QPoint lastPos,lastWheel;
    QColor trolltechGreen;
    QColor trolltechPurple;
};

#endif
