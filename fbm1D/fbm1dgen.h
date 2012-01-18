#ifndef FBM1D_H
#define FBM1D_H
 
#include <vector>
#include <cmath>
#include <complex>
#include "Array.h"
#include "fftw++.h"

class fbm1d
{
	public:
		fbm1d();
		~fbm1d(){};
		void generar_fbm1d (void );
		unsigned int getN(void){ return N;}; void setN(unsigned int A){N=A;};
		unsigned int getM(void){ return M;}; void setM(unsigned int B){M=B;};
		double getHurst(void ){return Hurst;}; void setHurst(double H){Hurst=H;};
		void setGenerateMethod(int I){generateIndex=I;};
		std::vector<int> obtener_fbm1d(void){ return fbrown;};
		double Gauss(void);
		void MidPointRecursion(int index0, int index2, int level, int maxlevel); 
	
	private:
		std::vector<double> fbrown2; 
		std::vector<int> fbrown;
		std::vector<double> delta;
		unsigned int N;
		unsigned int M;
		double Hurst;
		int generateIndex;
	
}; 
#endif
