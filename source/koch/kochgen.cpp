#include <vector>
#include "kochgen.h"
#include <iostream>

koch_fractal::koch_fractal ()
{
    line="RDLU";
    up="LURU";
    right="URDR";
    left="DLUL";
    down="RDLD";
	dots=30;
}

/*koch_fractal::koch_fractal (string starter)
{
    line=starter;
    up="ULURU";
    right="RURDR"; 
    left="LDLUL";
    down="DRDLD";
}*/


void koch_fractal::itera (unsigned int ite)
{
    unsigned int i, j, pos=1;
    unsigned int size=line.length();

    for(i=1; i< ite +1; i++){
        pos=0;
        size=line.length();
        for(j=0;j<size; j++){
            switch(line.at(pos)){
                case 'R':
                    line.replace(pos,1,right);
                    pos=pos+right.length();
                    break;
                case 'U':
                    line.replace(pos,1,up);
                    pos=pos+up.length();
                    break;
                case 'L':
                    line.replace(pos,1,left);
                    pos=pos+left.length();
                    break;
                case 'D':
                    line.replace(pos,1,down);
                    pos=pos+down.length();
                    break;
            }
        }
    }
	
}


void koch_fractal::setimage ( void ) 
{	
    unsigned int i,j;
    int posx=0,posy=0;
    int minx=0, miny=0, maxx = 0, maxy=0;
	
		
    for(i=0; i<line.length();i++){
        switch(line.at(i)){
            case 'R':
                posx++;
                break;
            case 'U':
                posy++;
                break;
            case 'L':
                posx--;
                break;
            case 'D':
                posy--;
                break;
        }
        if(maxx<posx) maxx=posx;
        if(maxy<posy) maxy=posy;
        if(minx>posx) minx=posx;
        if(miny>posy) miny=posy;
    }
	// Hace espacio para la imagen
	
    image.resize((maxx+1-minx)*dots);
    for( i = 0; i < image.size(); i++) {
        image[i].resize((maxy+1-miny)*dots);
    }
	for(i=0;i<image.size(); i++){
		for(j=0;j<image[i].size();j++){
			image[i][j]=1;
		}
	}
// Hacen que la esquina inferior izquierda se (0,0)
    posx=-minx*dots;
    posy=-miny*dots;
    for(i=0; i<line.length();i++){
        switch(line.at(i)){
            case 'R':
				for(j=0;j<dots;j++){ posx++; image[posx][posy] = 0;}
                break;
            case 'U':
				for(j=0;j<dots;j++){ posy++; image[posx][posy] = 0;}
                break;
            case 'L':
				for(j=0;j<dots;j++){ posx--; image[posx][posy] = 0;}
                break;
            case 'D':
				for(j=0;j<dots;j++){ posy--; image[posx][posy] = 0;}
                break;
            default:
                posy++;  // Inalcanzable
                break;
        }
	//	std::cout << posx <<","<< posy<< std::endl;
       //image[posx][posy] = 0;
    }
}
vector <vector<int> > koch_fractal::getimage ( void ) 
{
    return image;
}
