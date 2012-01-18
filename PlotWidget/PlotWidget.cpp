#include "PlotWidget.h"
#include <vector>
#include <cmath>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QtGui>

using namespace std;

PlotWidget::PlotWidget( QWidget *parent): QWidget(parent)
{
    ImageLabel= new QLabel;
    InformationLabel = new QLabel;
    QPushButton *saveDataButton = new QPushButton(tr("Save Data"));
    saveDataButton->setFixedSize(100,30);
    QPushButton *saveImageButton = new QPushButton(tr("Save Image"));
    saveImageButton->setFixedSize(100,30);
    
    connect(saveDataButton,SIGNAL(clicked()), this,SLOT(saveData()));
    connect(saveImageButton,SIGNAL(clicked()), this,SLOT(saveImage()));
    QVBoxLayout *Layout = new QVBoxLayout;
    Layout->addWidget(ImageLabel);
    Layout->addWidget(InformationLabel);
    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addStretch();
    HLayout->addWidget(saveDataButton);
    HLayout->addWidget(saveImageButton);
    
    Layout->addLayout(HLayout);
    setLayout(Layout);
    LinearFitEnabled=false;
    setMinimumHeight(140);
}

void PlotWidget::setData(std::vector<double> x, std::vector<double> y)
{
    int N=x.size();
    int M=y.size();
    if(N>M) N=M;
    XCoord.resize(N);
    YCoord.resize(N);
    for(int i=0;i<N;i++){
        XCoord[i]=x[i];
        YCoord[i]=y[i];
    }
}

void PlotWidget::setData(std::vector<double> y)
{
    int N=y.size();
    XCoord.resize(N);
    YCoord.resize(N);
    for(int i=0;i<N;i++){
        XCoord[i]=i;
        YCoord[i]=y[i];
    }
}

void PlotWidget::saveData(void)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(),  tr("Data (*.txt)"));     
    QFile file(fileName);
    file.open( QIODevice::WriteOnly);
    QTextStream stream( &file );
    for (int i =0; i<XCoord.size(); i++) {
        stream <<  XCoord[i] << "\t" << YCoord[i] << endl;
    }
    file.close();
}
void PlotWidget::saveImage(void)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), tr("Image (*.png, *.jpg)"));
    imagen.save(fileName);
}
void PlotWidget::resizeEvent(QResizeEvent *event)
{
    double maxX=XCoord[0], maxY=YCoord[0], minX=XCoord[0], minY=YCoord[0];
    uint i;
    int longX=width()-80;
    int longY=height()-140;
    for(i=0; i< XCoord.size(); i++){
        if(minX>XCoord[i]) minX=XCoord[i];
        if(maxX<XCoord[i]) maxX=XCoord[i];
        if(minY>YCoord[i]) minY=YCoord[i];
        if(maxY<YCoord[i]) maxY=YCoord[i];
    }
    double x,y;
    imagen=QImage(longX+30,longY+30,QImage::Format_RGB32);
    QPainter painter;
    painter.begin(&imagen);
    painter.eraseRect(0,0,longX+30,longY+30);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    for(i=0;i<=XCoord.size();i++){
        x=(XCoord[i]-minX)*longX/(maxX-minX)+30;
        y=(YCoord[i]-minY)*longY/(maxY-minY);
        painter.drawEllipse(x,longY-y,5,5);
    }
    painter.setPen(Qt::black);
    if(LinearFitEnabled){
        painter.drawLine(30,longY- ((minX*Plot_m+Plot_b)-minY)*longY/(maxY-minY),longX+30,longY-((maxX*Plot_m+Plot_b)-minY)*longY/(maxY-minY));
    }
    painter.end();
    ImageLabel->setPixmap(QPixmap::fromImage(imagen));
    //  ImageLabel->adjustSize();
    QWidget::resizeEvent(event);
}
void PlotWidget::makePlot( void )
{
    if(LinearFitEnabled){
        Information="";
        QTextStream out(&Information);
        out << "y(x)="  <<Plot_m<<"x"<<"+"<<Plot_b<< endl;
        out << "R^2=" << Plot_RSqu << endl;
    }
    InformationLabel->setText(Information);
    
    
    double maxX=XCoord[0], maxY=YCoord[0], minX=XCoord[0], minY=YCoord[0];
    uint i;
    int longX=width()-80;
    int longY=height()-140;
    for(i=0; i< XCoord.size(); i++){
        if(minX>XCoord[i]) minX=XCoord[i];
        if(maxX<XCoord[i]) maxX=XCoord[i];
        if(minY>YCoord[i]) minY=YCoord[i];
        if(maxY<YCoord[i]) maxY=YCoord[i];
    }
    double x,y;
    imagen=QImage(longX+40,longY+40,QImage::Format_RGB32);
    QPainter painter;
    painter.begin(&imagen);
    painter.eraseRect(0,0,longX+40,longY+40);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    for(i=0;i<=XCoord.size();i++){
        x=(XCoord[i]-minX)*longX/(maxX-minX)+30;
        y=(YCoord[i]-minY)*longY/(maxY-minY);
        painter.drawEllipse(x,longY-y,5,5);
    }
    painter.setPen(Qt::black);
    if(LinearFitEnabled){
        painter.drawLine(30,longY- ((minX*Plot_m+Plot_b)-minY)*longY/(maxY-minY),longX+30,longY-((maxX*Plot_m+Plot_b)-minY)*longY/(maxY-minY));
    }
    painter.end();
    ImageLabel->setPixmap(QPixmap::fromImage(imagen));
}
void PlotWidget::setType(QString Type)
{
    uint i;
    if(Type=="LOG-LOG"){
        for( i=0;i<XCoord.size();i++){
            XCoord[i]=log(XCoord[i]);
            YCoord[i]=log(YCoord[i]);
        }
    }
    if(Type=="X-LOG"){
        for( i=0;i<XCoord.size();i++){
            YCoord[i]=log(YCoord[i]);
        }
    }
    if(Type=="LOG-Y"){
        for( i=0;i<XCoord.size();i++) XCoord[i]=log(XCoord[i]);
    }
}

void PlotWidget::AddInformation( QString moreInformation)
{
    QString Information=InformationLabel->text();
    Information=Information+moreInformation;
    InformationLabel->setText(Information);
}

void PlotWidget::linearFit()
{
    uint i;
    double XSqu = 0, Xlin = 0, Ylin = 0, XY = 0;
    for( i=0;i<XCoord.size();i++){
        
        Xlin += XCoord[i];
        Ylin += YCoord[i];
        XY += XCoord[i]*YCoord[i];
        XSqu += XCoord[i]*XCoord[i];
    }
    
    Plot_m = ((XCoord.size())*XY - Xlin*Ylin)/((XCoord.size())*XSqu-Xlin*Xlin);
    Plot_b = (Ylin*XSqu - Xlin*XY)/((XCoord.size())*XSqu-Xlin*Xlin);
    
    double SSerr, SStot, YAverage = 0;
    SSerr = 0; SStot = 0;
    for( i = 0; i < XCoord.size(); i++){
        SSerr += (YCoord[i] - (Plot_m)*XCoord[i] - Plot_b)*(YCoord[i] - (Plot_m)*XCoord[i] - Plot_b);	
        YAverage += YCoord[i];
    } 
    YAverage = YAverage/YCoord.size();
    for(i = 0; i < YCoord.size(); i++){
        SStot += (YCoord[i] - YAverage)* (YCoord[i] - YAverage);
    }
    Plot_RSqu = 1- SSerr/SStot;	
    LinearFitEnabled=true;
}