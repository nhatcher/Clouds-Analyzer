#include <QtGui>
#include "clouds3Dgen.h"
#include "clouds3Ddriver.h"
#include "MetricSpaceTechnique.h"

Clouds3DPage::Clouds3DPage(QWidget *parent) : QWidget(parent)
{
	QLabel *CloudsHurstLabel= new QLabel ("Hurst Exponent= ");
	QDoubleSpinBox *CloudsHurstBox = new QDoubleSpinBox;
	QLabel *CloudsNLabel = new QLabel("Width = ");
	QLabel *CloudsMLabel = new QLabel("Height = ");
	QLabel *CloudsLLabel = new QLabel("Depth = ");
	QSpinBox *CloudsNBox = new QSpinBox;
	QSpinBox *CloudsMBox = new QSpinBox;
	QSpinBox *CloudsLBox = new QSpinBox;
	QSlider *zSlider = new QSlider(Qt::Horizontal);
	zSlider->setRange(0,125);
	zSlider->setValue(64);

	QHBoxLayout *CloudsHurstLayout = new QHBoxLayout;
	CloudsHurstLayout->addWidget(CloudsHurstLabel);
	CloudsHurstLayout->addWidget(CloudsHurstBox);
	CloudsHurstLayout->addStretch();	
    	
	QHBoxLayout *CloudsNLayout = new QHBoxLayout;
	CloudsNLayout->addWidget(CloudsNLabel);
	CloudsNLayout->addWidget(CloudsNBox);
	CloudsNLayout->addStretch();
	
	QHBoxLayout *CloudsMLayout = new QHBoxLayout;
	CloudsMLayout->addWidget(CloudsMLabel);
	CloudsMLayout->addWidget(CloudsMBox);
	CloudsMLayout->addStretch();
	
	QHBoxLayout *CloudsLLayout = new QHBoxLayout;
	CloudsLLayout->addWidget(CloudsLLabel);
	CloudsLLayout->addWidget(CloudsLBox);
	CloudsLLayout->addStretch();
	
	CloudsHurstBox->setRange(0,1);
	CloudsHurstBox->setValue(0.7); Clouds_Hurst=0.7;
	CloudsHurstBox->setSingleStep(0.01);
	CloudsNBox->setRange(1,1025);
	CloudsNBox->setValue(125); Clouds_N=125;
	CloudsNBox->setSingleStep(10);
	CloudsMBox->setRange(1,1025);
	CloudsMBox->setValue(125); Clouds_M=125;
	CloudsMBox->setSingleStep(10);
	CloudsLBox->setRange(1,1025);
	CloudsLBox->setValue(125); Clouds_L=125;
	CloudsLBox->setSingleStep(10);
	Clouds_z=64;
	

	QVBoxLayout *CloudsLayout = new QVBoxLayout;
	CloudsLayout->addLayout(CloudsHurstLayout);
	CloudsLayout->addLayout(CloudsNLayout);
	CloudsLayout->addLayout(CloudsMLayout);
	CloudsLayout->addLayout(CloudsLLayout);
	CloudsLayout->addWidget(zSlider);


	CloudsLayout->addStretch();
	setLayout(CloudsLayout);
	nubefBm = new nubes3D();
	
	connect(CloudsHurstBox, SIGNAL (valueChanged(double)),this, SLOT(setCloudsHurst(double)));
	connect(CloudsNBox, SIGNAL (valueChanged(int)),this, SLOT(setCloudsN(int)));
	connect(CloudsMBox, SIGNAL (valueChanged(int)),this, SLOT(setCloudsM(int)));
	connect(CloudsLBox, SIGNAL (valueChanged(int)),this, SLOT(setCloudsL(int)));
	connect(zSlider, SIGNAL (valueChanged(int)), this, SIGNAL(zChanged(int)));
	Update();
}

void Clouds3DPage::Update(void)
{
	nubefBm->setN((uint)Clouds_N);
	nubefBm->setM((uint)Clouds_M);
	nubefBm->setL((uint)Clouds_L);
	nubefBm->setHurst(Clouds_Hurst);
}

