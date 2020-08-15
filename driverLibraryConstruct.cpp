#include "classes.h"
//AUTOMATICKY GENEROVANE
DriverLibrary::DriverLibrary(Controller * par, Editor * w){
this->controller = par;
this->window = w;
this->drivers.append(new HeadDriver);
this->drivers.append(new ArrowDriver);
}