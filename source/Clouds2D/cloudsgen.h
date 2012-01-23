#ifndef CLOUDSGEN_H
#define CLOUDSGEN_H

#include <vector>
#include <cmath>
#include <complex>
#include "Array.h"
#include "fftw++.h"

class nubes
{ 
	public:
		nubes();
		~nubes(){};
		void generar_nube (void );
        double randomAngle();
		unsigned int getN(void){ return N;}; void setN(unsigned int A){N=A;};
		unsigned int getM(void){ return M;}; void setM(unsigned int B){M=B;};
		double getHurst(void ){return Hurst;}; void setHurst(double H){Hurst=H;};
		void setGenerateIndex(int a) {GenerateIndex=a;}
		std::vector <std::vector <int> >  obtener_nube(void){return nube;};
		double f3(double Delta, int x0, int x1,int x2);
		double f4(double Delta, int x0, int x1, int x2, int x3);
		double Gauss(void); 
	private:
		std::vector <std::vector <int> > nube;
		unsigned int N;
		unsigned int M;
		double Hurst;
		int GenerateIndex;
}; 
#endif
