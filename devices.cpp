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


Head::Head()
{

    this->ID = 10000;

}
