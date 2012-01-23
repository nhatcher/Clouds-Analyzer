#ifndef BOXCOUNTINGCALCULATOR_H
#define BOXCOUNTINGCALCULATOR_H

#include <vector>
#include <QWidget>
#include <QObject>
#include "PlotWidget.h"

class QSpinBox;
class QDoubleSpinBox;
class PlotWidget;
class QRadioButton;
class QComboBox;
class QPushButton;


class BoxCountingCalculator: public QWidget
{
    Q_OBJECT
    public:
        BoxCountingCalculator();
        ~BoxCountingCalculator(){};
        uint getNumBoxes(){return NumBoxes;};
        uint getTmin(){return Tmin;};
        void setData(std::vector<std::vector<bool> > Image);
    public slots:
        void calculate();
    private slots:
        void aceptar();
        void changeOffSet(int index);
        void changeAngle(int index);
    private:
        std::vector<std::vector<bool> > ImageBool;
        std::vector<int> boxes;
        PlotWidget *plotter;
        QSpinBox *TminBox;
        QSpinBox *StepBox;
        QDoubleSpinBox *FactorBox;
        QSpinBox *NumBoxesBox;
        QRadioButton *AritmeticCheckBox;
        QRadioButton *GeometricCheckBox;
        QComboBox *OffSetComboBox;
        QComboBox *AngleComboBox;
        QSpinBox *xOffSetBox;
        QSpinBox *yOffSetBox;
        QSpinBox *varOffSetBox;
        QSpinBox *angleBox;
        QSpinBox *angleVarBox;
        QPushButton *goButton;
        int Tmin, Step, NumBoxes;
        int xOff, yOff;
        int varOff;
        int angle, varAngle;
        double Factor;
};

#endif
