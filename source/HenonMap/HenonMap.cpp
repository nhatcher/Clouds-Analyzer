#include "HenonMap.h"
#include <QtGui>

HenonPage::HenonPage(QWidget *parent) : QWidget(parent)
{
    QLabel *bLabel = new QLabel("b=");
    QLabel *aLabel = new QLabel("a=");
    QLabel *iterLabel = new QLabel("Iteractions=");
    QLabel *magLabel = new QLabel("Zoom=");
    QLabel *ImageLabel =new QLabel;
    QImage image(":/images/HenonFormula.png");
    ImageLabel->setPixmap(QPixmap::fromImage(image));
    ImageLabel->adjustSize();
    QDoubleSpinBox *magBox =new QDoubleSpinBox;
    QDoubleSpinBox *aBox = new QDoubleSpinBox;
    QDoubleSpinBox *bBox = new QDoubleSpinBox;
    QSpinBox *iterBox = new QSpinBox;
    
    QRadioButton *ErgodicRadio = new QRadioButton("Ergodic");
    QRadioButton *NonErgodicRadio = new QRadioButton("No ergodic");
    ergodic=false;
    NonErgodicRadio->setEnabled(true);
    
    QHBoxLayout *aLayout = new QHBoxLayout;
    aLayout->addWidget(aLabel);
    aLayout->addWidget(aBox);
    aLayout->addStretch();
    
    QHBoxLayout *bLayout = new QHBoxLayout;
    bLayout->addWidget(bLabel);
    bLayout->addWidget(bBox);
    bLayout->addStretch();
    
    QVBoxLayout *abLayout = new QVBoxLayout;
    abLayout->addLayout(aLayout);
    abLayout->addLayout(bLayout);
    
    QHBoxLayout *abImageLayout = new QHBoxLayout;
    abImageLayout->addLayout(abLayout);
    abImageLayout->addWidget(ImageLabel);
    
    QHBoxLayout *iterLayout = new QHBoxLayout;
    iterLayout->addWidget(NonErgodicRadio);
    iterLayout->addWidget(iterLabel);
    iterLayout->addWidget(iterBox);
    iterLayout->addStretch();
    
    QHBoxLayout *ErgodicLayout = new QHBoxLayout;
    ErgodicLayout->addWidget(ErgodicRadio);
    //ErgodicLayout->addWidget
    
    iterBox->setRange(1,200);
    iterBox->setValue(30); Henon_iter=30;
    
    bBox->setRange(0,1);
    bBox->setValue(0.3); Henon_b=0.3;
    aBox->setRange(0,2);
    aBox->setValue(1.4); Henon_a=1.4;
    bBox->setSingleStep(0.01);
    aBox->setSingleStep(0.01);
    
    QHBoxLayout *magLayout = new QHBoxLayout;
    magLayout->addWidget(magLabel);
    magLayout->addWidget(magBox);
    magLayout->addStretch();
    magBox->setRange(0,100); magBox->setSingleStep(0.1);
    magBox->setValue(2); mag=2;
    
    
    connect(aBox, SIGNAL (valueChanged(double)),this, SLOT(setHenon_a(double)));
    connect(bBox, SIGNAL (valueChanged(double)),this, SLOT(setHenon_b(double)));
    connect(iterBox, SIGNAL (valueChanged(int)),this, SLOT(setHenon_iter(int)));
    connect(magBox, SIGNAL (valueChanged(double)),this, SLOT(setmag(double)));
    
    QVBoxLayout *HenonLayout = new QVBoxLayout;
    HenonLayout->addLayout(abImageLayout);
    HenonLayout->addLayout(iterLayout);
    HenonLayout->addLayout(ErgodicLayout);
    HenonLayout->addLayout(magLayout);
    HenonLayout->addStretch();
    setLayout(HenonLayout);
}

void HenonPage::generate()
{
    int i, j;
    long int k;
    int ip,jp;
    double x,y,xp,yp;
    int N=300*mag;
    int M=80*mag;
    image.resize(N+1);
    for(i=0;i<N+1;i++){
        image[i].resize(M+1);
        for(j=0;j<M+1;j++){
            image[i][j]=1;
        }
    }
    if(!ergodic){
        for(i=0;i<=N;i++){
            for(j=0;j<=M;j++){
                x=static_cast<double>(i)/(mag*100.0)-1.5; y=static_cast<double>(j)/(mag*100)-0.40;
                for(k=0;k<Henon_iter;k++){
                    xp=1+y-Henon_a*x*x;
                    yp=Henon_b*x;
                    x=xp; y=yp;
                }
                ip=static_cast<int>((x+1.5)*100.0*mag);
                jp=static_cast<int>((y+0.4)*100.0*mag);
                if(ip<=N && jp<=M && jp>=0 && ip>=0) image[ip][jp]=0;
            }
        }
    }else{
        x=0; y=0;
        for(k=0;k<120;k++){
            xp=1+y-Henon_a*x*x;
            yp=Henon_b*x;
            x=xp; y=yp;
        }
        for(k=0;k<1600000;k++){
            xp=1+y-Henon_a*x*x;
            yp=Henon_b*x;
            x=xp; y=yp;
            ip=static_cast<int>((x+1.5)*100.0*mag);
            jp=static_cast<int>((y+0.4)*100.0*mag);
            image[ip][jp]=0;
        }
    }
}



