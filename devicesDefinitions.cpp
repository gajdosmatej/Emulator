//AUTOMATICKY VYGENEROVANE

#include "classes.h"

Arrow::Arrow() : Device(){
this->ID = 10011;
this->period = 2000;
this->name = "Arrow";
};

void Arrow::work()
{

  switch(this->INPUT){

    case 0:
      this->OUTPUT = 0;
      break;

    case 1:
      this->OUTPUT = 1;
      break;
      
    case 2:
      this->OUTPUT = 2;
      break;
      
    case 3:
      this->OUTPUT = 3;
      break;

  }

};ErrorDevice::ErrorDevice() : Device(){
this->ID = 0;
this->period = 1000;
this->name = "ErrorDevice";
};

void ErrorDevice::work()
{};Head::Head() : Device(){
this->ID = 10000;
this->period = 1000;
this->name = "Head";
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