
#include "Fractal2D.h"
#include "AreaPerimeterCalculator.h"
#include "kochdriver.h"
#include "fbm1ddriver.h"
#include "HenonMap.h"
#include "BoxCountingCalculator.h"
#include "RenyiCalculator.h"
#include "CorrelationDimensionCalculator.h"

#include "DrawWidget.h"
#include "viewer3D.h"
#include <fstream>
#include <string.h>
#include <stdio.h>


#include <QtGui>
#include <qfile.h>
#include <vector>


Fractal2D::Fractal2D(QWidget *parent) : QWidget(parent)
{
    showContourButton = new QPushButton(tr("Show Contour"));
    QPushButton *grayScaleButton = new QPushButton(tr("Gray Scale"));
    QPushButton *mountainButton = new QPushButton(tr("Mountain View"));
    QPushButton *projectionButton = new QPushButton(tr("Projection 3D->2D"));

    //showContourButton->setEnabled(false);
    setMouseTracking (true);

    KochWidget = new KochPage;
    Fbm1dWidget = new Fbm1dPage;
    CloudsWidget = new CloudsPage;
    Clouds3DWidget = new Clouds3DPage;
    HenonWidget = new HenonPage;
    Calculate = new BoxCountingCalculator;
    CalculateCorr = new CorrelationCalculator;
    CalculateRenyi = new RenyiCalculator;
    CalculateAreaPerimeter = new CalculateAreaPerimeterWidget;
    MetricTechnique = new MetricSpaceTechnique;

    OptionsLayout = new QStackedLayout;
    OptionsLayout->addWidget(KochWidget);
    OptionsLayout->addWidget(Fbm1dWidget);
    OptionsLayout->addWidget(CloudsWidget);
    OptionsLayout->addWidget(Clouds3DWidget);
    OptionsLayout->addWidget(HenonWidget);

    QLabel *ThresholdLabel = new QLabel("Threshold = ");
    QSpinBox *ThresholdBox = new QSpinBox;
    QSlider *ThresholdSlider = new QSlider(Qt::Horizontal);
    QHBoxLayout *ThresholdLayout = new QHBoxLayout;
    ThresholdLayout->addWidget(ThresholdLabel);
    ThresholdLayout->addWidget(ThresholdBox);
    ThresholdLayout->addWidget(ThresholdSlider);
    ThresholdBox->setRange(-1,255);
    ThresholdBox->setValue(-1); Threshold=-1;
    ThresholdSlider->setRange(-1,255);
    ThresholdSlider->setValue(-1);
    Threshold=-1;

    fractalimage = new QLabel;
    fractalimage->setMouseTracking (true);
    scrollAreaFractal = new QScrollArea;
    scrollAreaFractal->setBackgroundRole(QPalette::Dark);
    scrollAreaFractal->setWidget(fractalimage);
    scrollAreaFractal->setMinimumWidth(500);
    scrollAreaFractal->setMouseTracking (true);

    connect(showContourButton, SIGNAL(clicked()),this, SLOT(contour()));
    connect(grayScaleButton, SIGNAL(clicked()),this, SLOT(grayScale()));

    connect(ThresholdBox, SIGNAL (valueChanged(int)),this, SLOT(setThreshold(int)));
    connect(ThresholdBox, SIGNAL (valueChanged(int)), ThresholdSlider, SLOT(setValue(int)));
    connect(ThresholdSlider, SIGNAL (valueChanged(int)), ThresholdBox, SLOT(setValue(int)));
    connect(ThresholdSlider, SIGNAL (valueChanged(int)), this, SLOT(Repaint()));
    connect(Clouds3DWidget, SIGNAL(zChanged(int)), this, SLOT(setZImage(int)));
    connect(mountainButton, SIGNAL(clicked()), this, SLOT(mountainView()));
    connect(projectionButton, SIGNAL(clicked()), this, SLOT(Projection()));

    QLabel *GenerationLabel = new QLabel(tr("<center><font color = DarkBlue> FRACTAL GENERATION SETTINGS"));
    QLabel *EditionLabel = new QLabel(tr("<center><font color = DarkBlue> IMAGE EDITION OPTIONS"));
    rightLayout = new QVBoxLayout;
    rightLayout->addSpacing(10);
    rightLayout->addWidget(GenerationLabel);
    rightLayout->addLayout(OptionsLayout);
    rightLayout->addWidget(EditionLabel);
    rightLayout->addLayout(ThresholdLayout);
    rightLayout->addWidget(showContourButton);
    rightLayout->addWidget(grayScaleButton);
    rightLayout->addWidget(mountainButton);
    rightLayout->addWidget(projectionButton);
    rightLayout->addSpacing(10);
    rightLayout->addWidget(MetricTechnique);

    QWidget *rightWidget = new QWidget;
    rightWidget->setLayout(rightLayout);
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(scrollAreaFractal);
    splitter->addWidget(rightWidget);
    rightWidget->setMinimumWidth(300);
    rightWidget->setMaximumWidth(350);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);
    setLayout(mainLayout);
}

