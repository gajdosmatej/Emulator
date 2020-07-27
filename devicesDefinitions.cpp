//AUTOMATICKY VYGENEROVANE

#include "devicesDefinitions.h"

ErrorDevice::ErrorDevice() : Device(){
this->ID = 0;
this->period = 1000;
};

void ErrorDevice::work()
{};Head::Head() : Device(){
this->ID = 10000;
this->period = 1000;
};

void Head::work()
{

  switch(this->INPUT){

    case 0:
      this->OUTPUT = 0;
      break;

    case 1:
      this->OUTPUT = 1;
      break;

  }

};