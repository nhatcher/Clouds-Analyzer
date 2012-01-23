#include "MetricSpaceTechnique.h"
#include "DrawWidget.h"
#include "AreaPerimeterCalculator.h"
#include <QtGui>
#include <iostream>

using namespace std;

MetricSpaceTechnique::MetricSpaceTechnique(QWidget *parent): QWidget(parent) 
{
	QLabel *MSTLabel = new QLabel(tr("<center><font color = DarkBlue> METRIC SPACE TECHNIQUE"));
	QPushButton *DensityVsThresholdButton = new QPushButton(tr("Distribution of Density"));
	QPushButton *AreaVsThresholdButton = new QPushButton(tr("Distribution of Volume"));
	QPushButton *ComponentsVsThresholdButton = new QPushButton(tr("Distribution of Topological Components"));
	QPushButton *FilamentIndexButton = new QPushButton(tr("Distribution of Filaments"));
	QPushButton *PixelHistogramButton = new QPushButton(tr("Distribution of Pixel Values"));
	
	QPushButton *AverageSpectrumButton = new QPushButton(tr("AverageSpectrum"));
	
	connect(AreaVsThresholdButton, SIGNAL(clicked()),this, SLOT(AreaVsThresholdDraw()));
	connect(DensityVsThresholdButton, SIGNAL(clicked()),this, SLOT(DensityVsThresholdDraw()));
	connect(ComponentsVsThresholdButton, SIGNAL(clicked()),this, SLOT(ComponentsVsThresholdDraw()));
	connect(PixelHistogramButton,SIGNAL(clicked()), this,SLOT(PixelHistogramDraw()));
	connect(AverageSpectrumButton,SIGNAL(clicked()), this,SLOT(averageSpectrum()));
	connect(FilamentIndexButton,SIGNAL(clicked()), this,SLOT(FilamentIndex()));
	
	AverageSpectrum = new AverageSpectrumWidget;
	
	
	
	QVBoxLayout *MSTLayout = new QVBoxLayout;
	MSTLayout->addWidget(MSTLabel);
	
	MSTLayout->addWidget(DensityVsThresholdButton);
	MSTLayout->addWidget(AreaVsThresholdButton);
	MSTLayout->addWidget(ComponentsVsThresholdButton);
	MSTLayout->addWidget(FilamentIndexButton);
	MSTLayout->addWidget(PixelHistogramButton);
	MSTLayout->addWidget(AverageSpectrumButton);

	MSTLayout->addStretch();
	setLayout(MSTLayout);
	
};

void MetricSpaceTechnique::AreaVsThresholdDraw(void) 
{

	if( !ImageArray2d.empty() ){
	QString X,Y;
	X = "Threshold";
	Y = "Volume";
	
	unsigned int N=ImageArray2d.size();
	unsigned int M=ImageArray2d[0].size();
	std::vector <double> XCoord;
	std::vector <double> YCoord;
	int t;
	unsigned int i,j;
	XCoord.resize(256);
	YCoord.resize(256);
	for(t=0; t<256; t++){
		XCoord[t]=t;
		YCoord[t]=0;
		for(i=0; i<N; i++){
			for(j=0; j<M; j++){
				if(ImageArray2d[i][j]>t) YCoord[t]++;
			}
		} 
		YCoord[t] = YCoord[t]/(N*M); 
	}
	std::vector <double> F;
	F.resize(256);
	unsigned int sigma,xx;
	double area; 
	double minarea; 
	minarea = 10E10;
	for (sigma=0; sigma<255; sigma++) {
		for (xx=0; xx<255; xx++){
			if (xx<=sigma) {
				F[xx] = 1;}
				if (xx>sigma) {
					F[xx] = 0;}	
		}
			
		area = 0;
		for (t = 0; t< 255; t++) {
			area += abs(YCoord[t] - F[t]); 			
		}
		if (area < minarea) {minarea = area;}
	}
	QString Area;
	Area.setNum(minarea);
	Area = "Volume Distribution=" +Area;
	
	drawAreaVsThreshold = new  DrawWidget();
	drawAreaVsThreshold->setMSTCoord(Area);
	drawAreaVsThreshold->setXAxisLabel(X);
	drawAreaVsThreshold->setYAxisLabel(Y);
	drawAreaVsThreshold->Plot(XCoord,YCoord);
	drawAreaVsThreshold->setWindowTitle(tr("Volume Distribution versus Threshold"));
	drawAreaVsThreshold->show(); }

	else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}

};

