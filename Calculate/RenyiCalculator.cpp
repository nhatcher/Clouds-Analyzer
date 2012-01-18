#include "RenyiCalculator.h"
#include "PlotWidget.h"

#include <QtGui>

#include <vector>
#include <cmath>
#include <complex>

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <iostream>

#define PI 3.1415926

using namespace std;

RenyiCalculator::RenyiCalculator ()
{
    plotter = new PlotWidget();
    Tmin=10;
    Step=1;
    Factor=1.2;
    NumBoxes=20;
    xOff=0;
    yOff=0;
    varOff=10;
    varAngle=10;
    Renyi_q=2;
    boxes.resize(NumBoxes);
    for(int i=0;i<NumBoxes;i++){
        boxes[i]=Step*i+Tmin;
    }
    QLabel *RenyiLabel = new QLabel("Renyi q= ");
    RenyiBox = new QDoubleSpinBox;
    RenyiBox->setRange(0,10);
    RenyiBox->setValue(Renyi_q);
    AritmeticCheckBox = new QRadioButton("Aritmetic");
    GeometricCheckBox = new QRadioButton("Geometric");
    AritmeticCheckBox->setChecked ( true );
    
    TminBox = new QSpinBox;
    QLabel *TminLabel = new QLabel;
    TminLabel->setText("Minimun lentgh= ");
    TminBox->setRange(1,200);
    TminBox->setValue(Tmin);
    
    StepBox = new QSpinBox;
    QLabel *StepLabel = new QLabel;
    StepLabel->setText("Step = ");
    StepBox->setRange(1,20);
    StepBox->setValue(Step);
    
    FactorBox = new QDoubleSpinBox;
    QLabel *FactorLabel = new QLabel;
    FactorLabel->setText("Factor = ");
    FactorBox->setRange(1,20);
    FactorBox->setValue(Factor);
    
    xOffSetBox = new QSpinBox;
    xOffSetBox->setValue(0);
    yOffSetBox = new QSpinBox;
    yOffSetBox->setValue(0);
    varOffSetBox = new QSpinBox;
    varOffSetBox->setValue(10);
    angleBox = new QSpinBox;
    angleBox->setValue(0);
    angleVarBox = new QSpinBox;
    angleBox->setRange(0,90);
    angleVarBox->setValue(45);
    angleVarBox->setRange(0,90);
    
    OffSetComboBox = new QComboBox();
    OffSetComboBox->addItem("Fixed");
    OffSetComboBox->addItem("Random");
    QLabel *xOffSetLabel = new QLabel("Delta x=");
    QLabel *yOffSetLabel = new QLabel("Delta y=");
    QLabel *varOffSetLabel = new QLabel("var=");
    
    AngleComboBox = new QComboBox();
    AngleComboBox->addItem("Fixed");
    AngleComboBox->addItem("Random");
    QLabel *angleLabel = new QLabel("Angle=");
    QLabel *angleVarLabel = new QLabel("Angle Var=");
    QHBoxLayout *RenyiLayout = new QHBoxLayout;
    RenyiLayout->addWidget(RenyiLabel);
    RenyiLayout->addWidget(RenyiBox);
    QHBoxLayout *OffSetFixedLayout = new QHBoxLayout;
    OffSetFixedLayout->addWidget(xOffSetLabel);
    OffSetFixedLayout->addWidget(xOffSetBox);
    OffSetFixedLayout->addWidget(yOffSetLabel);
    OffSetFixedLayout->addWidget(yOffSetBox);
    
    QHBoxLayout *OffSetRandomLayout = new QHBoxLayout;
    OffSetRandomLayout->addWidget(varOffSetLabel);
    OffSetRandomLayout->addWidget(varOffSetBox);
    
    QHBoxLayout *angleFixedLayout = new QHBoxLayout;
    angleFixedLayout->addWidget(angleLabel);
    angleFixedLayout->addWidget(angleBox);
    
    QHBoxLayout *angleRandomLayout = new QHBoxLayout;
    angleRandomLayout->addWidget(angleVarLabel);
    angleRandomLayout->addWidget(angleVarBox);
    
    xOffSetBox->setEnabled(true);
    yOffSetBox->setEnabled(true);
    varOffSetBox->setEnabled(false);
    
    angleBox->setEnabled(true);
    angleVarBox->setEnabled(false);

    
    NumBoxesBox = new QSpinBox;
    QLabel *NumBoxesLabel = new QLabel;
    NumBoxesLabel->setText("Number of Boxes= ");
    NumBoxesBox->setRange(1,200);
    NumBoxesBox->setValue(NumBoxes);
    
    QHBoxLayout *NumBoxesLayout = new QHBoxLayout;
    NumBoxesLayout->addWidget(NumBoxesLabel);
    NumBoxesLayout->addWidget(NumBoxesBox);
    
    QHBoxLayout *AritmeticLayout = new QHBoxLayout;
    AritmeticLayout->addWidget(AritmeticCheckBox);
    AritmeticLayout->addWidget(StepLabel);
    AritmeticLayout->addWidget(StepBox);
    
    QHBoxLayout *GeometricLayout = new QHBoxLayout;
    GeometricLayout->addWidget(GeometricCheckBox);
    GeometricLayout->addWidget(FactorLabel);
    GeometricLayout->addWidget(FactorBox);
    
    
    QHBoxLayout *TminLayout = new QHBoxLayout;
    TminLayout->addWidget(TminLabel);
    TminLayout->addWidget(TminBox);
    TminLayout->addStretch();
    
    QPushButton *OKButton = new QPushButton(tr("&OK"));
    QPushButton *cancelButton = new QPushButton(tr("&Cancel"));
    goButton = new QPushButton(tr("&Go!"));
    goButton->setEnabled(false);
    
    QHBoxLayout *ButtonsLayout = new QHBoxLayout;
    ButtonsLayout->addWidget(goButton);
    ButtonsLayout->addStretch();
    ButtonsLayout->addWidget(OKButton);
    ButtonsLayout->addWidget(cancelButton);
    
    QVBoxLayout *Layout = new QVBoxLayout;
    Layout->addLayout(RenyiLayout);
    Layout->addLayout(NumBoxesLayout);
    Layout->addLayout(AritmeticLayout);
    Layout->addLayout(GeometricLayout);
    Layout->addLayout(TminLayout);
    Layout->addWidget(OffSetComboBox);
    Layout->addLayout(OffSetFixedLayout);
    //Layout->addLayout(OffSetRandomLayout);
    //Layout->addWidget(AngleComboBox);
    //Layout->addLayout(angleFixedLayout);
    //Layout->addLayout(angleRandomLayout);
    //Layout->addLayout(ButtonsLayout);
    setLayout(Layout);
    
    connect(OKButton, SIGNAL (clicked()), this, SLOT(aceptar()));
    connect(OKButton, SIGNAL (clicked()), this, SLOT(close()));
    connect(cancelButton, SIGNAL (clicked()), this, SLOT(close()));
    connect(goButton,SIGNAL(clicked()),this,SLOT(aceptar()));
    connect(goButton,SIGNAL(clicked()), this, SLOT(calculate()));
    connect(OffSetComboBox, SIGNAL(activated(int)), this, SLOT(changeOffSet(int)));
    connect(AngleComboBox, SIGNAL(activated(int)), this, SLOT(changeAngle(int)));
    setWindowTitle("Renyi Settings");
    setWindowIcon(QIcon(":/images/renyi.png"));
};

