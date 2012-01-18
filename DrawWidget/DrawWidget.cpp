#include "DrawWidget.h"
#include <vector>
#include <cmath>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QtGui>
#include <iostream>
using namespace std;
DrawWidget::DrawWidget( QWidget *parent): QWidget(parent) {}

void DrawWidget::saveData(void)
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::currentPath(),  tr("Data (*.txt)"));
	
	QFile file(fileName);
	file.open( QIODevice::WriteOnly);
	QTextStream stream( &file );
	
	for (int i =0; i<xcoordCopy.size(); i++) {
		stream <<  xcoordCopy[i] << "\t" << ycoordCopy[i] << endl; }
		
		file.close();
}
void DrawWidget::saveImage(void)
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::currentPath(), tr("Image (*.png, *.jpg)"));
	imageCopy.save(fileName);
}

void DrawWidget::Plot(std::vector <double> XCoord, std::vector <double> YCoord)
{
	double maxX=XCoord[0], maxY=YCoord[0], minX=XCoord[0], minY=YCoord[0];
	uint i;
	for(i=0; i< XCoord.size(); i++){
		if(minX>XCoord[i]) minX=XCoord[i];
		if(maxX<XCoord[i]) maxX=XCoord[i];
		if(minY>YCoord[i]) minY=YCoord[i];
		if(maxY<YCoord[i]) maxY=YCoord[i];
	}
	double p, S=0;
	for(i=0;i<256;i++){
		p=(double) YCoord[i]/maxY;
		if(p!=0) S+=p*log(p);
	}
	xcoordCopy = XCoord;
	ycoordCopy = YCoord; 
	QString maxx,minx,maxy,miny;
	maxx.setNum(maxX);
	minx.setNum(minX);
	miny.setNum(minY);
	maxy.setNum(maxY);
	QString Entropy;
	Entropy.setNum(S);
	Entropy="Entropy="+Entropy;
	double x,y;
	QLabel *ImageLabel= new QLabel;
	QImage image (540,540,QImage::Format_RGB32);
	QPainter painter;
	painter.begin(&image);
	painter.eraseRect(0,0,540,540);
	painter.setPen(Qt::blue);
	painter.setBrush(Qt::blue);
	for(i=0;i<=XCoord.size();i++){
		x=(XCoord[i]-minX)*500.0/(maxX-minX)+30;
		y=(YCoord[i]-minY)*500.0/(maxY-minY);
		painter.drawEllipse(x,500.0-y,5,5);
	}
	painter.setPen(Qt::black);

	painter.drawText(320,40,MSTCoord);
	painter.drawLine(30,500,30,0);
	painter.drawText(0,10,maxy);
	painter.drawText(0,500,miny);
	painter.drawText(450,450,AditionalText);
	painter.drawLine(30,500,530,500);
	painter.drawText(30,515,minx);
	painter.drawText(520,515,maxx);
	painter.drawText(240,520,XAxisLabel);
	painter.rotate(270);
	painter.translate(-500,0);
	painter.drawText(200,10,YAxisLabel);
	painter.end();
	ImageLabel->setPixmap(QPixmap::fromImage(image));
	ImageLabel->adjustSize();
	QPushButton *saveDataButton = new QPushButton(tr("Save Data"));
	saveDataButton->setFixedSize(100,30);
	QPushButton *saveImageButton = new QPushButton(tr("Save Image"));
	saveImageButton->setFixedSize(100,30);

	connect(saveDataButton,SIGNAL(clicked()), this,SLOT(saveData()));
	connect(saveImageButton,SIGNAL(clicked()), this,SLOT(saveImage()));
	QVBoxLayout *Layout = new QVBoxLayout;
	Layout->addWidget(ImageLabel);
	QHBoxLayout *HLayout = new QHBoxLayout;
	HLayout->addStretch();
	HLayout->addWidget(saveDataButton);
	HLayout->addWidget(saveImageButton);

	Layout->addLayout(HLayout);
	setLayout(Layout);
	imageCopy = image;
}

void DrawWidget::PlotLinearFit(std::vector <double> XCoord, std::vector <double> YCoord)
		
