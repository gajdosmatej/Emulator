#include "classes.h"

//iniciace portu
Controller::Controller(Editor * editor, Compiler * comp){

    for(int i = 0; i < this->portsNumber; ++i){ this->PORTS.push_back(new Port);   }

    this->window = editor;
    this->compiler = comp;
	this->driverLibrary = new DriverLibrary(this);
}

void Controller::loadText(){

    Code * code = new Code(this->window->getText());
    this->compiler->validate(code);
}

int Controller::getNumberOfPorts(){ return this->portsNumber; }

Port::Port()
{

}
