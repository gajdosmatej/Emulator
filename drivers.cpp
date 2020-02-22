#include "classes.h"

Driver::Driver()
{

}


HeadDriver::HeadDriver()
{

    this->ID = 10000;
    this->functions = {"blink", "light_on", "light_off"};
 
}

bool DriverLibrary::existCommand(int pinNum, QString &command){

	if(this->controller->PORTS[pinNum]->device == nullptr){	return false;	}
	else{
	
			
		int id = this->controller->PORTS[pinNum]->device->ID;

		for(int i = 0; i < this->drivers.size(); ++i){

			//driver ma spravne id
			if(this->drivers[i]->ID == id){

				for(int j = 0; j < this->drivers[i]->functions.size(); ++j){

					//driver obsahuje fci
					if(this->drivers[i]->functions[j] == command){	return true;	}

				}

			}
		}	
		return false;
	}
}


DriverLibrary::DriverLibrary(Controller * par){

	this->controller = par;

}
