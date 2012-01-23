#ifndef RENYICALCULATOR_H
#define RENYICALCULATOR_H

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


class RenyiCalculator: public QWidget
{
    Q_OBJECT
    public:
        RenyiCalculator();
        ~RenyiCalculator(){};
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
        QDoubleSpinBox  *RenyiBox;
        int Tmin, Step, NumBoxes;
        int xOff, yOff;
        int varOff;
        int angle, varAngle;
        double Factor;
        double Renyi_q;
};

#endif
