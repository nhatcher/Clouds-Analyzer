#ifndef CORRELATIONCALCULATOR_H
#define CORRELATIONCALCULATOR_H

#include <vector>
#include <QWidget>
#include <QObject>
#include "PlotWidget.h"

class PlotWidget;
class QSpinBox;
class PlotWidget;

class CorrelationCalculator:public QWidget
{
    
    Q_OBJECT
    public:
        CorrelationCalculator();
        ~CorrelationCalculator(){};
        int getTmax(void){return Tmax;};
        int getTmin(void){return Tmin;};
        void setData(std::vector<std::vector<bool> > Image);
        void calculate(void);
    private slots:
        void acceptar();
    private:
        std::vector<std::vector<bool> > ImageBool;
        PlotWidget *plotter;
        QSpinBox *TminBox;
        QSpinBox *TmaxBox;
        int Tmax, Tmin;
};

#endif
