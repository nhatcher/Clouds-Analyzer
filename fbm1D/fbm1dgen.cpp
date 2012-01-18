
#include "fbm1dgen.h"
#include <vector>
#include <cmath>
#include <complex>
#include "Array.h"
#include <iostream>
#include "fftw++.h"

#define PI  3.1415926

using namespace std;

fbm1d::fbm1d() {};

void fbm1d::generar_fbm1d() 
{
	srand(time(NULL));
	unsigned int i;
	int fint; 
	double phi, modk, amp,u,fmax=-1.E15, fmin=+1.E15;
	double gamma = -2*Hurst -1;
	complex <double> I (0,1);
	int maxlevel, size;

	size_t align=sizeof(Complex); 
	Array::array1<Complex> f(N,align);

	fft1d Forward1(1,f);
	fbrown.resize(N); 
	switch(generateIndex){
		case 0:

	for (i=0; i< N; i++) {
		modk = sqrt(i*i);
		if (modk==0) amp=0;
		else amp=pow(modk, gamma/2);
		u = rand() %100;
		phi = (u/50 - 1)*PI;
		f(i) = amp*exp(I*phi);
	}

	Forward1.fft (f);
	for(i=0; i<N;i++){
		if(fmin>f(i).real()) fmin=f(i).real();
		if(fmax<f(i).real()) fmax=f(i).real();
	}

	for(i=0; i<N;i++){
		fint = (int) ((M-2)*(f(i).real() + abs(fmin))/(fmax+abs(fmin)))+1;
		fbrown[i] = fint; 
	}
		
		break;
	case 1:
	
			for(i=0; i<fbrown.size(); i++) { fbrown[i] = 0; }
			maxlevel = N;
			size = pow(2,(double) maxlevel);  
			fbrown.resize(size+1);
			fbrown2.resize(size+1);
			delta.resize(maxlevel);
			for (int i=1; i < maxlevel; i++) {
				delta[i] = pow(0.5,i*Hurst)*sqrt(1-pow(2,2*Hurst-2));
			}
			
			fbrown2[0] = 0;
			fbrown2[size] = Gauss();
			MidPointRecursion(0,size,1,maxlevel);
			double maxfbrown, minfbrown;
			maxfbrown = -10E5; 
			minfbrown = 10E5; 
			for ( int i=0; i< size;i++) {
				if(fbrown2[i]!=0) {
				if (fbrown2[i] > maxfbrown) { maxfbrown = fbrown2[i];}
				if (fbrown2[i] < minfbrown) { minfbrown = fbrown2[i];} }
			}
			for( int i=0; i< size;i++) { 	if(fbrown2[i]!=0) { fbrown2[i] = fbrown2[i] - minfbrown; }  }
			maxfbrown = maxfbrown - minfbrown;
			
			for( int i=0; i< size;i++) { 	if(fbrown2[i]!=0) { fbrown[i] = (int) (fbrown2[i]*M)/maxfbrown; } else {fbrown[i]=0;}  } 
			break;
	}
}
double fbm1d::Gauss(void)
{
	int Nrand = 4;
	int Arand = 100;
	int u; 
	double sum,gauss; 
	double GaussAdd,GaussFac;
	GaussAdd = sqrt(3*Nrand);
	GaussFac = 2*GaussAdd/(Nrand*Arand);
	
	sum = 0;
	for ( int j=1; j<=Nrand; j++){
		u = rand() %100;
		sum = sum + u;
	}
	gauss = (GaussFac*sum -GaussAdd);
	return gauss; 
	
} 
void fbm1d::MidPointRecursion(int index0, int index2, int level, int maxlevel)
{
	
	int index1 = (index0 + index2)/2;
	fbrown2[index1] = 0.5*(fbrown2[index0] + fbrown2[index2]) + delta[level]*Gauss();
	if (level < maxlevel) {
		MidPointRecursion(index0, index1,level+1, maxlevel);
		MidPointRecursion(index1, index2,level+1, maxlevel);
	}
	
}