void Fractal2D::mouseMoveEvent( QMouseEvent *Mevent)
{
    unsigned int i,j;
    QRgb value;
    QImage modfimage(fimage);
    value = qRgb(120,100,40);
    int hvalue = scrollAreaFractal->horizontalScrollBar()->value();
    int vvalue = scrollAreaFractal->verticalScrollBar()->value();
    i=Mevent->x()-7+hvalue;
    j=Mevent->y()-8+vvalue;
    if(Mevent->buttons() & Qt::LeftButton && fimage.rect().contains(i,j))
    {
        unsigned int a,b;
        if(minPosX<i)
        {
            for(a=minPosX;a<=i;a++){
                modfimage.setPixel(a, minPosY,value);
                modfimage.setPixel(a, j,value);
            }
        } else
        {
            for(a=i;a<=minPosX;a++){
                modfimage.setPixel(a, minPosY,value);
                modfimage.setPixel(a, j,value);
            }
        }
        if(minPosY<j) {

            for(b=minPosY;b<=j;b++){
                modfimage.setPixel(minPosX,b,value);
                modfimage.setPixel(i,b,value);
            }
        }else{
            for(b=j;b<=minPosY;b++){
                modfimage.setPixel(minPosX,b,value);
                modfimage.setPixel(i,b,value);
            }
        }
        fractalimage->setPixmap(QPixmap::fromImage(modfimage));
        fractalimage->adjustSize();
    }
    //QWidget::mouseMoveEvent(Mevent);
}
void Fractal2D::mousePressEvent( QMouseEvent *Mevent)
{
    unsigned int i,j;
    int hvalue = scrollAreaFractal->horizontalScrollBar()->value();
    int vvalue = scrollAreaFractal->verticalScrollBar()->value();
    i=Mevent->x()-7+hvalue;
    j=Mevent->y()-8+vvalue;
    emit positionChanged(i,j);
    if(fimage.rect().contains(i,j))
    {
        minPosX=i;
        minPosY=j;
    } else
    {
        minPosX=0; minPosY=0;
        maxPosX=fimage.width();
        maxPosY=fimage.height();
    }
   // QWidget::mousePressEvent(Mevent);

}
void Fractal2D::mouseReleaseEvent( QMouseEvent *Mevent)
{
    QRgb value;
    value = qRgb(120,100,40);
    QImage modfimage(fimage);
    unsigned int i,j;
    int hvalue = scrollAreaFractal->horizontalScrollBar()->value();
    int vvalue = scrollAreaFractal->verticalScrollBar()->value();
    i=Mevent->x()-7+hvalue;
    j=Mevent->y()-8+vvalue;
    if(fimage.rect().contains(i,j))
    {
        maxPosX=i;
        maxPosY=j;
        if(maxPosX<minPosX) {i=maxPosX; maxPosX=minPosX; minPosX=i;}
        if(maxPosY<minPosY) {i=maxPosY; maxPosY=minPosY; minPosY=i;}
        for(i=minPosX;i<=maxPosX;i++){
            modfimage.setPixel(i, minPosY,value);
            modfimage.setPixel(i, maxPosY,value);
        }
        for(j=minPosY;j<=maxPosY;j++){
            modfimage.setPixel(minPosX,j,value);
            modfimage.setPixel(maxPosX,j,value);
        }
        std::vector<std::vector<int> > metricArray;
        metricArray.resize(maxPosX-minPosX);
        for(i=0; i<maxPosX-minPosX;i++){
            metricArray[i].resize(maxPosY-minPosY);
            for(j=0; j<maxPosY-minPosY;j++){
                metricArray[i][j]=ImageArray2d[i+minPosX][j+minPosY];
            }
        }
        MetricTechnique->setImageArray(metricArray);
        fractalimage->setPixmap(QPixmap::fromImage(modfimage));
        fractalimage->adjustSize();
    }
   // QWidget::mouseReleaseEvent(Mevent);
}

