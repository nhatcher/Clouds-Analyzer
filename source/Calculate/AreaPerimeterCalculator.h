#ifndef AREAPERIMETERCALCULATOR_H
#define AREAPERIMETERCALCULATOR_H


#include <QObject>
#include <QWidget>
#include <QLabel>
#include <vector>
#include "Fractal2D.h"
#include "Components.h"
#include "DrawWidget.h"

class DrawWidget;


class AreaPerimeterCalculator
{

    public:
        AreaPerimeterCalculator();
        ~AreaPerimeterCalculator(){};
		
        double APCalculator(std::vector<std::vector<int> > ComponentsVector);
	double AverageFilamentIndex(std::vector<std::vector<int> > ComponentsVector);
	void setMinimumSize(unsigned int size) {MinimumSize = size;};
	void setMinimumThreshold(unsigned int s) {MinimumThreshold = s;};
	void setMaximumThreshold(unsigned int s) {MaximumThreshold = s;};
	void setStep(unsigned int s) {Step = s;};
        int sum(int, int);
   
		
    private:
        double Dper;
	unsigned int MinimumSize; 
	unsigned int MinimumThreshold;
	unsigned int MaximumThreshold;
	unsigned int Step;
	DrawWidget *drawAreaPerimeterVsThreshold;
};



class CalculateAreaPerimeterWidget: public QWidget
{
    Q_OBJECT
    public:
	CalculateAreaPerimeterWidget(QWidget *parent = 0);
	~CalculateAreaPerimeterWidget(){};
	void setAreaPerimeterText (QString s){ AreaPerimeterLabel->setText(s);};
	unsigned int getMinSize(void) {return MinimumSize;};
	unsigned int getMaximumThreshold(void) {return MaximumThreshold;};
	unsigned int getMinimumThreshold(void) {return MinimumThreshold;};
	unsigned int getNumberOfSteps(void) {return NumberOfSteps;};
    public slots:
	void setMinSize(int s) {MinimumSize = (unsigned int) s;};
	void setMinimumThreshold(int s) {MinimumThreshold = (unsigned int) s;};
	void setMaximumThreshold(int s) {MaximumThreshold = (unsigned int) s;};
	void setNumberOfSteps(int s) {NumberOfSteps = (unsigned int) s;};
    signals:
	void calculateAreaPerimeter(void);
	
    private:
	QLabel *AreaPerimeterLabel;
	unsigned int MinimumSize; 
	unsigned int MinimumThreshold;
	unsigned int MaximumThreshold;
	unsigned int NumberOfSteps;
};


class CalculateAreaPerimeterOptions: public QDialog
{
    Q_OBJECT
    public:
	//CalculateOptions(QWidget *parent=0);
	CalculateAreaPerimeterOptions(unsigned int , unsigned int , unsigned int, unsigned int, QWidget *parent=0);
	~CalculateAreaPerimeterOptions(){};
	unsigned int getMinSize(){return minSize;};
	unsigned int getMaximumThreshold(void) {return MaximumThreshold;};
	unsigned int getMinimumThreshold(void) {return MinimumThreshold;};
	unsigned int getNumberOfSteps(void) {return NumberOfSteps;};
    public slots:
	void setMinSize(int S){minSize=(unsigned int) S;};
	void setMinimumThreshold(int s) {MinimumThreshold = (unsigned int) s;};
	void setMaximumThreshold(int s) {MaximumThreshold = (unsigned int) s;};
	void setNumberOfSteps(int s) {NumberOfSteps = (unsigned int) s;};
    private:
	unsigned int minSize;
	unsigned int MinimumThreshold;
	unsigned int MaximumThreshold;
	unsigned int NumberOfSteps;
};
#endif
