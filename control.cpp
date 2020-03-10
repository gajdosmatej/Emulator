#include "classes.h"

Call::Call(){}

SystemCall::SystemCall(SystemLibrary * sysLib, QString com){

  this->systemLibrary = sysLib;
  this->command = com;

}

void SystemCall::doCommand(){

  this->systemLibrary->doCommand(this->command);

}

DriverCall::DriverCall(DriverLibrary * driverLib, QString com, int portNum){

  this->driverLibrary = driverLib;
  this->command = com;
  this->portNumber = portNum;

}

void DriverCall::doCommand(){

  this->driverLibrary->doCommand(this->portNumber, this->command);

}

ErrorCall::ErrorCall(Compiler * comp, QString message, QString com){

  this->errorMessage = message;
  this->compiler = comp;
  this->command = com;

}

void ErrorCall::doCommand(){

  QString err = this->errorMessage + " (in: \"" + this->command + "\")";
  this->compiler->print(err);

}


//iniciace portu
Controller::Controller(Editor * editor, Compiler * comp, Editor * driverWindow){

    for(int i = 0; i < this->portsNumber; ++i){ this->PORTS.push_back(new Port);   }

    this->window = editor;
    this->compiler = comp;
	  this->driverLibrary = new DriverLibrary(this, driverWindow);
    this->systemLibrary = new SystemLibrary(this, driverWindow);
}

void Controller::loadText(){

    Code * code = new Code(this->window->getText());
    this->compiler->validate(code);
}

int Controller::getNumberOfPorts(){ return this->portsNumber; }

Port::Port()
{

}

SystemLibrary::SystemLibrary(Controller * IC, Editor * w){  

  this->controller = IC;
  this->window = w;

}

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