void Fractal2D::mountainView()
{
    if(fimage.isNull()==false) {
    window3D = new Viewer3D(ImageArray2d);
    window3D->show(); }
}

void Fractal2D::grayScale()
{

    if(fimage.isNull()==false) {
    unsigned int i,j, maxx, maxy;
    maxx=fimage.width();
    maxy=fimage.height();
    QRgb value;
    value = qRgb(0,0,0);
    int red,blue,green,gray;

    ImageArray2d.resize(maxx);
    for ( i = 0; i < ImageArray2d.size(); i++){
        ImageArray2d[i].resize(maxy); }

        for(i = 0; i < maxx  ; i++){
            for (j=0; j< maxy; j++){
                red =  qRed(fimage.pixel(i, j));
                blue = qBlue(fimage.pixel(i, j));
                green =  qGreen(fimage.pixel(i,j));
                gray = static_cast<int>((3*red + 6*blue + green)/10);
                //  ImageArray2d[i][j] = gray;
                value = qRgb(gray,gray,gray);
                if(minPosX<=i && i<=maxPosX && minPosY<=j && j<=maxPosY) fimage.setPixel(i, j,value);
            }
        }
        fractalimage->setPixmap(QPixmap::fromImage(fimage));
        fractalimage->adjustSize();}

  else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}
}

void Fractal2D::contour()
{

    if(fimage.isNull()==false) {
    unsigned int i,j, maxx, maxy;
    maxx=fimage.width ();
    maxy=fimage.height();
    QRgb value;
    if(Threshold!=-1){
        vector < vector < bool > > Edge;
        Edge.resize(maxx);
        for ( i= 0; i < maxx; i++ ){
            Edge[i].resize(maxy);
        }
        QPainter painter;
        painter.begin(&fimage);
        painter.setPen(Qt::black);
        for (i = 1; i < maxx -1 ; i++){
            for (j=1; j< maxy -1; j++){
                Edge[i][j] = false;
                if(qBlue(fimage.pixel(i,j))==0) {
                    if ( qBlue(fimage.pixel(i+1,j))!=0 || qBlue(fimage.pixel(i-1,j))!=0 || qBlue(fimage.pixel(i,j+1))!=0 || qBlue(fimage.pixel(i,j-1))!=0 ) {
                        Edge[i][j]=true;
                        painter.drawPoint(i,j);}
                }
            }
        }
        value = qRgb(255,255,255);
        for(i = 0; i < maxx  ; i++){
            for (j=0; j< maxy; j++){
                if(Edge[i][j] == false) {
                    fimage.setPixel(i, j,value);}
            }
        }
        painter.end();
    }
    else {
        QMessageBox::warning(this, tr("Warning"), tr("Please select a threshold's value"));}

    fractalimage->setPixmap(QPixmap::fromImage(fimage));
    fractalimage->adjustSize(); }

    else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}

}

