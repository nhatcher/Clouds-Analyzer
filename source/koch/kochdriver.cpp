
#include <QtGui>

#include "kochdriver.h"

KochPage::KochPage(QWidget *parent) : QWidget(parent)
{
	QRegExp rx("[UDRL]*");
	QValidator *validator = new QRegExpValidator(rx,this);
	
	QLabel *KochStarterLabel = new QLabel ("Starter = ");
	QLineEdit *KochStarterLine = new QLineEdit("RDLU");
	Koch_Starter="RDLU";
	KochStarterLine->setValidator(validator);
	
	QLabel *KochUpLabel = new QLabel ("Up = ");
	QLineEdit *KochUpLine = new QLineEdit("ULURU");
	Koch_Up="ULURU";
	KochUpLine->setValidator(validator);
	
	QLabel *KochDownLabel = new QLabel ("Down = ");
	QLineEdit *KochDownLine = new QLineEdit("DRDLD");
	Koch_Down="DRDLD";
	KochDownLine->setValidator(validator);
	
	QLabel *KochRightLabel = new QLabel ("Right = ");
	QLineEdit *KochRightLine = new QLineEdit("RURDR");
	Koch_Right="RURDR";
	KochDownLine->setValidator(validator);
	
	QLabel *KochLeftLabel = new QLabel ("Left = ");
	QLineEdit *KochLeftLine = new QLineEdit("LDLUL");
	Koch_Left="LDLUL";
	KochLeftLine->setValidator(validator);
	
	koch = new koch_fractal(); 
	QLabel *KochIterLabel = new QLabel("Iterations = ");
	QSpinBox *KochIterBox = new QSpinBox;
	KochIterBox->setValue(5);
	Koch_iter=5;
	QLabel *KochDotsLabel = new QLabel("Dots = ");
	QSpinBox *KochDotsBox = new QSpinBox;
	KochDotsBox->setValue(1);
	Koch_Dots=1;
	
	QHBoxLayout *KochIterLayout = new QHBoxLayout;
	KochIterLayout->addWidget(KochIterLabel);
	KochIterLayout->addWidget(KochIterBox);
	KochIterLayout->addStretch();
	QHBoxLayout *KochDotsLayout = new QHBoxLayout;
	KochDotsLayout->addWidget(KochDotsLabel);
	KochDotsLayout->addWidget(KochDotsBox);
	KochDotsLayout->addStretch();
	
	QHBoxLayout *KochStarterLayout = new QHBoxLayout;
	KochStarterLayout->addWidget(KochStarterLabel);
	KochStarterLayout->addWidget(KochStarterLine);
	KochStarterLayout->addStretch();
	
	QHBoxLayout *KochLeftRightLayout = new QHBoxLayout;
	KochLeftRightLayout->addWidget(KochLeftLabel);
	KochLeftRightLayout->addWidget(KochLeftLine);
	KochLeftRightLayout->addWidget(KochRightLabel);
	KochLeftRightLayout->addWidget(KochRightLine);
	KochLeftRightLayout->addStretch();
	
	QHBoxLayout *KochUpDownLayout = new QHBoxLayout;
	KochUpDownLayout->addWidget(KochUpLabel);
	KochUpDownLayout->addWidget(KochUpLine);
	KochUpDownLayout->addWidget(KochDownLabel);
	KochUpDownLayout->addWidget(KochDownLine);
	KochUpDownLayout->addStretch();
	
	QVBoxLayout *KochLayout = new QVBoxLayout;
	KochLayout->addLayout(KochIterLayout);
	KochLayout->addLayout(KochDotsLayout);
	KochLayout->addLayout(KochStarterLayout);
	KochLayout->addLayout(KochLeftRightLayout);
	KochLayout->addLayout(KochUpDownLayout);
	KochLayout->addStretch();
	setLayout(KochLayout);
	
	connect(KochStarterLine, SIGNAL (textChanged(const QString & )),this, SLOT(setKochStarter(const QString &)));
	connect(KochRightLine, SIGNAL (textChanged(const QString & )),this, SLOT(setKochRight(const QString &)));
	connect(KochDownLine, SIGNAL (textChanged(const QString & )),this, SLOT(setKochDown(const QString &)));
	connect(KochLeftLine, SIGNAL (textChanged(const QString & )),this, SLOT(setKochLeft(const QString &)));
	connect(KochUpLine, SIGNAL (textChanged(const QString & )),this, SLOT(setKochUp(const QString &)));
	connect(KochIterBox, SIGNAL (valueChanged(int)),this, SLOT(setKochIter(int)));
	connect(KochDotsBox, SIGNAL (valueChanged(int)),this, SLOT(setKochDots(int)));
	Update();
}

void KochPage::Update(void)
{
	koch->setStarter(Koch_Starter);
	koch->setUp(Koch_Up);
	koch->setDown(Koch_Down);
	koch->setRight(Koch_Right);
	koch->setLeft(Koch_Left);
	koch->itera(Koch_iter);
	koch->setDots(Koch_Dots);
}
