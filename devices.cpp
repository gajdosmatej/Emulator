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

Device::Device(){

  this->timer = new QTimer(this);
  connect(this->timer, SIGNAL(timeout()), this, SLOT(readState()));
  timer->start(1000);

}

Head::Head()
{

    this->ID = 10000;

}

void Head::readState(){

  QTextStream out(stdout);
  out << this->state << endl;


}
