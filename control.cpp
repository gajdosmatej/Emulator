#include "classes.h"

//iniciace portu
Controller::Controller(Editor * editor, Compiler * comp){

    for(int i = 0; i < this->portsNumber; ++i){ this->PORTS.push_back(new Port);   }

    this->window = editor;
    this->compiler = comp;
	  this->driverLibrary = new DriverLibrary(this);
    this->systemLibrary = new SystemLibrary(this);
}

void Controller::loadText(){

    Code * code = new Code(this->window->getText());
    this->compiler->validate(code);
}

int Controller::getNumberOfPorts(){ return this->portsNumber; }

Port::Port()
{

}

SystemLibrary::SystemLibrary(Controller * IC){  this->controller = IC;  }

bool SystemLibrary::existCommand(QString command){

  int len = this->functions.size();
  for(int i = 0; i < len; ++i){

    if(functions[i] == command){  return true;  }

  }

  return false;
}

void SystemLibrary::doCommand(QString command){

  if(command == "delay"){ this->delay();  }

}

void SystemLibrary::delay(){

  QTextStream out(stdout);
  out << "yee"<< endl;


}