/*void Fractal2D::generate(Widget) {
  Widget->Update();
  Widget->setimage();
  ImageArray1d.clear();
  ImageArray2d.clear();
  ImageArray3d.clear();
  setImageArray(Widget->getimage());
  putImage(Widget->getimage());
  fractalimage->setPixmap(QPixmap::fromImage(fimage));
  fractalimage->adjustSize();
}*/


void Fractal2D::generateKoch() {
  // generate(Widget);
  KochWidget->Update();
  KochWidget->setimage();
  ImageArray1d.clear();
  ImageArray2d.clear();
  ImageArray3d.clear();
  setImageArray(KochWidget->getimage());
  putImage(KochWidget->getimage());
  fractalimage->setPixmap(QPixmap::fromImage(fimage));
  fractalimage->adjustSize();
}

void Fractal2D::generateFbm1d() {
  Fbm1dWidget->Update();
  Fbm1dWidget->setimage();
  ImageArray1d.clear();
  ImageArray2d.clear();
  ImageArray3d.clear();
  setImageArray(Fbm1dWidget->getimage());
  putImage(Fbm1dWidget->getimage());
  fractalimage->setPixmap(QPixmap::fromImage(fimage));
  fractalimage->adjustSize();
}


void Fractal2D::generateClouds() {
  CloudsWidget->Update();
  CloudsWidget->setimage();
  ImageArray1d.clear();
  ImageArray2d.clear();
  ImageArray3d.clear();
  setImageArray(CloudsWidget->getimage());
  putImage(CloudsWidget->getimage());
  fractalimage->setPixmap(QPixmap::fromImage(fimage));
  fractalimage->adjustSize();
}

void Fractal2D::generateClouds3D() {
  Clouds3DWidget->Update();
  Clouds3DWidget->setimage();
  ImageArray1d.clear();
  ImageArray2d.clear();
  ImageArray3d.clear();
  setImageArray(Clouds3DWidget->getimage());
  putImage(10,Clouds3DWidget->getimage());
  fractalimage->setPixmap(QPixmap::fromImage(fimage));
  fractalimage->adjustSize();
}

void Fractal2D::generateHenon() {
  // HenonWidget->Update();
  HenonWidget->generate();
  ImageArray1d.clear();
  ImageArray2d.clear();
  ImageArray3d.clear();
  setImageArray(HenonWidget->getimage());
  putImage(HenonWidget->getimage());
  fractalimage->setPixmap(QPixmap::fromImage(fimage));
  fractalimage->adjustSize();
}

void Fractal2D::Projection()
{
  if(!ImageArray3d.empty()) {
  Clouds3DWidget->project();
  setImageArray(Clouds3DWidget->getprojection());
  putImage(Clouds3DWidget->getprojection());
  fractalimage->setPixmap(QPixmap::fromImage(fimage));
  fractalimage->adjustSize(); }
}

void Fractal2D::calculate()
{
    vector <vector <bool> > ImageBool;
    vector <double> XCoord;
    vector <double> YCoord;

    if(fimage.isNull()==false) {

        unsigned int i,j, maxx, maxy;//, minx,miny;
        maxx=fimage.width ();
        maxy=fimage.height();
        ImageBool.resize(maxx);
        for(i = 0; i != maxx; ++i) {
            ImageBool[i].resize(maxy);
            for(j = 0; j != maxy; ++j) {
                ImageBool[i][j]=false;
                if(qBlue(fimage.pixel(i,j))==0) ImageBool[i][j]=true;
            }
        }
        int NumBoxes=Calculate->getNumBoxes();
        XCoord.resize(NumBoxes);
        YCoord.resize(NumBoxes);
        Calculate->setData(ImageBool);
        Calculate->calculate();

    }
    else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}
}

