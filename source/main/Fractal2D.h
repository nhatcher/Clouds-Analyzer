
#ifndef FRACTAL2D_H
#define FRACTAL2D_H

#include <QObject>
#include <vector>
#include <QWidget>
#include <QLabel>
#include <QDialog>
#include "kochgen.h"
#include "cloudsgen.h"
#include "clouds3Dgen.h"
#include "fbm1dgen.h"
#include "cloudsdriver.h"
#include "clouds3Ddriver.h"
#include "fbm1ddriver.h"
#include "HenonMap.h"
#include "Components.h"
#include <stdio.h>

#include <QtGui>

using namespace std;

class QLabel;
class QPushButton;
class QHBoxLayout;
class QComboBox;
class QImage;
class QScrollArea;
class QLineEdit;
class KochPage;
class Fbm1dPage;
class CloudsPage;
class Clouds3DPage;
class HenonPage;


class CalculateAreaPerimeterWidget;

class QStackedLayout;
class BoxCountingCalculator;
class CorrelationCalculator;
class RenyiCalculator;
class CalculateAreaPerimeterOptions;
class DrawWidget;
class MetricSpaceTechnique;
class Viewer3D;
class QScrollArea;

class Fractal2D : public QWidget
{
    Q_OBJECT

    public:
  Fractal2D(QWidget *parent = 0);
  ~Fractal2D(){};
  void putImage(std::vector<std::vector<int> > array);
  void putImage(std::vector<int>  array1d);
  void putImage(int L, std::vector<std::vector< std::vector <int> > > array3d);
  void putImage(void);
  void loadImage(QImage I);
  QImage getImage(void){return fimage;};
  void setImageArray(std::vector<std::vector<int> > array);
  void setImageArray(std::vector<int>  array1d);
  void setImageArray(std::vector<std::vector< std::vector <int> > > array3d);

  MetricSpaceTechnique *MetricTechnique;
  DrawWidget *drawFilamentIndex;
  DrawWidget *drawFilamentIndexKhalil;
  Viewer3D *window3D;
    public slots:
  // void generate();
  void generateKoch(void);
  void generateFbm1d(void);
  void generateHenon(void);
  void generateClouds(void);
  void generateClouds3D(void);
  void contour(void);
  void grayScale(void);
  void setThreshold( int T){Threshold=T;};
  // void setCurrentIndex(int index);
  void Repaint();
  void calculate(void);
  void calculateCorr(void);
  void calculateRenyi(void);
  void calculateOptions(void);
  void calculateCorrOptions(void);
  void calculateRenyiOptions(void);
  void calculateAreaPerimeterOptions(void);
  void calculateAreaPerimeter(void);

  void setZImage(int z);
  void mountainView(void);
  void Projection(void);
    signals:
  void positionChanged(int , int );

    protected:
  void mousePressEvent( QMouseEvent *Mevent);
  void mouseMoveEvent( QMouseEvent *Mevent);
  void mouseReleaseEvent( QMouseEvent *Mevent);
    private:
  QImage fimage;
  vector < vector < vector <int> > > ImageArray3d;
  vector < vector <int> > ImageArray2d;
  vector <int>  ImageArray1d;
  QLabel *fractalimage;
  KochPage *KochWidget;
  HenonPage *HenonWidget;
  CloudsPage *CloudsWidget;
  Clouds3DPage *Clouds3DWidget;
  Fbm1dPage *Fbm1dWidget;
  BoxCountingCalculator *Calculate;
  CorrelationCalculator *CalculateCorr;
    RenyiCalculator *CalculateRenyi;

  CalculateAreaPerimeterWidget *CalculateAreaPerimeter;
  QScrollArea *scrollAreaFractal;
  CalculateAreaPerimeterOptions *calculateoptionsap;
  QStackedLayout *OptionsLayout;
  // int currentIndex;
  int Threshold;
  QPushButton *showContourButton;
  QVBoxLayout *rightLayout;

  uint minPosX, minPosY, maxPosX, maxPosY;

};

#endif
