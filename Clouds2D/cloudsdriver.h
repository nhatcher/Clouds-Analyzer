

#ifndef CLOUDSDRIVER_H
#define CLOUDSDRIVER_H

#include <QObject>
#include <vector>
#include <QWidget>
#include <QLabel>
#include "cloudsgen.h"
#include "MetricSpaceTechnique.h"

class MetricSpaceTechnique;
class QSpinBox;
class QHBoxLayout;

class CloudsPage: public QWidget
{
	Q_OBJECT
	public slots:
		void setCloudsHurst(double H){Clouds_Hurst=H;};
		void setCloudsN(int a){Clouds_N=a;};
		void setCloudsM(int b){Clouds_M=b;};
		void setGenerateIndex(int a) {Index=a;};
		void changeBoxBehaviour(int caso);
	public:
		CloudsPage(QWidget *parent = 0);
		~CloudsPage(){};
		void setimage( void) {nubefBm->generar_nube();};
		std::vector < std::vector <int> > getimage ( void ){return nubefBm->obtener_nube();};
		void Update(void);
	
	private:
		QLabel *CloudsMLabel;
		QLabel *CloudsNLabel;
		double Clouds_Hurst;
		int Clouds_N;
		int Clouds_M;
		nubes *nubefBm;
		QSpinBox *CloudsNBox;
		QSpinBox *CloudsMBox;
		QHBoxLayout *CloudsMLayout;
		int Index;
		
};

#endif
