#include <QtGui>
#include "cloudsgen.h"
#include "cloudsdriver.h"
#include "MetricSpaceTechnique.h"

CloudsPage::CloudsPage(QWidget *parent) : QWidget(parent)
{


	QLabel *CloudsHurstLabel= new QLabel ("Hurst Exponent= ");
	QDoubleSpinBox *CloudsHurstBox = new QDoubleSpinBox;
	CloudsNLabel = new QLabel("Width = ");
	CloudsMLabel = new QLabel("Height = ");
	CloudsNBox = new QSpinBox;
	CloudsMBox = new QSpinBox;
	QComboBox *methodBox = new QComboBox;
	QLabel *methodLabel = new QLabel("Generation method: ");
	methodBox->addItem("Fourier");
	methodBox->addItem("Random Midpoint Displacement");
	
	QHBoxLayout *CloudsHurstLayout = new QHBoxLayout;
	CloudsHurstLayout->addWidget(CloudsHurstLabel);
	CloudsHurstLayout->addWidget(CloudsHurstBox);
	CloudsHurstLayout->addStretch();	
    	
	QHBoxLayout *CloudsNLayout = new QHBoxLayout;
	CloudsNLayout->addWidget(CloudsNLabel);
	CloudsNLayout->addWidget(CloudsNBox);
	CloudsNLayout->addStretch();
	
	CloudsMLayout = new QHBoxLayout;
	CloudsMLayout->addWidget(CloudsMLabel);
	CloudsMLayout->addWidget(CloudsMBox);
	CloudsMLayout->addStretch();
	CloudsHurstBox->setRange(0,1);
	CloudsHurstBox->setValue(0.7); Clouds_Hurst=0.7;
	CloudsHurstBox->setSingleStep(0.05);
	CloudsNBox->setRange(1,2049);
	CloudsNBox->setValue(513); Clouds_N=513;
	CloudsNBox->setSingleStep(10);
	CloudsMBox->setRange(1,2049);
	CloudsMBox->setValue(513); Clouds_M=513;
	CloudsMBox->setSingleStep(10);
	
	QVBoxLayout *CloudsLayout = new QVBoxLayout;
	CloudsLayout->addLayout(CloudsHurstLayout);
	CloudsLayout->addLayout(CloudsNLayout);
	CloudsLayout->addLayout(CloudsMLayout);
	CloudsLayout->addWidget(methodLabel);
	CloudsLayout->addWidget(methodBox);

	CloudsLayout->addStretch();
	setLayout(CloudsLayout);
	nubefBm = new nubes();
	Index = 0;
	
	connect(CloudsHurstBox, SIGNAL (valueChanged(double)),this, SLOT(setCloudsHurst(double)));
	connect(CloudsNBox, SIGNAL (valueChanged(int)),this, SLOT(setCloudsN(int)));
	connect(CloudsMBox, SIGNAL (valueChanged(int)),this, SLOT(setCloudsM(int)));
	connect(methodBox, SIGNAL (activated(int)),this, SLOT(setGenerateIndex(int)));
	connect(methodBox, SIGNAL (activated(int)),this, SLOT(changeBoxBehaviour(int)));
	Update();
	
	
}
void CloudsPage::changeBoxBehaviour(int caso)

{
switch(caso){
case 0:
CloudsNBox->setRange(1,2049);
CloudsNBox->setValue(513); Clouds_N=513;
CloudsNBox->setSingleStep(10);
CloudsNLabel->setText("Width = "); 
CloudsMBox->setRange(1,2049);
CloudsMBox->setValue(513); Clouds_M=513;
CloudsMBox->setSingleStep(10);
CloudsMBox->show();
CloudsMLabel->show(); 
break;
case 1:
CloudsNBox->setRange(5,11);
CloudsNBox->setValue(9); Clouds_N=9;
CloudsNBox->setSingleStep(1);
CloudsNLabel->setText("Size 2^N, N = "); 
CloudsMBox->hide();
CloudsMLabel->hide(); 
break;
}}

void CloudsPage::Update(void)
{
	nubefBm->setN((unsigned int)Clouds_N);
	nubefBm->setM((unsigned int)Clouds_M);
	nubefBm->setHurst(Clouds_Hurst);
	nubefBm->setGenerateIndex(Index);
}

