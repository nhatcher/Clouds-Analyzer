 
 #ifndef PLOTWIDGET_H
 #define PLOTWIDGET_H
 
 #include <QObject>
 #include <QWidget>
 #include <QLabel>
 #include <vector>
 class QLabel;
 class QImage;
 
 class PlotWidget: public QWidget
 {
     Q_OBJECT
     public:
	 PlotWidget(QWidget *parent=0);
	 ~PlotWidget(){};
	 void setData(std::vector<double> x, std::vector<double> y);
	 void setData(std::vector<double> y);
	 void setType(QString type);
	 void linearFit(void);
	 void makePlot(void);
	 void AddInformation(QString );
     public slots:
	 void saveData(void); 
	 void saveImage(void);
     protected:
	 void resizeEvent(QResizeEvent *event);
     private:
	 std::vector<double> XCoord;
	 std::vector<double> YCoord;
	 double Plot_RSqu, Plot_m, Plot_b;
	 QLabel *ImageLabel;
	 QLabel *InformationLabel;
	 QString Information;
	 QImage imagen;
	 bool LinearFitEnabled;
	// int longX, longY;
 };
 #endif
 