void Fractal2D::calculateCorr()
{
    vector <vector <bool> > ImageBool;
    vector <double> XCoord;
    vector <double> YCoord;

    if(fimage.isNull()==false) {

        unsigned int i,j, maxx, maxy;//, minx,miny;
        maxx=fimage.width ();
        maxy=fimage.height();
        maxx=maxPosX-minPosX;
        maxy=maxPosY-minPosY;
        ImageBool.resize(maxx);
        for(i = minPosX; i < maxPosX; i++) {
            ImageBool[i-minPosX].resize(maxy+1);
            for(j = minPosY; j < maxPosY; j++) {
                ImageBool[i-minPosX][j-minPosY]=false;
                if(qBlue(fimage.pixel(i,j))==0) ImageBool[i-minPosX][j-minPosY]=true;
            }
        }
        unsigned int Tmax=CalculateCorr->getTmax();
        unsigned int Tmin=CalculateCorr->getTmin();
        XCoord.resize(Tmax-Tmin+1);
        YCoord.resize(Tmax-Tmin+1);
        CalculateCorr->setData(ImageBool);
        CalculateCorr->calculate();
    }
    else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));
    }
}


void Fractal2D::calculateRenyi()
{
    vector <vector <bool> > ImageBool;
    vector <double> XCoord;
    vector <double> YCoord;

    if(fimage.isNull()==false) {

        unsigned int i,j, maxx, maxy;//, minx,miny;
        maxx=fimage.width ();
        maxy=fimage.height();
        ImageBool.resize(maxx);
        for(i = 0; i != maxx; ++i) {
            ImageBool[i].resize(maxy);
            for(j = 0; j != maxy; ++j) {
                ImageBool[i][j]=false;
                if(qBlue(fimage.pixel(i,j))==0) ImageBool[i][j]=true;
            }
        }
        int NumBoxes=CalculateRenyi->getNumBoxes();
        XCoord.resize(NumBoxes);
        YCoord.resize(NumBoxes);
        CalculateRenyi->setData(ImageBool);
        CalculateRenyi->calculate();

    }
    else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}
}


void Fractal2D::calculateAreaPerimeter()
{
    if(fimage.isNull()==false) {
        AreaPerimeterCalculator *AreaPer = new AreaPerimeterCalculator;

         AreaPer->setMinimumSize(CalculateAreaPerimeter->getMinSize());
   AreaPer->setMinimumThreshold(CalculateAreaPerimeter->getMinimumThreshold());
   AreaPer->setMaximumThreshold(CalculateAreaPerimeter->getMaximumThreshold());
   AreaPer->setStep(CalculateAreaPerimeter->getNumberOfSteps());
         AreaPer->APCalculator(ImageArray2d);

    }
    else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));
    }

}


void Fractal2D::Repaint()
{
    if(fimage.isNull()==false) {
    putImage();
    fractalimage->setPixmap(QPixmap::fromImage(fimage));
    fractalimage->adjustSize();}
    else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));
    }

}

void Fractal2D::putImage(void)
{
    unsigned int maxx=ImageArray2d.size();
    unsigned int maxy=ImageArray2d[0].size(),i,j;
    unsigned int color;
    fimage = QImage (maxx,maxy,QImage::Format_RGB32);
    QRgb value;
    double max=1;
    double scale = 255.0;
    for(i = 0; i != maxx; ++i) {
        for(j = 0; j != maxy; ++j) {
            if(max < ImageArray2d[i][j]) max = ImageArray2d[i][j];
        }
    }
    scale=scale/max;

    for(i = 0; i != maxx; i++) {
        for(j = 0; j != maxy; j++) {
            color=static_cast<int>(ImageArray2d[i][j])*scale;
            if(Threshold!=-1)
            {
                if(color> (unsigned int)Threshold){ color=255;} else {color=0;}
            }
            value = qRgb(color,color,color);
            fimage.setPixel(i, j,value);
        }
    }
    minPosX=0; minPosY=0;
    maxPosX=fimage.width();
    maxPosY=fimage.height();

}

