#include "Fractal2D.h"
#include "fractalviewer.h"
#include <QtGui>
#include <unistd.h>


int variable=5;


int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	QPixmap pixmap(":/images/inicio.jpg");
	QSplashScreen splash(pixmap);
	//splash.showMessage("Cloud Analyzer",Qt::AlignCenter,  Qt::magenta);

	splash.show();
	app.processEvents();
	
	FractalViewer fractalViewer;
	//fractalViewer.showMaximized();
	fractalViewer.show();
	sleep(1);
	splash.finish(&fractalViewer);
    return app.exec();
}
