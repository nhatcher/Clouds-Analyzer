#include "CorrelationDimensionCalculator.h"
#include "PlotWidget.h"

#include <QtGui>

#include <vector>
#include <cmath>
#include <iostream>
#include <complex>

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <stdio.h>

#define PI 3.1415926

using namespace std;

CorrelationCalculator::CorrelationCalculator (){
    plotter = new PlotWidget();
    Tmax=60;
    Tmin=10;
    TmaxBox = new QSpinBox;
    QLabel *TmaxLabel = new QLabel;
    TmaxLabel->setText("Tmax=");
    TmaxBox->setRange(2,100);
    TmaxBox->setValue(Tmax);
    
    TminBox = new QSpinBox;
    QLabel *TminLabel = new QLabel;
    TminLabel->setText("Tmin= ");
    TminBox->setRange(1,99);
    TminBox->setValue(Tmin);
    
    QHBoxLayout *TmaxLayout = new QHBoxLayout;
    TmaxLayout->addWidget(TmaxLabel);
    TmaxLayout->addWidget(TmaxBox);
    TmaxLayout->addStretch();
    
    QHBoxLayout *TminLayout = new QHBoxLayout;
    TminLayout->addWidget(TminLabel);
    TminLayout->addWidget(TminBox);
    TminLayout->addStretch();
    
    QPushButton *OKButton = new QPushButton(tr("&OK"));
    QPushButton *cancelButton = new QPushButton(tr("&Cancel"));
    
    QHBoxLayout *ButtonsLayout = new QHBoxLayout;
    ButtonsLayout->addWidget(OKButton);
    ButtonsLayout->addWidget(cancelButton);
    
    QVBoxLayout *Layout = new QVBoxLayout;
    Layout->addLayout(TmaxLayout);
    Layout->addLayout(TminLayout);
    Layout->addLayout(ButtonsLayout);
    setLayout(Layout);
    
    connect(OKButton, SIGNAL (clicked()), this, SLOT(acceptar()));
    connect(cancelButton, SIGNAL (clicked()), this, SLOT(close()));
    setWindowTitle("Correlation Settings");
    setWindowIcon(QIcon(":/images/correlation.png"));
};


void CorrelationCalculator::acceptar()
{
    Tmin=TminBox->value();
    Tmax=TmaxBox->value();
    close();
}

void CorrelationCalculator::setData(std::vector<std::vector<bool> > Image)
{
    int N=Image.size();
    int M=Image[0].size();
    int i,j;
    ImageBool.resize(N);
    for(i=0;i<N;i++){
        ImageBool[i].resize(M);
        for(j=0;j<M;j++){
            ImageBool[i][j]=Image[i][j];
        }
    }
}

void CorrelationCalculator::calculate()
{
    vector <double> XCoord,YCoord;
    XCoord.resize(Tmax-Tmin+1);
    YCoord.resize(Tmax-Tmin+1);
    QString Information;
    
    int t;
    double Num=0;
    uint Np[Tmax+1-Tmin];	
    int N=ImageBool.size();
    int M=ImageBool[0].size();
    int Amax, Amin, Bmax, Bmin;
    int i,j,a,b;
    for(i=0; i<N;i++){
        for(j=0;j<M;j++){
            if(ImageBool[i][j]==true)
                Num++;
        }
    }
    for(t=Tmin; t<Tmax+1;t++) Np[t-Tmin]=0;
    for(i=0; i<N;i++){
        for(j=0;j<M;j++){
            if(ImageBool[i][j]==true){
                if(i<Tmax) Amin=i; else Amin=Tmax;
                if(i+Tmax>N) Amax=N-i; else Amax=Tmax;
                if(j<Tmax) Bmin=j; else Bmin=Tmax;
                if(j+Tmax>M) Bmax=M-j; else Bmax=Tmax;
                for(a=-Amin;a<Amax;a++){
                    for(b=0;b<Bmax;b++){
                        if(b==0 && a<0) a=0;
                        if(ImageBool[i+a][j+b]==true && !(b==0 && a==0))
                        {
                            for(t=sqrt(a*a+b*b)+1;t<Tmax+1;t++) Np[t-Tmin]++;
                        }
                    }
                }
            }
        }
    }
    for(t=Tmin;t<Tmax+1;t++){
        XCoord[t-Tmin] = static_cast<double>(t);
        YCoord[t-Tmin] = static_cast<double>(Np[t-Tmin])/(Num*(Num)); 
    }
    plotter->setData(XCoord,YCoord);
    plotter->setType("LOG-LOG");
    plotter->linearFit();
   // plotter->AddInformation(Num)
    plotter->makePlot();
    plotter->show();
}
