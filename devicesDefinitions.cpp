//AUTOMATICKY VYGENEROVANE

#include "devicesDefinitions.h"

Head::Head(){
this->ID = 80;
this->period = 500;
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