void MetricSpaceTechnique::DensityVsThresholdDraw(void) 
{
	if( !ImageArray2d.empty() ){
	QString X,Y;
	X = "Threshold";
	Y = "Density";
	
	unsigned int N=ImageArray2d.size();
	unsigned int M=ImageArray2d[0].size();
	std::vector <double> XCoord;
	std::vector <double> YCoord;
	double TotalColor;
	int t;
	unsigned int i,j;
	XCoord.resize(256);
	YCoord.resize(256);
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			TotalColor +=ImageArray2d[i][j];
		}
	}
	QProgressDialog thresholdInProgress(this);
	thresholdInProgress.setRange(0,256);
	thresholdInProgress.setModal(true);
	
	for(t=0; t<256; t++){

		XCoord[t]=t;
		YCoord[t]=0;
		for(i=0; i<N; i++){
			for(j=0; j<M; j++){
				if(ImageArray2d[i][j]>t) YCoord[t] +=ImageArray2d[i][j];
			}
		}
		thresholdInProgress.setValue(t);
		qApp->processEvents();
		 
		YCoord[t] = YCoord[t]/TotalColor; 
	}
	std::vector <double> F;
	F.resize(256); 
	unsigned int sigma,xx;
	double density; 
	double mindensity; 
	mindensity = 10E5;
	for (sigma=0; sigma<255; sigma++) {
		for (xx=0; xx<255; xx++){
			if (xx<=sigma) {
				F[xx] = 1;}
				if (xx>sigma) {
					F[xx] = 0;}	
		}
			
		density = 0;
		for (t = 1; t< 255; t++) {
			density += abs(YCoord[t] - F[t]); 			
		}
		if (density < mindensity) {mindensity = density;}
	}
	QString Density;
	Density.setNum(mindensity);
	Density = "Density Distribution=" +Density;
	drawDensityVsThreshold = new  DrawWidget();
	drawDensityVsThreshold->setMSTCoord(Density);
	drawDensityVsThreshold->setXAxisLabel(X);
	drawDensityVsThreshold->setYAxisLabel(Y);
	drawDensityVsThreshold->Plot(XCoord,YCoord);
	drawDensityVsThreshold->setWindowTitle(tr("Density versus Threshold"));
	drawDensityVsThreshold->show(); }

	else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}
};
void MetricSpaceTechnique::ComponentsVsThresholdDraw(void) 		
{
	if( !ImageArray2d.empty() ){
	QString X,Y;
	X = "Threshold";
	Y = "Number of components";
	unsigned int N=ImageArray2d.size();
	unsigned int M=ImageArray2d[0].size();
	std::vector <std::vector <int> > array;
	std::vector <double> XCoord;
	std::vector <double> YCoord;
	QProgressDialog thresholdInProgress(this);
	int t;
	unsigned int i,j;
	array.resize(N);
	for(i=0; i<N; i++){
		array[i].resize(M);
	}
	Components *components = new Components;
	XCoord.resize(256);
	YCoord.resize(256);
	
	thresholdInProgress.setRange(0,256);
	thresholdInProgress.setModal(true);
	for(t=0; t<256; t++){
		for(i=0; i<N; i++){
			for(j=0; j<M; j++){
				if(ImageArray2d[i][j]>t){array[i][j]=-1;} else{ array[i][j]=0;}
			}
		}
		thresholdInProgress.setValue(t);
		qApp->processEvents();
		XCoord[t]=t;
		YCoord[t]= components->CalculateComponents(array);
	}

	double componentsValue;  
	
	componentsValue = 0;
	for (t = 1; t< 255; t++) {
		componentsValue += abs(YCoord[t] - 1); 			
	}
	
	QString ComponentsString;
	ComponentsString.setNum(componentsValue);
	ComponentsString = "Components Distribution=" +ComponentsString;
	drawComponentsVsThreshold = new  DrawWidget();
	drawComponentsVsThreshold->setMSTCoord(ComponentsString);
	drawComponentsVsThreshold->setXAxisLabel(X);
	drawComponentsVsThreshold->setYAxisLabel(Y);
	drawComponentsVsThreshold->Plot(XCoord,YCoord);
	drawComponentsVsThreshold->setWindowTitle(tr("Components versus Threshold"));
	drawComponentsVsThreshold->show(); }

	else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}
}
void MetricSpaceTechnique::PixelHistogramDraw(void)
{
	if( !ImageArray2d.empty() ){
	QString X,Y;
	X = "Intensity";
	Y = "Number of pixels";
	unsigned int N=ImageArray2d.size();
	unsigned int M=ImageArray2d[0].size();
	std::vector <double> XCoord;
	std::vector <double> YCoord;
	int t;
	double Min=0, Max=0;
	unsigned int i,j; 
	double MaxH=0;
	XCoord.resize(256);
	YCoord.resize(256);
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			if(Max<ImageArray2d[i][j]) Max=ImageArray2d[i][j];
			if(Min>ImageArray2d[i][j]) Min=ImageArray2d[i][j];
		}
	}
	
	for(t=0; t<256; t++){
		YCoord[t]=0;
		XCoord[t]=t;
		for(i=0; i<N; i++){
			for(j=0; j<M; j++){
				if((double) ImageArray2d[i][j]==t ) 
					YCoord[t]++;
				}
			}
		}
		
	double pixelHistogramValue;  

	for (t = 0; t< 256; t++) {
	      if(YCoord[t] > MaxH) {MaxH = YCoord[t];}		
	}


	pixelHistogramValue = 2*N*M - 2*MaxH; 
	
	QString PixelHistogramString;
	PixelHistogramString.setNum(pixelHistogramValue);
	PixelHistogramString = "Pixels Distribution=" +PixelHistogramString;
	drawPixelHistogram = new  DrawWidget();
	drawPixelHistogram->setMSTCoord(PixelHistogramString);
	drawPixelHistogram->setXAxisLabel(X);
	drawPixelHistogram->setYAxisLabel(Y);
	drawPixelHistogram->Plot(XCoord,YCoord);
	drawPixelHistogram->setWindowTitle(tr("Pixel Histogram"));
	drawPixelHistogram->show(); }

	else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}
}
void MetricSpaceTechnique::averageSpectrum(void)
{
	if( !ImageArray2d.empty() ){
	QString average;
	unsigned int i,j, maxx, maxy,area;
	double sum;
	maxx=ImageArray2d.size();
	maxy=ImageArray2d[0].size();
	area = maxx * maxy;
	sum = 0; 
	for(i = 0; i != maxx; i++) {
		for(j = 0; j != maxy; j++) {
			//if(ImageArray2d[i][j]>110) sum += (ImageArray2d[i][j]-110);
			sum += ImageArray2d[i][j];
		}
	}
	QTextStream(&average) << "Average Pixel Value ="<< sum/area <<" Total Color= "<< sum;

	AverageSpectrum->setAverageText(average);
	AverageSpectrum->setWindowTitle(tr("Average Spectrum"));
	AverageSpectrum->adjustSize();
	AverageSpectrum->show();  }

	else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}

}

