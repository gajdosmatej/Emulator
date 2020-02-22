#include "classes.h"


HeadDriver::HeadDriver()
{

    this->ID = 10000;
    this->functions = {"blink", "light_on", "light_off"};

}

void HeadDriver::execute(Device * device, QString &command){

  if(command == "blink") this->blink(device);
  if(command == "light_on") this->light_on(device);
  if(command == "light_off")  this->light_off(device);

}

void HeadDriver::light_on(Device * device){

  device->state = 1;

}

void HeadDriver::light_off(Device * device){

  device->state = 0;

}

void HeadDriver::blink(Device * device){



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

void DriverLibrary::doCommand(int pinNum, QString &command){

    int id = this->controller->PORTS[pinNum]->device->ID;

    for(int i = 0; i < this->drivers.size(); ++i){

			//driver ma spravne id
			if(this->drivers[i]->ID == id){

				this->drivers[i]->execute(this->controller->PORTS[pinNum]->device, command);

			}
		}
}

DriverLibrary::DriverLibrary(Controller * par){

	this->controller = par;

}
