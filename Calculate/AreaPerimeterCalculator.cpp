#include "AreaPerimeterCalculator.h"
#include "DrawWidget.h"

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

AreaPerimeterCalculator::AreaPerimeterCalculator (){};

double AreaPerimeterCalculator::APCalculator (std::vector<std::vector<int> > CloudArray)
{
    int NobjTotal = 0; 
    int InfiniteAreaTotal = 0;
    int threshold;
    int i,j,a,b,k,ap;
    bool notFinished;
    std::vector <int> stackX; 
    std::vector <int> stackY;
    std::vector <int> AreaObj;
    int nobj=0;
    std::vector<int>  Edge;
    std::vector<bool> PossibleInfiniteArea;
    int imax = CloudArray.size();
    int jmax = CloudArray[0].size();
    double XY,Xlin,Ylin,XSqu; 
      XY=0; Xlin=0; Ylin=0; XSqu=0;
      unsigned int npix;
      std::vector <double> XCoord;
      std::vector <double> YCoord;
 
    

    std::vector<std::vector<int> > ComponentsVector;
    ComponentsVector.resize(imax);
	
    for(i = 0; i != imax;++i) {
	ComponentsVector[i].resize(jmax); }
    
    //Hallo el numero de componentes y sus areas.

    for (threshold=MinimumThreshold; threshold <= MaximumThreshold; threshold+=Step){
			nobj = 0;
			for(i = 0; i != imax ;++i) {
				for(j = 0; j != jmax; ++j) {
					ComponentsVector[i][j]=0;
					if(CloudArray[i][j] >= threshold) {ComponentsVector[i][j]=-1;}
				}		
			}
			
	
    int maxY,maxX;
    for(i=0;i<imax;i++){
        for(j=0;j<jmax;j++){
            if(ComponentsVector[i][j]==-1){
                AreaObj.push_back(0);
                nobj++;
                a=i; b=j;
                maxX =a; maxY=b;
                stackX.push_back(a); stackY.push_back(b);
                notFinished=true;
                while(notFinished){
                    ComponentsVector[sum(a,imax)][sum(b,jmax)]=nobj;
                    if(ComponentsVector[sum(a+1,imax)][sum(b,jmax)]==-1){
                        a++;//a=sum(a+1,imax);
                        if (maxX < a) {maxX=a;}
                        stackX.push_back(a); stackY.push_back(b);
                    } else { 
                        if(ComponentsVector[sum(a+1,imax)][sum(b+1,jmax)]==-1){
                            a++; b++;//a=sum(a+1,imax); b=sum(b+1,jmax); 
                            if (maxX < a) {maxX=a;}
                            if (maxY < b) {maxY=b;}
                            stackX.push_back(a); stackY.push_back(b);
                        }else {
                            if(ComponentsVector[sum(a,imax)][sum(b+1,jmax)]==-1){
                                b++;//b=sum(b+1,jmax);
                                if (maxY < b) {maxY=b;}
                                stackX.push_back(a); stackY.push_back(b);
                            } else{
                                if(ComponentsVector[sum(a-1,imax)][sum(b+1,jmax)]==-1){
                                    a--;b++;//a=sum(a-1,imax); b=sum(b+1,jmax);
                                    if (maxY < b) {maxY=b;}
                                    stackX.push_back(a); stackY.push_back(b);
                                }else{
                                    if(ComponentsVector[sum(a-1,imax)][sum(b,jmax)]==-1){
                                        a--;//a=sum(a-1,imax);
                                        stackX.push_back(a); stackY.push_back(b);
                                    }else{
                                        if(ComponentsVector[sum(a-1,imax)][sum(b-1,jmax)]==-1){
                                            a--;b--;//a=sum(a-1,imax); b=sum(b-1,jmax);
                                            stackX.push_back(a); stackY.push_back(b);
                                        }else {
                                            if(ComponentsVector[sum(a,imax)][sum(b-1,jmax)]==-1){
                                                b--;//b=sum(b-1,jmax);
                                                stackX.push_back(a); stackY.push_back(b);
                                            }else{
                                                if(ComponentsVector[sum(a+1,imax)][sum(b-1,jmax)]==-1){
                                                    a++;b--;//a=sum(a+1,imax); b=sum(b-1,jmax);
                                                    stackX.push_back(a); stackY.push_back(b);
                                                } else {
                                                    if(sum(a,imax)==i && sum(b,jmax)==j) {
                                                        notFinished=false;
                                                        if ( abs(maxX - a) >= imax-1 || abs(maxY - b) >= jmax-1 ) {PossibleInfiniteArea.push_back(true);}
                                                        else {PossibleInfiniteArea.push_back(false);}
                                                        
                                                    } else {
                                                        stackX.pop_back(); stackY.pop_back();
                                                        a=stackX.back(); b=stackY.back();
                                                    };
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                };
            }
        }
    }
    
    
    bool perimeter;
    Edge.resize(nobj);
    for (k=1; k<= nobj; k++){
        Edge[k-1]=0;
        AreaObj[k-1]=0;
        perimeter = false;
        for(i=0;i<imax;i++){
            for(j=0;j<jmax;j++){
                
                if(ComponentsVector[i][j]==k){
                    AreaObj[k-1]++;
                    for(a=-1;a<2; a++){
                        for(ap=-1;ap<2;ap++){
                            if (ComponentsVector[sum(i+a,imax)][sum(j+ap,jmax)]==0) { perimeter =true;}
                            
                        }
                    }
                }
                if (perimeter==true){Edge[k-1]++;}
                perimeter = false;
            }
        }
    }
    
    
    int perimeterLength =0;  

    
    std::vector <bool> InfiniteArea;
    InfiniteArea.resize(nobj+1);
    for(k=1;k<=nobj;k++){ InfiniteArea[k] = false; }
    
    int nobjk;
    
    for(k=1;k<=nobj;k++){
        nobjk=0;
        if(PossibleInfiniteArea[k-1]==true){
            
            for(i=0;i<imax;i++){
                for(j=0;j<jmax;j++){
                    if(ComponentsVector[i][j]==k){
                        nobjk++;
                        a=i; b=j;
                        stackX.push_back(a); stackY.push_back(b);
                        notFinished=true;
                        while(notFinished){
                            ComponentsVector[a][b]=-nobjk;
                            if( a < imax-1 && ComponentsVector[a+1][b]==k){
                                a++;//a=sum(a+1,imax);
                                stackX.push_back(a); stackY.push_back(b);
                            } else { 
                                if( a < imax-1 && b < jmax-1 && ComponentsVector[a+1][b+1]==k){
                                    a++; b++;//a=sum(a+1,imax); b=sum(b+1,jmax);
                                    stackX.push_back(a); stackY.push_back(b);
                                }else {
                                    if( b < jmax-1 && ComponentsVector[a][b+1]==k){
                                        b++;//b=sum(b+1,jmax);
                                        stackX.push_back(a); stackY.push_back(b);
                                    } else{
                                        if( a > 0 && b <jmax-1 && ComponentsVector[a-1][b+1]==k){
                                            a--;b++;//a=sum(a-1,imax); b=sum(b+1,jmax);
                                            stackX.push_back(a); stackY.push_back(b);
                                        }else{
                                            if( a > 0 && ComponentsVector[a-1][b]==k){
                                                a--;//a=sum(a-1,imax);
                                                stackX.push_back(a); stackY.push_back(b);
                                            }else{
                                                if( a > 0 && b > 0 && ComponentsVector[a-1][b-1]==k){
                                                    a--;b--;//a=sum(a-1,imax); b=sum(b-1,jmax);
                                                    stackX.push_back(a); stackY.push_back(b);
                                                }else {
                                                    if( b > 0 && ComponentsVector[a][b-1]==k){
                                                        b--;//b=sum(b-1,jmax);
                                                        stackX.push_back(a); stackY.push_back(b);
                                                    }else{
                                                        if( a < imax-1 && b > 0 && ComponentsVector[a+1][b-1]==k){
                                                            a++; b--;//a=sum(a+1,imax); b=sum(b-1,jmax);
                                                            stackX.push_back(a); stackY.push_back(b);
                                                        } else {
                                                            
                                                            if(a==i && b==j) {
                                                                notFinished=false;
                                                            } else {
                                                                stackX.pop_back(); stackY.pop_back();
                                                                a=stackX.back(); b=stackY.back();
                                                                
                                                            };
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    };
                }
            }
            
            for( int z = 1; z <=nobjk ; z++){
                for(i=0;i<imax;i++){
                    if( ComponentsVector[i][0]==-z && ComponentsVector[i][jmax-1]==-z) { InfiniteArea[k]=true;} }
                    for(j=0;j<jmax;j++){
                        if( ComponentsVector[0][j]==-z && ComponentsVector[imax-1][j]==-z) { InfiniteArea[k]=true;} }
            }
            
            for(i=0;i<imax;i++){
                for(j=0;j<jmax;j++){
                    if(ComponentsVector[i][j]<0) { ComponentsVector[i][j] = k; }
                }
            }
        }
    }
    int NumberInfiniteArea = 0;
			for (k=1;k<=nobj;k++){
				if(InfiniteArea[k]==true) { NumberInfiniteArea++; } }
		
				for(k=1;k<=nobj;k++) {
					npix=AreaObj[k-1];
					perimeterLength = Edge[k-1];
	
					if (npix >= MinimumSize && InfiniteArea[k]==false) {
	
						XCoord.push_back(log(npix));
						YCoord.push_back(log(perimeterLength));
	
						XY += log(perimeterLength)*log(npix);
						Ylin += log(perimeterLength);
						Xlin += log(npix);
						XSqu += log(npix)*log(npix);
					}
				}
				InfiniteAreaTotal += NumberInfiniteArea;
				NobjTotal += nobj;
		}
    
        
	double  Dper;
		
	Dper = ((XCoord.size())*XY - Xlin*Ylin)/((XCoord.size())*XSqu-Xlin*Xlin);
	
        QString Ndatos;
        QString TotalComponents;
        QString InfiniteAreaString;
        
        TotalComponents.setNum(nobj);
        TotalComponents = "Total Components= " + TotalComponents; 
        
        
        //InfiniteAreaString.setNum(NumberInfiniteArea);
        //InfiniteAreaString = "Number Infinite Area = " + InfiniteAreaString;
        QString MinimumSizeString;
        MinimumSizeString.setNum(MinimumSize);
        MinimumSizeString = "Minimum Component Size = " + MinimumSizeString;
        
        Ndatos.setNum(XCoord.size());
        Ndatos = "Ndatos=" + Ndatos;
        
        double SSerr, M,B,s, deltaM, SSxx = 0, XAverage = 0;
        
        M = ((XCoord.size())*XY - Xlin*Ylin)/((XCoord.size())*XSqu-Xlin*Xlin);
        B = (Ylin*XSqu - Xlin*XY)/((XCoord.size())*XSqu-Xlin*Xlin);
        
        SSerr = 0; 
        for( uint i = 0; i < XCoord.size(); i++){
            SSerr += (YCoord[i] - (M)*XCoord[i] - B)*(YCoord[i] - (M)*XCoord[i] - B);	
            XAverage += XCoord[i];
        }
        s = sqrt(SSerr/(XCoord.size()-2));
        XAverage = XAverage/XCoord.size(); 
        for( uint i = 0; i < XCoord.size(); i++){
            SSxx  += (XCoord[i] - XAverage)*(XCoord[i] - XAverage);	
        }
        deltaM = s/(sqrt(SSxx)); 
        
        
        QString PerimeterDim, DeltaPerimeterDim;
        PerimeterDim.setNum(2*Dper);
        DeltaPerimeterDim.setNum(2*deltaM);
        
        PerimeterDim = "Perimeter Dimension=" +PerimeterDim;
        //PerimeterDim += " +/- " + DeltaPerimeterDim;
        QString X = "log(area)";
        QString Y = "log(perimeter)";
        drawAreaPerimeterVsThreshold = new  DrawWidget();
        drawAreaPerimeterVsThreshold->setMSTCoord(PerimeterDim);
        drawAreaPerimeterVsThreshold->setXAxisLabel(X);
        drawAreaPerimeterVsThreshold->setYAxisLabel(Y);
        //drawAreaPerimeterVsThreshold->setAditionalText(TotalComponents);
        drawAreaPerimeterVsThreshold->setAditionalText2(MinimumSizeString);
        //drawAreaPerimeterVsThreshold->setAditionalText3(Ndatos);
       // drawAreaPerimeterVsThreshold->setAditionalText4(InfiniteAreaString);
        drawAreaPerimeterVsThreshold->PlotLinearFit(XCoord,YCoord);
        drawAreaPerimeterVsThreshold->setWindowTitle("Area-Perimeter Dimension");
        drawAreaPerimeterVsThreshold->show();
        return 2*Dper;

}

int AreaPerimeterCalculator::sum(int i, int max)
{
    if(i<0) return sum(i+max,max);
    if(i>=max) return sum(i-max,max);
    return i;
};

double AreaPerimeterCalculator::AverageFilamentIndex(std::vector<std::vector<int> > ComponentsVector)
{
    MinimumSize = 1;
    int imax = ComponentsVector.size();
    int jmax = ComponentsVector[0].size();
    
    int i,j,a,b,k;
    bool notFinished; 
    std::vector <int> stackX; 
    std::vector <int> stackY;
    std::vector <int> AreaObj;
    std::vector <double> ComponentsDiameter;
    int nobj=0;
    std::vector<bool> PossibleInfiniteArea;
    int maxA, minA, maxB,minB;
    double d;
    for(i=0;i<imax;i++){
        for(j=0;j<jmax;j++){
            if(ComponentsVector[i][j]==-1){
                AreaObj.push_back(1);
                nobj++;
                a=i; b=j;
                maxA =a; maxB=b; minA=a; minB=b;
                stackX.push_back(a); stackY.push_back(b);
                notFinished=true;
                while(notFinished){
                    ComponentsVector[sum(a,imax)][sum(b,jmax)]=nobj;
                    if(ComponentsVector[sum(a+1,imax)][sum(b,jmax)]==-1){
                        a++;//a=sum(a+1,imax);
                        if (maxA < a) {maxA=a;}
                        AreaObj[nobj-1]++;
                        stackX.push_back(a); stackY.push_back(b);
                    } else { 
                        if(ComponentsVector[sum(a+1,imax)][sum(b+1,jmax)]==-1){
                            a++; b++;//a=sum(a+1,imax); b=sum(b+1,jmax);
                            stackX.push_back(a); stackY.push_back(b);
                            if (maxA < a) {maxA=a;}
                            if (maxB < b) {maxB=b;}
                            AreaObj[nobj-1]++;
                        }else {
                            if(ComponentsVector[sum(a,imax)][sum(b+1,jmax)]==-1){
                                b++;//b=sum(b+1,jmax);
                                stackX.push_back(a); stackY.push_back(b);
                                if (maxB < b) {maxB=b;}
                                AreaObj[nobj-1]++;
                            } else{
                                if(ComponentsVector[sum(a-1,imax)][sum(b+1,jmax)]==-1){
                                    a--;b++;//a=sum(a-1,imax); b=sum(b+1,jmax);
                                    stackX.push_back(a); stackY.push_back(b);
                                    if (maxB < b) {maxB=b;}
                                    if (minA > a) {minA=a;}
                                    AreaObj[nobj-1]++;
                                }else{
                                    if(ComponentsVector[sum(a-1,imax)][sum(b,jmax)]==-1){
                                        a--;//a=sum(a-1,imax);
                                        if (minA > a) {minA=a;}
                                        stackX.push_back(a); stackY.push_back(b);
                                        AreaObj[nobj-1]++;
                                    }else{
                                        if(ComponentsVector[sum(a-1,imax)][sum(b-1,jmax)]==-1){
                                            a--;b--;//a=sum(a-1,imax); b=sum(b-1,jmax);
                                            if (minA > a) {minA=a;}; if(minB > b) {minB=b;}
                                            stackX.push_back(a); stackY.push_back(b);
                                            AreaObj[nobj-1]++;
                                        }else {
                                            if(ComponentsVector[sum(a,imax)][sum(b-1,jmax)]==-1){
                                                b--;//b=sum(b-1,jmax);
                                                if(minB > b) {minB=b;}
                                                stackX.push_back(a); stackY.push_back(b);
                                                AreaObj[nobj-1]++;
                                            }else{
                                                if(ComponentsVector[sum(a+1,imax)][sum(b-1,jmax)]==-1){
                                                    a++;b--;//a=sum(a+1,imax); b=sum(b-1,jmax);
                                                    if(minB > b) {minB=b;} 
                                                    if(maxA < a) {maxA=a;}
                                                    stackX.push_back(a); stackY.push_back(b);
                                                    AreaObj[nobj-1]++;
                                                    
                                                } else {
                                                    if(sum(a,imax)==i && sum(b,jmax)==j) {
                                                        notFinished=false;
                                                        if ( abs(maxA - a) >= imax-1 || abs(maxB - b) >= jmax-1 )
                                                        {PossibleInfiniteArea.push_back(true);}
                                                        else {PossibleInfiniteArea.push_back(false);}
                                                        d = sqrt((maxA-minA+1)*(maxA-minA+1)+(maxB-minB+1)*(maxB-minB+1));
                                                        ComponentsDiameter.push_back(d);
                                                        
                                                    } else {
                                                        stackX.pop_back(); stackY.pop_back();
                                                        a=stackX.back(); b=stackY.back();
                                                    };
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                };
            }
        }
    }
    
    
    
    std::vector <bool> InfiniteArea;
    InfiniteArea.resize(nobj+1);
    for(k=1;k<=nobj;k++){ InfiniteArea[k] = false; }
    
    int nobjk;
    
    for(k=1;k<=nobj;k++){
        nobjk=0;
        if(PossibleInfiniteArea[k-1]==true){
            
            for(i=0;i<imax;i++){
                for(j=0;j<jmax;j++){
                    if(ComponentsVector[i][j]==k){
                        nobjk++;
                        a=i; b=j;
                        stackX.push_back(a); stackY.push_back(b);
                        notFinished=true;
                        while(notFinished){
                            ComponentsVector[a][b]=-nobjk;
                            if( a < imax-1 && ComponentsVector[a+1][b]==k){
                                a++;//a=sum(a+1,imax);
                                stackX.push_back(a); stackY.push_back(b);
                            } else { 
                                if( a < imax-1 && b < jmax-1 && ComponentsVector[a+1][b+1]==k){
                                    a++; b++;//a=sum(a+1,imax); b=sum(b+1,jmax);
                                    stackX.push_back(a); stackY.push_back(b);
                                }else {
                                    if( b < jmax-1 && ComponentsVector[a][b+1]==k){
                                        b++;//b=sum(b+1,jmax);
                                        stackX.push_back(a); stackY.push_back(b);
                                    } else{
                                        if( a > 0 && b <jmax-1 && ComponentsVector[a-1][b+1]==k){
                                            a--;b++;//a=sum(a-1,imax); b=sum(b+1,jmax);
                                            stackX.push_back(a); stackY.push_back(b);
                                        }else{
                                            if( a > 0 && ComponentsVector[a-1][b]==k){
                                                a--;//a=sum(a-1,imax);
                                                stackX.push_back(a); stackY.push_back(b);
                                            }else{
                                                if( a > 0 && b > 0 && ComponentsVector[a-1][b-1]==k){
                                                    a--;b--;//a=sum(a-1,imax); b=sum(b-1,jmax);
                                                    stackX.push_back(a); stackY.push_back(b);
                                                }else {
                                                    if( b > 0 && ComponentsVector[a][b-1]==k){
                                                        b--;//b=sum(b-1,jmax);
                                                        stackX.push_back(a); stackY.push_back(b);
                                                    }else{
                                                        if( a < imax-1 && b > 0 && ComponentsVector[a+1][b-1]==k){
                                                            a++; b--;//a=sum(a+1,imax); b=sum(b-1,jmax);
                                                            stackX.push_back(a); stackY.push_back(b);
                                                        } else {
                                                            
                                                            if(a==i && b==j) {
                                                                notFinished=false;
                                                            } else {
                                                                stackX.pop_back(); stackY.pop_back();
                                                                a=stackX.back(); b=stackY.back();
                                                                
                                                            };
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    };
                }
            }
            
            for( int z = 1; z <=nobjk ; z++){
                for(i=0;i<imax;i++){
                    if( ComponentsVector[i][0]==-z && ComponentsVector[i][jmax-1]==-z) { InfiniteArea[k]=true;} }
                    for(j=0;j<jmax;j++){
                        if( ComponentsVector[0][j]==-z && ComponentsVector[imax-1][j]==-z) { InfiniteArea[k]=true;} }
            }
            
            for(i=0;i<imax;i++){
                for(j=0;j<jmax;j++){
                    if(ComponentsVector[i][j]<0) { ComponentsVector[i][j] = k; }
                }
            }
        }
    }
    
    
    double Index =0;
    double diameter;
    double AverageIndex;
    int ndatos = 0;
    uint npix;
    for(k=1;k<=nobj;k++) {
        npix=AreaObj[k-1];
        diameter = ComponentsDiameter[k-1];
        
        if (npix >= MinimumSize && InfiniteArea[k]==false) {
            
            Index += (3.1415926*diameter*diameter)/(4*npix);
            ndatos++;
        }
    }
    
    
    if(ndatos!=0) {AverageIndex = Index/ndatos;}
    else {AverageIndex = 0;}
    
    return AverageIndex;
}


CalculateAreaPerimeterOptions::CalculateAreaPerimeterOptions(uint Min, uint MinThr, uint MaxThr, uint Steps, QWidget *parent) : QDialog(parent)
{
    minSize = Min;
    MinimumThreshold = MinThr;
    MaximumThreshold = MaxThr;
    NumberOfSteps = Steps;
    QSpinBox *MinimumSizeBox = new QSpinBox; 
    QSpinBox *MinimumThresholdBox = new QSpinBox;
    QSpinBox *MaximumThresholdBox = new QSpinBox;
    QSpinBox *NumberOfStepsBox = new QSpinBox;
    
    QLabel *MinimumSizeLabel = new QLabel;
    QLabel *MinimumThresholdLabel = new QLabel;
    QLabel *MaximumThresholdLabel = new QLabel;
    QLabel *NumberOfStepsLabel = new QLabel;
    
    MinimumSizeLabel->setText("Minimum Component's Size=");
    MinimumThresholdLabel->setText("Minimum Threshold Value=");
    MaximumThresholdLabel->setText("Maximum Threshold Value=");
    NumberOfStepsLabel->setText("Step=");
    MinimumSizeBox->setRange(1,1000);
    MinimumSizeBox->setSingleStep(10);
    MinimumSizeBox->setValue(Min);
    MinimumThresholdBox->setRange(1,255);
    MaximumThresholdBox->setRange(1,255);
    MaximumThresholdBox->setValue(MaxThr);
    MinimumThresholdBox->setValue(MinThr);
    NumberOfStepsBox->setValue(Steps);
    MinimumThresholdBox->setSingleStep(10);
    MaximumThresholdBox->setSingleStep(10);
    
    
    QPushButton *OKButton = new QPushButton(tr("&OK"));
    QPushButton *cancelButton = new QPushButton(tr("&Cancel"));
    
    QHBoxLayout *MinimumSizeLayout = new QHBoxLayout;
    MinimumSizeLayout->addWidget(MinimumSizeLabel);
    MinimumSizeLayout->addWidget(MinimumSizeBox);
    MinimumSizeLayout->addStretch();
    
    
    QHBoxLayout *MinimumThresholdLayout = new QHBoxLayout;
    MinimumThresholdLayout->addWidget(MinimumThresholdLabel);
    MinimumThresholdLayout->addWidget(MinimumThresholdBox);
    MinimumThresholdLayout->addStretch();
    
    
    QHBoxLayout *MaximumThresholdLayout = new QHBoxLayout;
    MaximumThresholdLayout->addWidget(MaximumThresholdLabel);
    MaximumThresholdLayout->addWidget(MaximumThresholdBox);
    MaximumThresholdLayout->addStretch();
    
    QHBoxLayout *NumberOfStepsLayout = new QHBoxLayout;
    NumberOfStepsLayout->addWidget(NumberOfStepsLabel);
    NumberOfStepsLayout->addWidget(NumberOfStepsBox);
    NumberOfStepsLayout->addStretch();
    
    QHBoxLayout *ButtonsLayout = new QHBoxLayout;
    ButtonsLayout->addWidget(OKButton);
    ButtonsLayout->addWidget(cancelButton);
    
    QVBoxLayout *Layout = new QVBoxLayout;
    Layout->addLayout(MinimumSizeLayout);
    Layout->addLayout(MinimumThresholdLayout);
    Layout->addLayout(MaximumThresholdLayout);
    Layout->addLayout(NumberOfStepsLayout);
    Layout->addLayout(ButtonsLayout);
    
    setLayout(Layout);
    connect(MinimumSizeBox, SIGNAL (valueChanged(int)), this, SLOT(setMinSize(int)));
    connect(MinimumSizeBox, SIGNAL (valueChanged(int)), MinimumSizeBox, SLOT(setValue(int)));
    connect(MinimumThresholdBox, SIGNAL (valueChanged(int)), this, SLOT(setMinimumThreshold(int)));
    connect(MaximumThresholdBox, SIGNAL (valueChanged(int)), this, SLOT(setMaximumThreshold(int)));
    connect(NumberOfStepsBox, SIGNAL (valueChanged(int)), this, SLOT(setNumberOfSteps(int)));
    connect(OKButton, SIGNAL (clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL (clicked()), this, SLOT(reject()));
    setWindowTitle("Area Perimeter Settings");
    setWindowIcon(QIcon(":/images/calculateAreaPerimeterIcon.png"));
    
    show();
};

CalculateAreaPerimeterWidget::CalculateAreaPerimeterWidget(QWidget *parent): QWidget(parent)
{
    MinimumSize = 50; 
    MinimumThreshold = 50;
    MaximumThreshold = 200;
    NumberOfSteps = 10;
    
};
