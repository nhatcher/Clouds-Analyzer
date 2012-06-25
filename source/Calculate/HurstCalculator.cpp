#include "HurstCalculator.h"
#include "DrawWidget.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <complex>
#include "Array.h"
#include "fftw++.h"
#include <QtGui>


#include <QObject>
#include <QWidget>
#include <QLabel>
#include <stdio.h>

#define PI 3.1415926

using namespace std;
HurstCalculator::HurstCalculator (){};
 
double HurstCalculator::HCalculator (std::vector<std::vector<int> > arrayimagen)
{
  double Hurst = 0;
  int Tmin = 10;
  int Tmax = 50;
  int t, i, j, dx, dy, ndatos, N, M,a;
  N=arrayimagen.size();
    M=arrayimagen[0].size();
  vector <double> XCoord,YCoord;
  double AverageColor, SquareSum, StandardDeviation,fmax,fmin,RescaledRange;
  for(t=Tmin; t<Tmax;t++){
    RescaledRange = 0; ndatos = 0;
    for(i=0; i<N/t;i++){
      for(j=0;j<M/t;j++){
        AverageColor = 0; SquareSum= 0; fmax = -10E5; fmin= 10E5;
        for(dx=0; dx<t; dx++){
          for(dy=0; dy<t; dy++){
          AverageColor += arrayimagen[i*t+dx][j*t+dy];
          SquareSum += arrayimagen[i*t+dx][j*t+dy]*arrayimagen[i*t+dx][j*t+dy];
          if(arrayimagen[i*t+dx][j*t+dy] > fmax) {fmax = arrayimagen[i*t+dx][j*t+dy];}
          if(arrayimagen[i*t+dx][j*t+dy] < fmin) {fmin = arrayimagen[i*t+dx][j*t+dy];}
          }
        }
        AverageColor = AverageColor/(t*t);
        StandardDeviation = sqrt(SquareSum/(t*t) - AverageColor*AverageColor);
        RescaledRange += (fmax-fmin)/StandardDeviation;
      }
    }
  RescaledRange = RescaledRange/((N*M)/(t*t));
  //cout << t << "\t"<< RescaledRange << endl;
  XCoord.push_back(log(t));
  YCoord.push_back(log(RescaledRange));
  }
  
  drawHurst = new DrawWidget();
  drawHurst->PlotLinearFit(XCoord,YCoord);
  drawHurst->setWindowTitle("Hurst Exponent");
  drawHurst->show();
  
    /*int i,j, icen,jcen, N, M;
    N=arrayimagen.size();
    M=arrayimagen[0].size();
    icen = (N-1)/2;
    jcen = (M-1)/2;
    double Xlin=0, Ylin=0, XY=0, XSqu=0;
    double Hurst, Gamma, x,y;
    size_t align=sizeof(Complex); 
    array2<Complex> f(N,M,align);
    fft2d Backward2(-1,f);  
    for (i=0; i<N ; i++){
        for(j=0; j<M; j++) {
            f(i,j).real() = arrayimagen[i][j];
        }
  
    }
  std::vector <double> XCoord;
  std::vector <double> YCoord;
  XCoord.resize(icen*jcen);
  YCoord.resize(icen*jcen);
  int k = 0; 
    Backward2.fftNormalized(f);
    for(i=0; i<=icen;i++){
        for(j=0; j<=jcen; j++){
            if(i!=0 && j!=0){
                x = log(pow((pow(static_cast<double>(i),2) + pow( static_cast<double>(j),2)),0.5));
                y=log( abs(f(i,j).real()));
        XCoord[k] = x;
        YCoord[k] = y;
                XY += y*x;
                Xlin += x;
                Ylin += y;
                XSqu += x*x;
        k++;
            }
        }
    }

    Gamma = 2*((icen*jcen*XY - Xlin*Ylin)/(icen*jcen*XSqu - Xlin*Xlin));
    Hurst = -(Gamma+2)/2;
  double SSerr,B,s, deltaM, SSxx = 0, XAverage = 0;
  B = (Ylin*XSqu - Xlin*XY)/(icen*jcen*XSqu-Xlin*Xlin);

  QString X, Y;
  X = "log(i)";
  X = "log(F(i))";
  
  
  SSerr = 0; 
  for( uint i = 0; i < XCoord.size(); i++){
    SSerr += (YCoord[i] - (Gamma/2)*XCoord[i] - B)*(YCoord[i] - (Gamma/2)*XCoord[i] - B);  
    XAverage += XCoord[i];
  }
  s = sqrt(SSerr/(XCoord.size()-2));
  XAverage = XAverage/XCoord.size(); 
  for( uint i = 0; i < XCoord.size(); i++){
    SSxx  += (XCoord[i] - XAverage)*(XCoord[i] - XAverage);  
  }
  deltaM = s/(sqrt(SSxx)); 
    
      
  QString HurstExp, DeltaHurst;
  HurstExp.setNum(Hurst);
  DeltaHurst.setNum(deltaM);
    
  HurstExp = "Hurst Exponent=" + HurstExp;
  HurstExp += " +/- " + DeltaHurst;
  
  
  drawHurst = new DrawWidget();
  drawHurst->setXAxisLabel(X);
  drawHurst->setYAxisLabel(Y);
  drawHurst->setMSTCoord(HurstExp);
  drawHurst->PlotLinearFit(XCoord,YCoord);
  drawHurst->setWindowTitle("Hurst Exponent");
  drawHurst->show(); */

    return Hurst;
}

