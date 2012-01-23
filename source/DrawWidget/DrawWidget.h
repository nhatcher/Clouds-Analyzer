#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <vector>

class DrawWidget: public QWidget
{
	Q_OBJECT
	public:
		DrawWidget(QWidget *parent=0);
		~DrawWidget(){};
		
		void Plot(std::vector <double>, std::vector <double>);
		void PlotLinearFit(std::vector <double>, std::vector <double>);
		void setMSTCoord(QString S){ MSTCoord = S; };
		void setXAxisLabel(QString S){ XAxisLabel = S; };
		void setYAxisLabel(QString S){ YAxisLabel = S; };
		void setAditionalText(QString S) {AditionalText = S;};
		void setAditionalText2(QString S) {AditionalText2 = S;};
		void setAditionalText3(QString S) {AditionalText3 = S;};
		void setAditionalText4(QString S) {AditionalText4 = S;};
		void setEquation(QString E) {Equation = E;};
		
	public slots:
		void saveData(void); 
		void saveImage(void);
		
		
	private:
		std::vector<double> xcoordCopy;
		std::vector<double> ycoordCopy;
		QImage imageCopy;
		QString MSTCoord;
		QString XAxisLabel;
		QString YAxisLabel;
		QString AditionalText; QString AditionalText2; QString AditionalText3; QString AditionalText4;
		QString Equation;

};
#endif

