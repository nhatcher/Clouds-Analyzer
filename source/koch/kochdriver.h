#ifndef KOCHDRIVER_H
#define KOCHDRIVER_H

#include <QObject>
#include <QWidget>
#include "kochgen.h"
#include <vector>

class KochPage: public QWidget
{
	Q_OBJECT
	public slots:
		void setKochIter(int I){Koch_iter=I;};
		void setKochDots(int d){Koch_Dots=(uint) d;};
		void setKochStarter(QString s){Koch_Starter=s.toStdString();}
		void setKochUp(QString s){Koch_Up=s.toStdString();};
		void setKochDown(QString s){Koch_Down=s.toStdString();};
		void setKochRight(QString s){Koch_Right=s.toStdString();};
		void setKochLeft(QString s){Koch_Left=s.toStdString();};
	public:
		KochPage(QWidget *parent = 0);
		~KochPage(){};
		void setimage( void) {koch->setimage();};
		std::vector < std::vector <int> > getimage ( void ){return koch->getimage();};
		void Update(void);
	private:
		int Koch_iter;
		uint Koch_Dots;
		string Koch_Starter;
		string Koch_Up,Koch_Down, Koch_Left, Koch_Right;
		koch_fractal *koch; 
};

#endif
