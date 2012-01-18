#ifndef HENONMAP_H
#define HENONMAP_H

#include <QObject>
#include <vector>
#include <QWidget>

class HenonPage: public QWidget
{
     Q_OBJECT
     public slots:
	void setHenon_a(double a){Henon_a=a;}
	void setHenon_b(double b){Henon_b=b;}
	void setHenon_iter(int iter){Henon_iter=iter;}
	void setmag(double m){mag=m;}

    public:
	HenonPage(QWidget *parent = 0);
	~HenonPage(){};
	void generate( void);
	std::vector<std::vector<int> > getimage(void){return image;};
    private:
	std::vector<std::vector <int> > image;
	double Henon_a, Henon_b;
	double mag;
    bool ergodic;
	int Henon_iter;
};

#endif