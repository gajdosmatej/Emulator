//AUTOMATICKY VYGENEROVANE

#include "classes.h"



void HeadDriver::light_on(Device * device){

  device->INPUT = 1;

}



void HeadDriver::light_off(Device * device){

  device->INPUT = 0;

}



void HeadDriver::blink(Device * device){



}



void HeadDriver::processOutput(int deviceOutput, int port, DeviceWindowWrapper * deviceWindowWrapper){

    if(deviceOutput == 0){

      deviceWindowWrapper->setTextOnPort(port, "*LIGHT OFF*");

    }else if(deviceOutput == 1){

      deviceWindowWrapper->setTextOnPort(port, "*LIGHT ON*");

    }
}

HeadDriver::HeadDriver(){
this->ID = 10000;
this->functions = {"light_on","light_off","blink"};
}

void HeadDriver::execute(Device * device, QString command){
if(command == "light_on"){    this->light_on(device);  }
if(command == "light_off"){    this->light_off(device);  }
if(command == "blink"){    this->blink(device);  }
}



void ArrowDriver::move_left(Device * device){

  device->INPUT = 0;

}



void ArrowDriver::move_up(Device * device){

  device->INPUT = 1;

}



void ArrowDriver::move_right(Device * device){

  device->INPUT = 2;

}



void ArrowDriver::move_down(Device * device){

  device->INPUT = 3;

}




void ArrowDriver::processOutput(int deviceOutput, int port, DeviceWindowWrapper * deviceWindowWrapper){

    if(deviceOutput == 0){

      deviceWindowWrapper->setTextOnPort(port, "*MOVED LEFT*");

    }else if(deviceOutput == 1){

      deviceWindowWrapper->setTextOnPort(port, "*MOVED UP*");

    }else if(deviceOutput == 2){

      deviceWindowWrapper->setTextOnPort(port, "*MOVED RIGHT*");

    }else if(deviceOutput == 3){

      deviceWindowWrapper->setTextOnPort(port, "*MOVED DOWN*");

    }
}

ArrowDriver::ArrowDriver(){
this->ID = 10011;
this->functions = {"move_left","move_up","move_right","move_down"};
}

void ArrowDriver::execute(Device * device, QString command){
if(command == "move_left"){    this->move_left(device);  }
if(command == "move_up"){    this->move_up(device);  }
if(command == "move_right"){    this->move_right(device);  }
if(command == "move_down"){    this->move_down(device);  }
}

