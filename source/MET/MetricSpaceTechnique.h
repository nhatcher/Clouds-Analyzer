#ifndef METRICSPACETECHNIQUE_H
#define METRICSPACETECHNIQUE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <vector>
#include "Fractal2D.h"
#include "Components.h"
#include "DrawWidget.h"
#include "AreaPerimeterCalculator.h"

class DrawWidget;
class AverageSpectrumWidget;
class AreaPerimeterCalculator;

class MetricSpaceTechnique: public QWidget
{
	Q_OBJECT
	public:
		MetricSpaceTechnique(QWidget *parent = 0);
		~MetricSpaceTechnique(){};
		void setImageArray(std::vector < std::vector <int> > I) {ImageArray2d = I;};
	public slots:
		void AreaVsThresholdDraw(void); 
		void DensityVsThresholdDraw(void);
		void ComponentsVsThresholdDraw(void);
		void PixelHistogramDraw(void);
		void averageSpectrum(void);
		void FilamentIndex(void);
//		void Intensity(void);
		
	private:
		DrawWidget *drawAreaVsThreshold;
		DrawWidget *drawDensityVsThreshold;
		DrawWidget *drawComponentsVsThreshold;
		DrawWidget *drawPixelHistogram;
		DrawWidget *drawFilamentIndexVsThreshold;
		AverageSpectrumWidget *AverageSpectrum;
		std::vector < std::vector <int> > ImageArray2d;

		MetricSpaceTechnique *MetricTechnique;

};

class AverageSpectrumWidget: public QWidget
{
	Q_OBJECT
	public:
		AverageSpectrumWidget(QWidget *parent = 0);
		~AverageSpectrumWidget(){};
		void setAverageText (QString s){ AverageLabel->setText(s);};
		void setImageLabel(QImage I);
		
	signals:
		//void calculateAverageSpectrum(void);

	private:
		QLabel *AverageLabel;
};
#endif
