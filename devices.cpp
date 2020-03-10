#include "classes.h"


//reference na radic
DeviceManager::DeviceManager(Controller * IO){

    this->controller = IO;

}


//dej portu v radici referenci na zarizeni
void DeviceManager::connectDevice(Device * device, int port){

    this->controller->PORTS[port]->device = device;

}

//smaz portu v radici referenci na zarizeni
void DeviceManager::disconnectDevice(int port){

    delete this->controller->PORTS[port]->device;
    this->controller->PORTS[port]->device = nullptr;

}

Device::Device(Editor * w){

  this->window = w;

  this->timer = new QTimer(this);
  connect(this->timer, SIGNAL(timeout()), this, SLOT(readState()));
  timer->start(50);

}

Head::Head(Editor * w) : Device(w)
{

    this->ID = 10000;

}

void Head::readState(){

  QString printedText;

  switch(this->state){

    case 0:
      printedText = "*NOT LIGHTING*";
      break;

    case 1:
      printedText = "*LIGHTING*";
      break;

  }
  this->window->setText(printedText);


}