void Fractal2D::putImage(std::vector<std::vector<int> > array)
{
    unsigned int maxx=array.size();
    unsigned int maxy=array[0].size(),i,j;
    unsigned int color;
    fimage = QImage (maxx,maxy,QImage::Format_RGB32);
    QRgb value;
    double max=1;
    double scale = 255.0;
    for(i = 0; i != maxx; ++i) {
        for(j = 0; j != maxy; ++j) {
            if(max < array[i][j]) max = array[i][j];
        }
    }
    scale=scale/max;

    for(i = 0; i != maxx; i++) {
        for(j = 0; j != maxy; j++) {
            color=static_cast<int>(array[i][j])*scale;
            if(Threshold!=-1)
            {
                if(color > (unsigned int)Threshold){ color=255;} else {color=0;}
            }
            value = qRgb(color, color, color);
            fimage.setPixel(i, j,value);
        }
    }
    minPosX=0; minPosY=0;
    maxPosX=fimage.width();
    maxPosY=fimage.height();
}

void Fractal2D::setZImage(int z)
{
    putImage(z,ImageArray3d);
    fractalimage->setPixmap(QPixmap::fromImage(fimage));
    fractalimage->adjustSize();
}
void Fractal2D::putImage(int alpha, std::vector<std::vector<std::vector <int> > > array)
{
    unsigned int maxx=array.size();
    unsigned int maxy=array[0].size(),i,j;
    //  unsigned int maxz=array[0][0].size();
    unsigned int color;
    ImageArray2d.resize(maxx);
    for(i=0;i<maxy;i++)
        ImageArray2d[i].resize(maxy);
    fimage = QImage (maxx,maxy,QImage::Format_RGB32);
    QRgb value;
    double max=1;
    double scale = 255.0;
    for(i = 0; i != maxx; ++i) {
        for(j = 0; j != maxy; ++j) {
            if(max < array[i][j][alpha]) max = array[i][j][alpha];
            ImageArray2d[i][j]=ImageArray3d[i][j][alpha];
        }
    }
    scale=scale/max;

    for(i = 0; i != maxx; i++) {
        for(j = 0; j != maxy; j++) {
            color=static_cast<int>(array[i][j][alpha])*scale;
            if(Threshold!=-1)
            {
                if(color > (unsigned int)Threshold){ color=255;} else {color=0;}
            }
            value = qRgb(color, color, color);
            fimage.setPixel(i, j,value);
        }
    }
    minPosX=0; minPosY=0;
    maxPosX=fimage.width();
    maxPosY=fimage.height();
    MetricTechnique->setImageArray(ImageArray2d);
}

void Fractal2D::putImage(std::vector<int>  array1d)
{
    int maxx=array1d.size();
    int i,j;
    double maxy=array1d[0], miny=array1d[0];
    for (i=0; i < maxx; i++){
        if (array1d[i] > (int) maxy) { maxy = array1d[i];};
        if (array1d[i] < (int) miny) { miny = array1d[i];};
    }
    fimage = QImage (maxx,maxy-miny,QImage::Format_RGB32);
    QPainter painter;
    painter.begin(&fimage);

    for(i =0; i< maxx; i++){
        for(j=miny; j< maxy; j++){
            painter.setPen(Qt::white);
            painter.drawPoint(i,j-miny);
        }
    }
    painter.setPen(Qt::black);
    for(i =0; i < maxx; i++){
        painter.drawLine(i,array1d[i]-miny,i-1,array1d[i-1]-miny);
    }
    painter.end();
    minPosX=0; minPosY=0;
    maxPosX=fimage.width();
    maxPosY=fimage.height();
}