void RenyiCalculator::changeOffSet(int index)
{
    if(index==1)
    {
        xOffSetBox->setEnabled(false);
        yOffSetBox->setEnabled(false);
        varOffSetBox->setEnabled(true);
    } else
    {
        xOffSetBox->setEnabled(true);
        yOffSetBox->setEnabled(true);
        varOffSetBox->setEnabled(false);
    }
}
void RenyiCalculator::changeAngle(int index)
{
    if(index==0)
    {
        angleBox->setEnabled(true);
        angleVarBox->setEnabled(false);
    } else{
        angleBox->setEnabled(false);
        angleVarBox->setEnabled(true);
    }
}

void RenyiCalculator::aceptar()
{
    int i;
    Tmin=TminBox->value();
    Step=StepBox->value();
    Factor=FactorBox->value();
     Renyi_q=RenyiBox->value();
    NumBoxes=NumBoxesBox->value();
    xOff=xOffSetBox->value();
    yOff=yOffSetBox->value();
    varOff=varOffSetBox->value();
    boxes.resize(NumBoxes);
    if(AritmeticCheckBox->isChecked()){
        for(i=0;i<NumBoxes;i++){
            boxes[i]=Step*i+Tmin;
        }
    } else {
        for(i=0;i<NumBoxes;i++){
            boxes[i]=pow(Factor,i)*Tmin;
        }
    }
}

void RenyiCalculator::setData(std::vector<std::vector<bool> > Image)
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
    goButton->setEnabled(true);
}

void RenyiCalculator::calculate()
{
    vector <double> XCoord,YCoord;
    int t;
    int dx, dy;
    int NumPoints;
    double Np[NumBoxes];
    int N=ImageBool.size();
    int M=ImageBool[0].size();
    int i,j,k;
    int x0, y0,x,y;
    XCoord.resize(NumBoxes);
    YCoord.resize(NumBoxes);
    for(k=0; k<NumBoxes;k++){
        if(OffSetComboBox->currentIndex()==1){
            x0=rand()%varOff;
            y0=rand()%varOff;
        } else {
            x0=xOff; y0=yOff;
        }
        t=boxes[k];
        while(t<x0) x0-=t;
        while(t<y0) y0-=t;
        Np[k]=0;
        for(i=-1; i<=(N-x0)/t;i++){
            for(j=-1; j<=(M-y0)/t;j++){
                NumPoints=0;
                for(dx=0; dx<t; dx++){
                    for(dy=0; dy<t; dy++){
                        x=x0+i*t+dx;
                        y=y0+j*t+dy;
                        if(x>=0 && x<N && y>=0 && y<M){
                            if(ImageBool[x][y]==true) NumPoints++;
                        }
                    }
                }
                Np[k]+=pow(NumPoints,Renyi_q);
            }
        }        
        XCoord[k]=log(static_cast<double>(t));
        YCoord[k]=log(static_cast<double>(Np[k]))/(Renyi_q-1);
    }
    plotter->setData(XCoord,YCoord);
    plotter->setType("X-Y");
    plotter->linearFit();
    plotter->makePlot();
    plotter->show();
}

