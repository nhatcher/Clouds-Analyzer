#include "cloudsgen.h"
#include <vector>
#include <cmath>
#include <complex>
#include "Array.h"
#include "fftw++.h"

using namespace std;
 
nubes::nubes(){}

void nubes::generar_nube() 
{
	srand(time(NULL));
	
	unsigned int a, b;
	double phi, modk, amp,fmax=-1.E15, fmin=+1.E15;
	double gamma = -2*Hurst - 2;
	complex <double> I (0,1);
	size_t align=sizeof(Complex); 
	Array::array2<Complex> f(N,M,align);
	fft2d Forward2(1,f);
	int size, maxlevel;
	
	switch(GenerateIndex) {
		case 0:
		nube.resize(N); 
		for ( a = 0; a< N; a++) {
		nube[a].resize(M);
		} 
    	for(a=0;a<=(N-1)/2;a++){
        	for(b=0;b<=(M-1)/2;b++){
            modk = sqrt (a*a + b*b);
            if (modk==0) {amp=0;} else { amp=pow(modk, gamma/2);}
            phi = randomAngle();
            f(a,b)=amp*exp(I*phi); if(a!=0 && b!=0) f(N-a,M-b)=amp*exp(-I*phi);
            phi = randomAngle();
            if(a!=0) f(N-a,b)=amp*exp(I*phi);
            if(b!=0) f(a,M-b)=amp*exp(-I*phi); 
        }
    }
	Forward2.fft (f);
	for(a=0; a<N;a++){
		for(b=0; b<M; b++){;
			if(fmin>f(a,b).real()) fmin=f(a,b).real();
			if(fmax<f(a,b).real()) fmax=f(a,b).real();
		}
	}
	for (a=0; a<nube.size() ; a++){
		for(b=0;b < nube[a].size(); b++) {
			nube[a][b]= static_cast<int> (254*(f(a,b).real() + abs(fmin))/(fmax+abs(fmin))+1);
			
		}
	}
	break; 
		case 1:
			double Delta;
			maxlevel = N;
			bool addition = true;
			size = pow(2, (double) maxlevel);
			std::vector <std::vector <double> > nubeD;
			nubeD.resize(size+1); int i,j;
			for(i=0; i <size+1; i++) {nubeD[i].resize(size+1);}
			nubeD[0][0] = Gauss(); nubeD[0][size]=Gauss(); nubeD[size][0]=Gauss(); nubeD[size][size]=Gauss();
			int D,d; D= size; d = size/2;
			int stage; Delta=1000;
			for(stage=1; stage <= maxlevel; stage++) {
				Delta = Delta * pow(0.5, 0.5*Hurst);
				for(i=d; i<=size-d; i+=D) {
					for(j=d; j<=size-d; j+=D) {
						nubeD[i][j] = f4(Delta,nubeD[i+d][j+d],nubeD[i+d][j-d], nubeD[i-d][j+d], nubeD[i-d][j-d]);
					}
				}
			
				if(addition) {
					for(i=0; i<=size; i+=D) {
						for(j=0; j<=size; j+=D) {
							nubeD[i][j] = nubeD[i][j] + Delta*Gauss();	
						}
					}	
				}
		
				Delta = Delta*pow(0.5,0.5*Hurst);
		
				for (i=d; i<=size-d; i+=D) {
					nubeD[i][0] = f3(Delta, nubeD[i+d][0], nubeD[i-d][0], nubeD[i][d]);
					nubeD[i][size] = f3(Delta, nubeD[i+d][size], nubeD[i-d][size], nubeD[i][size-d]);
					nubeD[0][i] = f3(Delta, nubeD[0][i+d], nubeD[0][i-d], nubeD[d][i]);
					nubeD[size][i] = f3(Delta, nubeD[size][i+d], nubeD[size][i-d], nubeD[size-d][i]);
				}
				for(i=d; i<=size-d; i+=D) {
					for(j=D; j<=size-d; j+=D) {
						nubeD[i][j] = f4(Delta,nubeD[i][j+d],nubeD[i][j-d], nubeD[i+d][j], nubeD[i-d][j]);
					}
				}
		
				for(i=D; i<=size-d; i+=D) {
					for(j=d; j<=size-d; j+=D) {
						nubeD[i][j] = f4(Delta,nubeD[i][j+d],nubeD[i][j-d], nubeD[i+d][j], nubeD[i-d][j]);
					}
				}
	
				if(addition) {
					for(i=0; i<=size; i+=D) {
						for(j=0; j<=size; j+=D) {
							nubeD[i][j] = nubeD[i][j] + Delta*Gauss();
						}
					}
					for(i=0; i<=size-d; i+=D) {
						for(j=0; j<=size-d; j+=D) {
							nubeD[i][j] = nubeD[i][j] + Delta*Gauss();
						}
					}
				}
		
				D= D/2;
				d= d/2;
		
			}
		
			nube.resize(size+1);
		
			for (i=0; i <=size; i++) {
				nube[i].resize(size+1); }
				double max= -10E5,min = 10E5;
				for (i=0; i <=size; i++) {
					for (j=0; j <= size; j++) {
						if(nubeD[i][j] > max) {max=nubeD[i][j];}
						if(nubeD[i][j] < min) {min=nubeD[i][j];}
					}
				}	
				max = max - min;
				for (i=0; i <=size; i++) {
					for (j=0; j <= size; j++) {
							nubeD[i][j] = nubeD[i][j] - min;
							nube[i][j] = (int) nubeD[i][j]*255/max;}
				
				}
	break;
	}

}
double nubes::randomAngle()
{
    double u = rand() %1000;
    return (u/500 - 1)*3.1415926;
} 
double nubes::Gauss(void)
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
double nubes::f3(double Delta, int x0, int x1,int x2) 
{
	return ((x0 + x1 + x2)/3 + Delta*Gauss());	
}
double nubes::f4(double Delta, int x0, int x1, int x2, int x3) 
{
	return ((x0 + x1 + x2 + x3)/4 + Delta*Gauss());	
}

