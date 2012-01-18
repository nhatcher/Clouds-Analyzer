#include "Components.h"
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
 
Components::Components (){};

int Components::CalculateComponents (std::vector<std::vector<int> > box)
{	
    int imax = box.size();
    int jmax = box[0].size();
    int i,j;
    bool notFinished;
    std::vector <int> stackX;
    std::vector <int> stackY;
    int nobj=0;
    for(i=0;i<imax;i++){
        for(j=0;j<jmax;j++){
            if(box[i][j]==-1){
                nobj++;
                stackX.push_back(i); stackY.push_back(j);
                notFinished=true;
                while(notFinished){
                    box[i][j]=nobj;
                    if(box[sum(i+1,imax)][j]==-1){
                        i=sum(i+1,imax);
                        stackX.push_back(i); stackY.push_back(j);
                    } else { 
                        if(box[sum(i+1,imax)][sum(j+1,jmax)]==-1){
                            i=sum(i+1,imax); j=sum(j+1,jmax);
                            stackX.push_back(i); stackY.push_back(j);
                        }else {
                            if(box[i][sum(j+1,jmax)]==-1){
                                j=sum(j+1,jmax);
                                stackX.push_back(i); stackY.push_back(j);
                            } else{
                                if(box[sum(i-1,imax)][sum(j+1,jmax)]==-1){
                                    i=sum(i-1,imax); j=sum(j+1,jmax);
                                    stackX.push_back(i); stackY.push_back(j);
                                }else{
                                    if(box[sum(i-1,imax)][j]==-1){
                                        i=sum(i-1,imax);
                                        stackX.push_back(i); stackY.push_back(j);
                                    }else{
                                        if(box[sum(i-1,imax)][sum(j-1,jmax)]==-1){
                                            i=sum(i-1,imax); j=sum(j-1,jmax);
                                            stackX.push_back(i); stackY.push_back(j);
                                        }else {
                                            if(box[i][sum(j-1,jmax)]==-1){
                                                j=sum(j-1,jmax);
                                                stackX.push_back(i); stackY.push_back(j);
                                            }else{
                                                if(box[sum(i+1,imax)][sum(j-1,jmax)]==-1){
                                                    i=sum(i+1,imax); j=sum(j-1,jmax);
                                                    stackX.push_back(i); stackY.push_back(j);
                                                } else {
                                                    if(stackX.size()==1) {
                                                        notFinished=false;
                                                    } else {
                                                        stackX.pop_back(); stackY.pop_back();
                                                        i=stackX.back(); j=stackY.back();
                                                    };
                                                };
                                            };
                                        };
                                    };
                                };
                            };
                        };
                    };
                };
            };
        };
    };
    return nobj;
}


int Components::sum(int i, int max)
{
    if(i<0) return sum(i+max,max);
    if(i>=max) return sum(i-max,max);
    return i;
};

