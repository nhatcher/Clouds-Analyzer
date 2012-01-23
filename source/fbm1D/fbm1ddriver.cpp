
#include "fbm1ddriver.h"
#include "fbm1dgen.h"
#include <QtGui>


Fbm1dPage::Fbm1dPage(QWidget *parent) : QWidget(parent)
{
    QLabel *Fbm1dHurstLabel= new QLabel ("Hurst Exponent= ");
    QDoubleSpinBox *Fbm1dHurstBox = new QDoubleSpinBox;
    Fbm1dNLabel = new QLabel("Width = ");
    QLabel *Fbm1dMLabel = new QLabel("Height = ");
    Fbm1dNBox = new QSpinBox;
    QSpinBox *Fbm1dMBox = new QSpinBox;	
    GenerateFbm1dBox = new QComboBox;
    QLabel *GenerateFbm1dLabel = new QLabel("Generation Method : ");
	
    QHBoxLayout *Fbm1dHurstLayout = new QHBoxLayout;
    Fbm1dHurstLayout->addWidget(Fbm1dHurstLabel);
    Fbm1dHurstLayout->addWidget(Fbm1dHurstBox);
    Fbm1dHurstLayout->addStretch();
    	
    QHBoxLayout *Fbm1dNLayout = new QHBoxLayout;
    Fbm1dNLayout->addWidget(Fbm1dNLabel);
    Fbm1dNLayout->addWidget(Fbm1dNBox);
    Fbm1dNLayout->addStretch();
	
    QHBoxLayout *Fbm1dMLayout = new QHBoxLayout;
    Fbm1dMLayout->addWidget(Fbm1dMLabel);
    Fbm1dMLayout->addWidget(Fbm1dMBox);
    Fbm1dMLayout->addStretch();
    Fbm1dHurstBox->setRange(0,1);
    Fbm1dHurstBox->setValue(0.7); Fbm1d_Hurst=0.7;
    Fbm1dHurstBox->setSingleStep(0.01);
    Fbm1dNBox->setRange(1,1025);
    Fbm1dNBox->setValue(513); Fbm1d_N=513;
    Fbm1dNBox->setSingleStep(10);
    Fbm1dMBox->setRange(1,1025);
    Fbm1dMBox->setValue(200); Fbm1d_M=200;
    Fbm1dMBox->setSingleStep(10);
	
	QVBoxLayout *GenerateFbm1MLayout = new QVBoxLayout;
	GenerateFbm1dBox->addItem("Fourier");
	GenerateFbm1dBox->addItem("Random Midpoint Displacement");
	GenerateIndex = 0; 
	GenerateFbm1MLayout->addWidget(GenerateFbm1dLabel);
	GenerateFbm1MLayout->addWidget(GenerateFbm1dBox);
	GenerateFbm1MLayout->addStretch();
	
    QVBoxLayout *Fbm1dLayout = new QVBoxLayout;
    Fbm1dLayout->addLayout(Fbm1dHurstLayout);
    Fbm1dLayout->addLayout(Fbm1dNLayout);
    Fbm1dLayout->addLayout(Fbm1dMLayout); 
    Fbm1dLayout->addLayout(GenerateFbm1MLayout);
    Fbm1dLayout->addStretch();
    setLayout(Fbm1dLayout);
    graphfBm = new fbm1d();
    
    connect(Fbm1dHurstBox, SIGNAL (valueChanged(double)),this,SLOT(setFbm1dHurst(double)));
    connect(Fbm1dNBox, SIGNAL (valueChanged(int)),this, SLOT(setFbm1dN(int)));
    connect(Fbm1dMBox, SIGNAL (valueChanged(int)),this, SLOT(setFbm1dM(int)));
    connect(GenerateFbm1dBox, SIGNAL (activated(int)),this, SLOT(setGenerateIndex(int)));
    connect(GenerateFbm1dBox, SIGNAL (activated(int)),this, SLOT(changeBoxBehaviour(int)));
	Update();
}

void Fbm1dPage::changeBoxBehaviour(int caso)
{
switch(caso){
case 0:
Fbm1dNBox->setRange(1,2049);
Fbm1dNBox->setValue(513); Fbm1d_N=513;
Fbm1dNBox->setSingleStep(10);
Fbm1dNLabel->setText("Width = "); 
break;
case 1:
Fbm1dNBox->setRange(5,11);
Fbm1dNBox->setValue(9); Fbm1d_N=9;
Fbm1dNBox->setSingleStep(1);
Fbm1dNLabel->setText("Size 2^N, N = "); 
break;
}}

void Fbm1dPage::Update(void)
{
    graphfBm->setN((unsigned int)Fbm1d_N);
    graphfBm->setM((unsigned int)Fbm1d_M);
    graphfBm->setHurst(Fbm1d_Hurst);
	graphfBm->setGenerateMethod(GenerateIndex);
}
