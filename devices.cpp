#include "classes.h"


//reference na radic
DeviceManager::DeviceManager(Editor * w, Controller * IO){

    this->controller = IO;
    this->window = w;


}


Device * DeviceManager::deviceFromName(QString name, Editor * deviceEditor){
    
    if(name == "Head"){
     
        return new Head(deviceEditor);
        
    }else{
        
        return new ErrorDevice(deviceEditor);
        
    }

}

void DeviceManager::proceed(Editor * deviceEditor){

  //this->connectDevice(new Head(deviceEditor), 0);
  QString rawCode = this->window->getText();

  DeviceParser * parser = new DeviceParser;
  QVector<QString> words = parser->separateWords(rawCode);

    if(words[0] == "new"){
        
        bool ok;
        int port = words[1].toInt(&ok);
        
        if(ok){
         
            if(port < this->controller->getNumberOfPorts()){
            
                Device * device = this->deviceFromName( words[2], deviceEditor );
                
                if(device->ID != 0){
                
                    this->connectDevice(device, port);
                    
                }
            }
        }

        
    }else if(words[0] == "delete"){
        
        
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

Device::Device(Editor * w){

  this->window = w;

  this->timer = new QTimer(this);
  connect(this->timer, SIGNAL(timeout()), this, SLOT(readState()));
  timer->start(100);

}

ErrorDevice::ErrorDevice(Editor * w) : Device(w){
    
    this->ID = 0;
    
}

void ErrorDevice::readState(){};

Head::Head(Editor * w) : Device(w)
{

    this->ID = 10000;
    this->period = 1000;

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
