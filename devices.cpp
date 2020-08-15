#include "classes.h"


//reference na radic
DeviceManager::DeviceManager(Editor * w, Controller * IO){

    this->controller = IO;
    this->window = w;


}

void DeviceManager::proceed(){

  //this->connectDevice(new Head(deviceEditor), 0);
  QString rawCode = this->window->getText();

  DeviceParser * parser = new DeviceParser;
  QVector<QString> words = parser->separateWords(rawCode);

    if(words[0] == "new"){

        bool ok;
        int port = words[1].toInt(&ok);

        if(ok){

            if(port < this->controller->getNumberOfPorts()){

                Device * device = this->deviceFromName( words[2] );

                if(device->ID != 0){

                    this->connectDevice(device, port);

                }
            }
        }


    }else if(words[0] == "delete"){

      bool ok;
      int port = words[1].toInt(&ok);

      if(ok){

          if(port < this->controller->getNumberOfPorts()){

              this->disconnectDevice(port);
          }
      }

    }

  //zkouska jestli parsovani funguje
    //QTextStream o(stdout);
  //for(int i = 0; i < words.length(); ++i){ o<<words[i];}

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
  connect(this->timer, SIGNAL(timeout()), this, SLOT(work()));
  timer->start(this->period);

}
/*
ErrorDevice::ErrorDevice() : Device()
{

    this->ID = 0;
    this->name = "Grounded";

}

void ErrorDevice::work()
{};

Head::Head() : Device()
{

    this->ID = 10000;
    this->period = 1000;
    this->name = "Head";

}

void Head::work(){

  switch(this->INPUT){

    case 0:
      this->OUTPUT = 0;
      break;

    case 1:
      this->OUTPUT = 1;
      break;

  }
}*/
