#include <iostream>
#include "sculptor.hpp"

using namespace std;

int main(void)
{  
  Sculptor s(10,10,10);
  s.setColor(0, 0, 1.0, 1.0);
  s.putEllipsoid(6, 6, 6, 4, 3 ,3);

  s.writeOFF("Elipsoid.off");
     return 0;
}
