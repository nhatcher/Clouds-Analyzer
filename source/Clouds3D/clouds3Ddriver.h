

#ifndef CLOUDS3dDRIVER_H
#define CLOUDS3dDRIVER_H

#include <QObject>
#include <vector>
#include <QWidget>
#include <QLabel>
#include "clouds3Dgen.h"
#include "MetricSpaceTechnique.h"

class MetricSpaceTechnique;

class Clouds3DPage: public QWidget
{
	Q_OBJECT
	public slots:
		void setCloudsHurst(double H){Clouds_Hurst=H;};
		void setCloudsN(int a){Clouds_N=a;};
		void setCloudsM(int b){Clouds_M=b;};
		void setCloudsL(int c){Clouds_L=c;};
		void setZ(int a){Clouds_z=a;};
		int getZ(void){return Clouds_z;};
	public:
		Clouds3DPage(QWidget *parent = 0);
		~Clouds3DPage(){};
		void setimage( void) {nubefBm->generar_nube();};
		std::vector < std::vector <std::vector <int> > > getimage ( void ){return nubefBm->obtener_nube();};
		void project (void) {nubefBm->projection();}
		std::vector < std::vector <int> > getprojection (void) {return nubefBm->obtener_proyeccion();};
		void Update(void);
	signals:
		void zChanged(int);
	
	private:
		double Clouds_Hurst;
		int Clouds_N;
		int Clouds_M;
		int Clouds_L;
		int Clouds_z;
		nubes3D *nubefBm;
};

#endif
