#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <vector>

class Components
{
    public:
        Components();
        ~Components(){};		
        int CalculateComponents( std::vector<std::vector<int> > box);
        int sum(int, int);
  //      void VisitNext(int, int);
    private:
};
#endif

