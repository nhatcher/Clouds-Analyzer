

#ifndef KOCHGEN_H
#define KOCHGEN_H

#include <string>
#include <vector>

using namespace std;

class koch_fractal
{
    public:
        koch_fractal ();
        koch_fractal (string starter);
        ~koch_fractal(){};
        void itera (unsigned int ite);
        void setimage (void);
		void setStarter(string starter){line=starter;};
		void setUp(string s){up=s;};
		void setDown(string s){down=s;};
		void setLeft(string s){left=s;};
		void setRight(string s){right=s;};
		void setDots(unsigned int d){dots=d;};
        vector <vector <int> > getimage (void);
    private:
        string line;
        string up, down, left, right;
        vector <vector <int> > image;
		unsigned int dots;
}; 
#endif
