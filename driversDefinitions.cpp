//AUTOMATICKY VYGENEROVANE

#include "driversDefinitions.h"



void HeadDriver::light_on(Device * device){

  device->INPUT = 1;

}



void HeadDriver::light_off(Device * device){

  device->INPUT = 0;

}



void HeadDriver::blink(Device * device){



}

HeadDriver::HeadDriver(){
this->ID = 10000
this->functions = {"light_on","light_off","blink"}
}