double HurstCalculator::HCalculator (std::vector<int>  arrayimagen1d)
{
  int i;
  int N = arrayimagen1d.size();
  double x, y;
  double Xlin = 0, Ylin = 0, XY = 0, XSqu = 0;
  double Hurst, Gamma;
  size_t align = sizeof(Complex); 
  array1 <Complex> f(N,align);
  fft1d Backward1(-1,f);
  for (i=0; i<N ; i++){
    // f(i).real()
    f[i] = Complex(arrayimagen1d[i]);
  }
  Backward1.fftNormalized(f);
  std::vector <double> XCoord;
  std::vector <double> YCoord;
  XCoord.resize((N-1)/2+1);
  YCoord.resize((N-1)/2+1);
    
  for (i=1; i<=(N-1)/2;i++) {
    x = log((double) i);
    y = log(abs(f(i)));
    XCoord[i] = x;
    YCoord[i] = y;
    XY += y*x;
    Xlin += x;
    Ylin += y;
    XSqu += x*x;
  }
  double Num=(N-1)/2;
  Gamma = 2*(Num*XY - Xlin*Ylin)/(Num*XSqu - Xlin*Xlin);
  double SSerr,B,s, deltaM, SSxx = 0, XAverage = 0;
  B = (Ylin*XSqu - Xlin*XY)/(Num*XSqu-Xlin*Xlin);
  Hurst = -(Gamma+1)/2;
  QString X, Y;
  X = "log(i)";
  X = "log(F(i))";
 
  SSerr = 0; 
  for( uint i = 0; i < XCoord.size(); i++){
    SSerr += (YCoord[i] - (Gamma/2)*XCoord[i] - B)*(YCoord[i] - (Gamma/2)*XCoord[i] - B);  
    XAverage += XCoord[i];
  }
  s = sqrt(SSerr/(XCoord.size()-2));
  XAverage = XAverage/XCoord.size(); 
  for( uint i = 0; i < XCoord.size(); i++){
    SSxx  += (XCoord[i] - XAverage)*(XCoord[i] - XAverage);  
  }
  deltaM = s/(sqrt(SSxx)); 
         
  QString HurstExp, DeltaHurst;
  HurstExp.setNum(Hurst);
  DeltaHurst.setNum(deltaM);
    
  HurstExp = "Hurst Exponent = " + HurstExp;
  HurstExp += " +/- " + DeltaHurst;
  
  
  drawHurst = new DrawWidget();
  drawHurst->setXAxisLabel(X);
  drawHurst->setYAxisLabel(Y);
  drawHurst->setMSTCoord(HurstExp);
  drawHurst->Plot(XCoord,YCoord);
  drawHurst->setWindowTitle("Hurst Exponent");
  drawHurst->show();

  return Hurst;
};

 
