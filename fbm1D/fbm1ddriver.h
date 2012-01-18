
#ifndef FBM1DDRIVER_H
#define FBM1DDRIVER_H

#include <QObject>
#include <vector>
#include <QWidget>
#include <QLabel>
#include <iostream>
#include "fbm1dgen.h"

class QSpinBox;
class QComboBox;
class QHBoxLayout;

class Fbm1dPage: public QWidget
{
	Q_OBJECT
	public slots:
		void setFbm1dHurst(double H){Fbm1d_Hurst=H;};
		void setFbm1dN(int a){Fbm1d_N=a;};
		void setFbm1dM(int b){Fbm1d_M=b;};
		void setGenerateIndex(int b){GenerateIndex=b;};
		void changeBoxBehaviour(int caso);
	public:
		Fbm1dPage(QWidget *parent = 0);
		~Fbm1dPage(){};
		void setimage(void) {graphfBm->generar_fbm1d();};
		std::vector<int> getimage ( void ){return graphfBm->obtener_fbm1d();};
		void Update(void);
	private:
		double Fbm1d_Hurst;
		int Fbm1d_N;
		int Fbm1d_M;
		int GenerateIndex;
		fbm1d *graphfBm;
		QLabel *Fbm1dNLabel;
		QSpinBox *Fbm1dNBox;
		QComboBox *GenerateFbm1dBox;
};

#endif
