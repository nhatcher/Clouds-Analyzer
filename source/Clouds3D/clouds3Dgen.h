#ifndef CLOUDS3dGEN_H
#define CLOUDS3dGEN_H

#include <vector>
#include <cmath>
#include <complex>
#include "Array.h"
#include "fftw++.h"

class nubes3D
{
	public:
		nubes3D();
		~nubes3D(){};
		void generar_nube (void );
        double randomAngle();
		unsigned int getN(void){ return N;}; void setN(unsigned int A){N=A;};
		unsigned int getM(void){ return M;}; void setM(unsigned int B){M=B;};
		unsigned int getL(void){ return L;}; void setL(unsigned int C){L=C;};
		double getHurst(void ){return Hurst;}; void setHurst(double H){Hurst=H;};
		std::vector <std::vector <std::vector <int> > >  obtener_nube(void){return nube;};
		std::vector <std::vector  <int> > obtener_proyeccion(void) {return nube2d;};
		void projection(void);
	private:
		std::vector <std::vector <std::vector <int> > > nube;
		std::vector <std::vector <int> > nube2d;
		unsigned int N;
		unsigned int M;
		unsigned int L;
		double Hurst;
}; 
#endif