{		xcoordCopy = XCoord;
		ycoordCopy = YCoord; 
		double maxX=XCoord[0], maxY=YCoord[0], minX=XCoord[0], minY=YCoord[0];
		uint i;
		for(i=0; i< XCoord.size(); i++){
			if(minX>XCoord[i]) minX=XCoord[i];
			if(maxX<XCoord[i]) maxX=XCoord[i];
			if(minY>YCoord[i]) minY=YCoord[i];
			if(maxY<YCoord[i]) maxY=YCoord[i];
		}
		QString maxx,minx,maxy,miny;
		maxx.setNum(maxX);
		minx.setNum(minX);
		miny.setNum(minY);
		maxy.setNum(maxY);
	
		
		double RSqu, XSqu = 0, Xlin = 0, Ylin = 0, XY = 0;
		double m, b; 
		for( i=0;i<XCoord.size();i++){

			Xlin += XCoord[i];
			Ylin += YCoord[i];
			XY += XCoord[i]*YCoord[i];
			XSqu += XCoord[i]*XCoord[i];
		}
	
		m = ((XCoord.size())*XY - Xlin*Ylin)/((XCoord.size())*XSqu-Xlin*Xlin);
		b = (Ylin*XSqu - Xlin*XY)/((XCoord.size())*XSqu-Xlin*Xlin);
	
		double SSerr, SStot, YAverage = 0;
		SSerr = 0; SStot = 0;
		for( i = 0; i < XCoord.size(); i++){
			SSerr += (YCoord[i] - (m)*XCoord[i] - b)*(YCoord[i] - (m)*XCoord[i] - b);	
			YAverage += YCoord[i];
		} 
		YAverage = YAverage/YCoord.size();
		for(i = 0; i < YCoord.size(); i++){
			SStot += (YCoord[i] - YAverage)* (YCoord[i] - YAverage); }
			RSqu = 1- SSerr/SStot;
		
			QString Equation;
			Equation.setNum(m);
			Equation = " y = " + Equation;
			Equation += "x";
			QString YCut;
			YCut.setNum(b);
			YCut = " + " + YCut;
			Equation += YCut;
	
			QString RSquare;
			RSquare.setNum(RSqu);
			RSquare = " R^2 = " + RSquare;
		
		double p, S=0;
		for(i=0;i<256;i++){
			p=(double) YCoord[i]/maxY;
			if(p!=0) S+=p*log(p);
		}
		for(i=0;i<XCoord.size();i++){
			XCoord[i]=XCoord[i]-minX;
			YCoord[i]=YCoord[i]-minY;
		}
		XSqu = 0, Xlin = 0, Ylin = 0, XY = 0;
		for( i=0;i<XCoord.size();i++){

			Xlin += XCoord[i];
			Ylin += YCoord[i];
			XY += XCoord[i]*YCoord[i];
			XSqu += XCoord[i]*XCoord[i];
		}
	
		m = ((XCoord.size())*XY - Xlin*Ylin)/((XCoord.size())*XSqu-Xlin*Xlin);
		b = (Ylin*XSqu - Xlin*XY)/((XCoord.size())*XSqu-Xlin*Xlin);

		
		QString Entropy;
		Entropy.setNum(S);
		Entropy="Entropy="+Entropy;
		double x,y;
		QLabel *ImageLabel= new QLabel;
		QImage image (540,540,QImage::Format_RGB32);
		QPainter painter;
		painter.begin(&image);
		painter.eraseRect(0,0,540,540);
		painter.setPen(Qt::blue);
		painter.setBrush(Qt::blue);
		
		
		maxX = maxX - minX;
		minX = 0;
		maxY = maxY - minY;
		minY = 0;
		
		for(i=0;i<=XCoord.size();i++){
			x=(XCoord[i]*500.0/maxX)+30;
			y=(YCoord[i]*500.0/maxY);
			painter.drawEllipse(x,500 -y,5,5);
		}
		double scalingFactorX =	500.0/maxX;
		double scalingFactorY = 500.0/maxY;
		painter.setPen(Qt::magenta);
		
		painter.drawLine(maxX*scalingFactorX + 30, 500 - (m*maxX + b)*scalingFactorY, 30, 500 - (m*minX + b)*scalingFactorY);

	
		painter.setPen(Qt::black);

		painter.drawText(60,50,MSTCoord);
		painter.drawText(320,380,Equation);
		painter.drawText(320,400,RSquare);
		painter.drawText(320,420,AditionalText);
		painter.drawText(320,440,AditionalText2);
		painter.drawText(320,460,AditionalText3);
		painter.drawText(320,480,AditionalText4);
		painter.drawLine(30,500,30,0);
		painter.drawText(0,10,maxy);
		painter.drawText(0,500,miny);
		painter.drawLine(30,500,530,500);
		painter.drawText(30,515,minx);
		painter.drawText(520,515,maxx);
		painter.drawText(240,520,XAxisLabel);
		painter.rotate(270);
		painter.translate(-500,0);
		painter.drawText(200,10,YAxisLabel);
		painter.end();
		ImageLabel->setPixmap(QPixmap::fromImage(image));
		ImageLabel->adjustSize();
		QPushButton *saveDataButton = new QPushButton(tr("Save Data"));
		saveDataButton->setFixedSize(100,30);
		QPushButton *saveImageButton = new QPushButton(tr("Save Image"));
		saveImageButton->setFixedSize(100,30);

		connect(saveDataButton,SIGNAL(clicked()), this,SLOT(saveData()));
		connect(saveImageButton,SIGNAL(clicked()), this,SLOT(saveImage()));
		QVBoxLayout *Layout = new QVBoxLayout;
		Layout->addWidget(ImageLabel);
		QHBoxLayout *HLayout = new QHBoxLayout;
		HLayout->addStretch();
		HLayout->addWidget(saveDataButton);
		HLayout->addWidget(saveImageButton);

		Layout->addLayout(HLayout);
		setLayout(Layout);
		imageCopy = image;
}