AverageSpectrumWidget::AverageSpectrumWidget(QWidget *parent): QWidget(parent)
{
	AverageLabel = new QLabel;
	
	QVBoxLayout *AverageSpectrumLayout = new QVBoxLayout;
	AverageSpectrumLayout->addWidget(AverageLabel);
	setLayout(AverageSpectrumLayout);
	
};

void AverageSpectrumWidget::setImageLabel(QImage I)
{
	AverageLabel->setPixmap(QPixmap::fromImage(I));
	AverageLabel->adjustSize();
}	
void MetricSpaceTechnique::FilamentIndex(void) 
{
	if( !ImageArray2d.empty() ){
	QString X = "Threshold";
	QString Y = "Average Filament Index";
	QProgressDialog thresholdInProgress(this);
	unsigned int i,j, maxx, maxy;
	int threshold;
	std::vector<std::vector <int> > ImageOn;
	std::vector <double> XCoord;
	std::vector <double> YCoord;
	maxx=ImageArray2d.size();
	maxy=ImageArray2d[0].size();
	ImageOn.resize(maxx);
	double IndexCoordinate = 0;
	AreaPerimeterCalculator *AreaPerimeterIndex = new AreaPerimeterCalculator;
	for(i=0;i< maxx; i++){ ImageOn[i].resize(maxy); }
	XCoord.resize(256); YCoord.resize(256);
		
	thresholdInProgress.setRange(80,256);
	thresholdInProgress.setModal(true);
	double Value; 
	for (threshold=80; threshold < 256; threshold++){
		for(i = 0; i != maxx; ++i) {
			for(j = 0; j != maxy; ++j) {
				ImageOn[i][j]=0;
				if(ImageArray2d[i][j] >= threshold) {ImageOn[i][j]=-1;}
			}		
		}
		thresholdInProgress.setValue(threshold);
		qApp->processEvents();
		Value = AreaPerimeterIndex->AverageFilamentIndex(ImageOn);
		YCoord.push_back(Value);
		IndexCoordinate += Value;
		XCoord.push_back(threshold);	
	}
	QString FilamentIndexString;
	FilamentIndexString.setNum(IndexCoordinate);
	FilamentIndexString = "Filament Index=" +FilamentIndexString;
	drawFilamentIndexVsThreshold = new DrawWidget();
	drawFilamentIndexVsThreshold->setXAxisLabel(X);
	drawFilamentIndexVsThreshold->setYAxisLabel(Y);
	drawFilamentIndexVsThreshold->setMSTCoord(FilamentIndexString);
	drawFilamentIndexVsThreshold->Plot(XCoord,YCoord);
	drawFilamentIndexVsThreshold->setWindowTitle(tr("Filament Index"));
	drawFilamentIndexVsThreshold->show(); }

	else {
        QMessageBox::warning(this, tr("Warning"), tr("Please load an image"));}
};