void Fractal2D::loadImage(QImage I)
{
    fimage = I;
    fractalimage->setPixmap(QPixmap::fromImage(I));

    fractalimage->adjustSize();


    unsigned int i,j, maxx, maxy;
    maxx=fimage.width ();
    maxy=fimage.height();
    ImageArray2d.resize(maxx);
    for ( i = 0; i < ImageArray2d.size(); i++){
        ImageArray2d[i].resize(maxy);
    }
    for ( i = 0; i < ImageArray2d.size(); i++){
        for ( j = 0; j < ImageArray2d[0].size(); j++){
            ImageArray2d[i][j] = (6*qBlue(fimage.pixel(i,j))+3*qRed(fimage.pixel(i,j))+qGreen(fimage.pixel(i,j)))/10;
        }
    }
    MetricTechnique->setImageArray(ImageArray2d);
    minPosX=0; minPosY=0;
    maxPosX=fimage.width();
    maxPosY=fimage.height();
}

void Fractal2D::setImageArray(std::vector<std::vector<int> > array)
{
    unsigned int i,j, maxx, maxy;
    //  std::vector<std::vector<int> > metricArray;
    maxx=array.size();
    maxy=array[0].size();
    ImageArray2d.resize(maxx);
    //  metricArray.resize(maxPosX-minPosX);
    for(i = 0; i != maxx; ++i) {
        ImageArray2d[i].resize(maxy);
        for(j = 0; j != maxy; ++j) {
            ImageArray2d[i][j]=array[i][j];
        }
    }
    //   for(i=0; i<maxPosX-minPosX;i++){
   //     metricArray[i].resize(maxPosY-minPosY);
   //     for(j=0; j<maxPosY-minPosY;j++){
   //       metricArray[i][j]=array[i+minPosX][j+maxPosY];
   //     }
   //   }
   MetricTechnique->setImageArray(ImageArray2d);

}

void Fractal2D::setImageArray(std::vector<std::vector<std::vector <int> > > array)
{
    unsigned int i,j, k, maxx, maxy, maxz;
    maxx=array.size();
    maxy=array[0].size();
    maxz=array[0][0].size();
    ImageArray3d.resize(maxx);
    for(i = 0; i != maxx; ++i) {
        ImageArray3d[i].resize(maxy);
        for(j = 0; j != maxy; ++j) {
            ImageArray3d[i][j].resize(maxz);
            for(k=0;k!=maxz;k++){
                ImageArray3d[i][j][k]=array[i][j][k];
            }
        }
    }
    //  MetricTechnique->setImageArray(ImageArray2d);
}
void Fractal2D::setImageArray( std::vector<int>  array1d)
{
    unsigned int i, maxx;
    maxx=array1d.size();
    ImageArray1d.resize(maxx);
    for(i = 0; i != maxx; ++i) {
        ImageArray1d[i] = array1d[i];
    }
}
void Fractal2D::calculateOptions()
{
    Calculate->show();
}
void Fractal2D::calculateCorrOptions()
{
    CalculateCorr->show();
}
void Fractal2D::calculateRenyiOptions()
{
    CalculateRenyi->show();
}

void Fractal2D::calculateAreaPerimeterOptions()
{

    calculateoptionsap = new CalculateAreaPerimeterOptions(CalculateAreaPerimeter->getMinSize(),CalculateAreaPerimeter->getMinimumThreshold(), CalculateAreaPerimeter->getMaximumThreshold(), CalculateAreaPerimeter->getNumberOfSteps(), this);

    if( calculateoptionsap->exec() ){
        CalculateAreaPerimeter->setMinSize(calculateoptionsap->getMinSize());
        CalculateAreaPerimeter->setMinimumThreshold(calculateoptionsap->getMinimumThreshold());
        CalculateAreaPerimeter->setMaximumThreshold(calculateoptionsap->getMaximumThreshold());
        CalculateAreaPerimeter->setNumberOfSteps(calculateoptionsap->getNumberOfSteps());

    }
}
