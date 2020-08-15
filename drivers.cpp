#include "classes.h"

/*
HeadDriver::HeadDriver()
{

    this->ID = 10000;
    this->functions = {"blink", "light_on", "light_off"};

}

void HeadDriver::execute(Device * device, QString command){

  if(command == "blink") this->blink(device);
  if(command == "light_on") this->light_on(device);
  if(command == "light_off")  this->light_off(device);

}

void HeadDriver::light_on(Device * device){

  device->INPUT = 1;

}

void HeadDriver::light_off(Device * device){

  device->INPUT = 0;

}

void HeadDriver::blink(Device * device){



}

void HeadDriver::processOutput(int deviceOutput, int port, DeviceWindowWrapper * deviceWindowWrapper)
{

    if(deviceOutput == 0){

      deviceWindowWrapper->setTextOnPort(port, "*LIGHT OFF*");

    }else if(deviceOutput == 1){

      deviceWindowWrapper->setTextOnPort(port, "*LIGHT ON*");

    }
}
*/

bool DriverLibrary::existCommand(int pinNum, QString command){

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

void DriverLibrary::processOutput(DeviceWindowWrapper * deviceWindowWrapper)
{

  int portNum = this->controller->getNumberOfPorts();

  for(int i = 0; i < portNum; ++i){

    if(this->controller->PORTS[i]->device != nullptr){

      int id = this->controller->PORTS[i]->device->ID;

  		for(int j = 0; j < this->drivers.size(); ++j){

  			//driver ma spravne id
  			if(this->drivers[j]->ID == id){

  				this->drivers[j]->processOutput(this->controller->PORTS[i]->device->OUTPUT, i, deviceWindowWrapper);

  			}
  		}
    }
  }
}


void DriverLibrary::doCommand(int pinNum, QString command){

    int id = this->controller->PORTS[pinNum]->device->ID;

    for(int i = 0; i < this->drivers.size(); ++i){

			//driver ma spravne id
			if(this->drivers[i]->ID == id){

        //text do driver window
        QString winText = this->window->getText() + "DO " + command + " ON " + QString::number(pinNum) + ";\n";
        this->window->setText(winText);

				this->drivers[i]->execute(this->controller->PORTS[pinNum]->device, command);

			}
		}
}
