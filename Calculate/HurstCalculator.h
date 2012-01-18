#ifndef HURSTCALCULATOR_H
#define HURSTCALCULATOR_H

#include <vector>
#include <QObject>
#include <QWidget>
#include <QLabel>

#include "Fractal2D.h"
#include "Components.h"

#include "DrawWidget.h"

class DrawWidget;

class HurstCalculator
{

	public:
		 HurstCalculator();
		~HurstCalculator(){};
		
		double HCalculator(std::vector<std::vector<int> > arrayimagen);
		double HCalculator(std::vector<int>  arrayimagen1d);
		
	private:
		double expHurst;
		DrawWidget *drawHurst;
};
#endif
 
