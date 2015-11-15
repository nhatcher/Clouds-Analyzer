#include "fractalviewer.h"
#include <QtGui>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  FractalViewer fractalViewer;
  fractalViewer.show();

  return app.exec();
}
