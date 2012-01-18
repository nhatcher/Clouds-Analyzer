#include "clouds3Dgen.h"
#include <vector>
#include <cmath>
#include <complex>
#include "Array.h"
#include "fftw++.h"

using namespace std;

nubes3D::nubes3D(){}

void nubes3D::generar_nube() 
{
	srand(time(NULL));
	uint a, b, c;
	double phi, modk, amp,fmax=-1.E15, fmin=+1.E15;
	double gamma = -2*Hurst - 3;
	complex <double> I (0,1);
	size_t align=sizeof(Complex); 
	Array::array3<Complex> f(N,M,L,align);
	fft3d Forward3(1,f);
	nube.resize(N); 
	for ( a = 0; a< N; a++) {
		nube[a].resize(M);
		for(b=0;b < M; b++){
			nube[a][b].resize(L);
		}
	} 
    for(a=0;a<=(N-1)/2;a++){
        for(b=0;b<=(M-1)/2;b++){
			for(c=0;c<=(L-1)/2;c++){ 
            modk = sqrt (a*a + b*b + c*c);
            if (modk==0) {amp=0;} else { amp=pow(modk, gamma/2);}
            phi = randomAngle();
            f(a,b,c)=amp*exp(I*phi); if(a!=0 && b!=0 && c!=0) f(N-a,M-b,L-c)=amp*exp(-I*phi);
            phi = randomAngle();
            if(c!=0) f(a,b,L-c)=amp*exp(I*phi);
            if (a!=0 && b!=0) f(N-a,M-b,c)=amp*exp(-I*phi); 
			phi = randomAngle();
            if(a!=0 && c!=0) f(N-a,b,L-c)=amp*exp(I*phi);
            if(b!=0) f(a,M-b,c)=amp*exp(-I*phi); 
			phi = randomAngle();
            if(a!=0) f(N-a,b,c)=amp*exp(I*phi);
            if(b!=0 && c!=0) f(a,M-b,L-c)=amp*exp(-I*phi); 
			}
        }
    }
	Forward3.fft (f);
	for(a=0; a<N;a++){
		for(b=0; b<M; b++){
			for(c=0; c<L; c++){
			if(fmin>f(a,b,c).real()) fmin=f(a,b,c).real();
			if(fmax<f(a,b,c).real()) fmax=f(a,b,c).real();
			}
		}
	}
	for (a=0; a<nube.size() ; a++){
		for(b=0;b < nube[0].size(); b++) {
			for(c=0;c < nube[0][0].size(); c++) {
			nube[a][b][c]= static_cast<int> (254*(f(a,b,c).real() + abs(fmin))/(fmax+abs(fmin))+1);
			}
		}
	}

}
void nubes3D::projection(void)
{
	unsigned int a,b,c;
	nube2d.resize(nube.size());
	for(a=0; a<nube.size() ; a++){
	nube2d[a].resize(nube[0].size()); }
	
	double max = -10E5, min = 10E5;
	for (a=0; a<nube.size() ; a++){
		for(b=0;b < nube[0].size(); b++) {
			 nube2d[a][b] = 0;
			for(c=0;c < nube[0][0].size(); c++) {
			  nube2d[a][b] += nube[a][b][c];
			}
			if (nube2d[a][b] > max) {max=nube2d[a][b];}
			if (nube2d[a][b] < min) {min=nube2d[a][b];}
		}
	}
	
	for (a=0; a<nube.size() ; a++){
		for(b=0;b < nube[0].size(); b++) {
			 nube2d[a][b] =  static_cast<int> ((5000*(nube2d[a][b] - min)/(max - min))+1);
		}
	}

}
double nubes3D::randomAngle()
{
    double u = rand() %1000;
    return (u/500 - 1)*3.1415926;
} 

